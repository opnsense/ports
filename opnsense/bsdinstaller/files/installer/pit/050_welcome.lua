-- $Id: 050_welcome.lua,v 1.10 2005/08/26 04:25:25 cpressey Exp $

--
-- "Welcome screen" for the BSD Installer.
--

return {
    id = "welcome",
    name = _("Welcome Screen"),
    effect = function(step)
	local result = App.ui:present({
	    id = "welcome",
    	    name =  App.conf.product.name ..  " " ..
		App.conf.product.version,
	    short_desc =
	       "Welcome to the " .. App.conf.product.name .. " " ..
	       " " .. App.conf.product.version .. " installer!\n\n"			..
	       "Before we begin, you will be asked a few questions "	..
	       "so that this installation environment can be set up "	..
	       "to suit your needs.\n\n"				..
	       "You will then be presented a menu of items from which "	..
	       "you may select to install a new system, with or "       ..
	       "without importing a previous configuration.",
	    actions = {
		{
		    id = "ok",
		    name = _("Ok, let's go."),
		    short_desc = _("Set up the installation environment and continue")
		}
	    }
	}).action_id

	if result == "ok" then
		return step:next()
	end
    end
}
