--
-- Select disk install mode.
--

return {
    id = "select_mode",
    name = _("Select install mode"),
    req_state = { "storage" },
    effect = function(step)
	if App.state.sel_disk:is_mounted() then
		local response = App.ui:present{
		    id = "partition_disk",
		    name = _("Partition Disk?"),
		    short_desc = _(
			"One or more subpartitions of one or more "	..
			"primary partitions of the selected disk "	..
			"are already in use (they are currently "	..
			"mounted on mountpoints in the filesystem.) "	..
			"You cannot repartition the disk under "	..
			"these circumstances. If you wish to do so, "	..
			"you must unmount the subpartitions before "	..
			"proceeding."
		    ),
		    actions = {
			{
			    id = "unmount",
			    name = _("Unmount Subpartitions"),
			    effect = function()
				local cmds = CmdChain.new()
				App.state.sel_disk:cmds_unmount_all_under(cmds)
				cmds:execute()
				return step
			    end
			},
			{
			    id = "cancel",
			    name = _("Return to %s", step:get_prev_name()),
			    accelerator = "ESC",
			    effect = function()
				return step:prev()
			    end
			}
		    }
		}
		return response.result
	end

	local mode = 0

	local cmd = App.expand("uname -m")
	local pty = Pty.Logged.open(cmd, App.log_string)
	local line = pty:readline()
	pty:close()

	-- UEFI only works on amd64
	if string.find(line, "^amd64") then
		mode = StorageUI.select_mode({
			dd = App.state.sel_disk,
			short_desc = _("Select the installation mode."),
			cancel_desc = _("Return to %s", step:get_prev_name())
		})
	end

	if mode then
		return step:next()
	else
		return step:prev()
	end
    end
}
