--
-- This file contains product-specific overrides to BSDInstaller.lua
--

product = {
	name = "OPNsense",
	version = "15.1"
}

mountpoints = function(part_cap, ram_cap)

	-- smaller than 30GB disables swap
	if part_cap < 30720 then
		return {
			{ mountpoint = "/",     capstring = "*" },
		}
	end

	-- calculate the suggested swap size
	local swap = 2 * ram_cap
	if ram_cap > (part_cap / 2) or part_cap < 4096 then
		swap = ram_cap
	end
	swap = tostring(swap) .. "M"

	return {
		{ mountpoint = "/",     capstring = "*" },
		{ mountpoint = "swap",  capstring = swap },
	}

end

mtrees_post_copy = {} -- none

install_items = {
	".cshrc",
	".profile",
	"COPYRIGHT",
	"bin",
	"boot",
	"boot.config",
	"conf",
	"cf",			-- compat glue
	"dev",
	"etc",
	"home",
	"lib",
	"libexec",
	"media",
	"proc",
	"rescue",
	"root",
	"sbin",
	"sys",
	"usr/bin",
	"usr/games",
	"usr/include",
	"usr/lib",
	"usr/lib32",
	"usr/libdata",
	"usr/libexec",
	"usr/local",
	"usr/obj",
	"usr/sbin",
	"usr/share",
	"usr/src",
	"var",
}

ui_nav_control = {
	["*/welcome"] = "ignore",				-- do not show any "welcome" items
	["*/configure_installed_system"] = "ignore",		-- don't put these on
	["pre_install_tasks/select_language"] = "ignore",	-- do not show language selection
	["pre_install_tasks/configure_network"] = "ignore",	-- no need for configuring network
	["*/upgrade_installed_system"] = "ignore",		-- the main menu...
	["*/load_kernel_modules"] = "ignore",			-- do not ask about loading kernel modules
	["*/pit/configure_console"] = "ignore",			-- do not ask about console
	["*/pit/configure_network"] = "ignore",			-- do not ask about network
	["*/*netboot*"] = "ignore",				-- ignore netboot installation services
	["*/install/select_packages"] = "ignore",		-- do not do the "Select Packages" step on install
	["*/install/confirm_install_os"] = "ignore",		-- no need to confirm os install
	["*/install/warn_omitted_subpartitions"] = "ignore",	-- warn that /tmp /var and friends are being ommited
	["*/install/finished"] = "ignore",			-- no need to extra spamming
	["*/install/select_additional_filesystems"] = "ignore",	-- do not include additional filesystems prompts
	["*/install/270_install_bootblocks.lua"] = "ignore",	-- ignore the old boot block installer program
	["*/configure/*"] = "ignore",				-- do not configure, we've already did it.
}

dir = { root = "/", tmp = "/tmp/" }

limits.part_min = "100M"

use_cpdup = true
