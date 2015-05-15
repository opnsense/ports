--
--  This file cleans up after a normal install.
--

return {
	id = "after_install_routines",
	name = _("Post-installation tasks"),
	effect = function(step)
		local cmdsAIR = CmdChain.new()

		cmdsAIR:add("/usr/local/installer/after_installation_routines.sh");
		cmdsAIR:execute()
	
		return step:next()
	end
}
