-- $Id: 300_select_part.lua,v 1.37 2005/08/26 04:25:24 cpressey Exp $

--
-- Select partition onto which to install.
--

return {
    id = "select_part",
    name = _("Select Partition"),
    req_state = { "storage", "sel_disk" },
    effect = function(step)
	pd = App.state.sel_part

	if pd then
		if pd:is_mounted() then
			App.ui:inform(_(
			    "One or more subpartitions on the selected "	..
			    "primary partition already in use (they are "	..
			    "currently mounted in the filesystem.) "		..
			    "You should either unmount them before "		..
			    "proceeding, or select a different partition "	..
			    "or disk on which to install %s.",
			    App.conf.product.name
			))
			return step
		end

		App.state.sel_part = pd

		local part_min_capacity = Storage.Capacity.new(
		    App.conf.limits.part_min
		)
		if part_min_capacity:exceeds(pd:get_capacity()) then
			App.ui:inform(_(
			    "WARNING: primary partition #%d appears to have " ..
			    "a capacity of %s, which is less than the minimum " ..
			    "recommended capacity, %s. You may encounter "   ..
			    "problems while trying to install %s onto it.",
			    pd:get_number(),
			    pd:get_capacity():format(),
			    part_min_capacity:format(),
			    App.conf.product.name)
			)
		end

			local cmds = CmdChain.new()

			pd:cmds_set_sysid(cmds, App.conf.default_sysid)
			pd:cmds_initialize_disklabel(cmds)

			if cmds:execute() then
			--[[
				App.ui:inform(_(
				    "Primary partition #%d was formatted.",
				    pd:get_number())
				)
			--]]
				return step:next()
			else
			--[[
				App.ui:inform(_(
				    "Primary partition #%d was "	..
				    "not correctly formatted, and may "	..
				    "now be in an inconsistent state. "	..
				    "We recommend re-formatting it "	..
				    "before proceeding.",
				    pd:get_number())
				)
			--]]
				return step
			end
	else
		return step:prev()
	end
    end
}
