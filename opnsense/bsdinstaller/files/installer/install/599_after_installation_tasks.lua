--
--  This file cleans up after a normal install.
--

return {
	id = "after_install_routines",
	name = _("Post-installation tasks"),
	effect = function(step)
		local cmds = CmdChain.new()

		-- Execute post-install scripts
		App.state.target:cmds_post_install(cmds)

		-- Remove currently active swap used for installation
		if App.state.storage:get_activated_swap():in_units("K") > 0 then
			local spd

			for spd in App.state.sel_part:get_subparts() do
				if spd:get_fstype() == "swap" then
					cmds:add{
						cmdline = "${root}${SWAPOFF} ${root}dev/${dev}",
						replacements = {
							dev = spd:get_device_name()
						}
					}
				end
			end
		end

		cmds:execute()
	
		return step:next()
	end
}
