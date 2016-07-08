--
--  This file cleans up after a normal install.
--

return {
	id = "after_install_routines",
	name = _("Post-installation tasks"),
	effect = function(step)
		local cmds = CmdChain.new()

		cmds:add(":");
		cmds:add("/usr/local/installer/after_installation_routines.sh");

		-- Remove currently active swap used for installation
		if App.state.storage:get_activated_swap():in_units("K") > 0 then
			local spd

			for spd in App.state.sel_part:get_subparts() do
				if spd:get_fstype() == "swap" then
					local dev = spd:get_device_name()
					if App.state.sel_part:set_uefi() == 1 then
						-- only one partition matches
						dev = App.state.sel_part:get_parent():get_device_name() .. "p4"
					end
					-- swap may or may not be mounted
					cmds:add("${root}${SWAPOFF} ${root}dev/" .. dev .. " || true");
				end
			end
		end

		cmds:execute()
	
		return step:next()
	end
}
