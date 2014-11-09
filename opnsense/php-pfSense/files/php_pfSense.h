#ifndef PHP_PFSENSE_H
#define PHP_PFSENSE_H 1

#ifdef ZTS
#include "TSRM.h"
#endif

#include "php_dummynet.h"

ZEND_BEGIN_MODULE_GLOBALS(pfSense)
	int s;
	int inets;
	int ipfw;
	int csock;
ZEND_END_MODULE_GLOBALS(pfSense)

#ifdef ZTS
#define PFSENSE_G(v) TSRMG(pfSense_globals_id, zend_pfSense_globals *, v)
extern int pfSense_globals_id;
#else
#define PFSENSE_G(v) (pfSense_globals.v)
#endif

#define PHP_PFSENSE_WORLD_VERSION "1.0"
#define PHP_PFSENSE_WORLD_EXTNAME "pfSense"

PHP_MINIT_FUNCTION(pfSense_socket);
PHP_MSHUTDOWN_FUNCTION(pfSense_socket_close);

PHP_FUNCTION(pfSense_get_interface_info);
PHP_FUNCTION(pfSense_get_interface_stats);
PHP_FUNCTION(pfSense_get_pf_stats);
PHP_FUNCTION(pfSense_get_os_hw_data);
PHP_FUNCTION(pfSense_get_os_kern_data);
PHP_FUNCTION(pfSense_get_interface_addresses);
PHP_FUNCTION(pfSense_getall_interface_addresses);
PHP_FUNCTION(pfSense_vlan_create);
PHP_FUNCTION(pfSense_interface_rename);
PHP_FUNCTION(pfSense_interface_mtu);
PHP_FUNCTION(pfSense_bridge_add_member);
PHP_FUNCTION(pfSense_bridge_del_member);
PHP_FUNCTION(pfSense_bridge_member_flags);
PHP_FUNCTION(pfSense_interface_listget);
PHP_FUNCTION(pfSense_interface_create);
PHP_FUNCTION(pfSense_interface_destroy);
PHP_FUNCTION(pfSense_interface_flags);
PHP_FUNCTION(pfSense_interface_setaddress);
PHP_FUNCTION(pfSense_interface_deladdress);
PHP_FUNCTION(pfSense_interface_capabilities);
PHP_FUNCTION(pfSense_ngctl_name);
PHP_FUNCTION(pfSense_ngctl_attach);
PHP_FUNCTION(pfSense_ngctl_detach);
PHP_FUNCTION(pfSense_get_modem_devices);
PHP_FUNCTION(pfSense_sync);
PHP_FUNCTION(pfSense_kill_states);
PHP_FUNCTION(pfSense_kill_srcstates);
PHP_FUNCTION(pfSense_ip_to_mac);

PHP_FUNCTION(pfSense_ipfw_getTablestats);
PHP_FUNCTION(pfSense_ipfw_Tableaction);
PHP_FUNCTION(pfSense_pipe_action);

extern zend_module_entry pfSense_module_entry;
#define phpext_pfSense_ptr &pfSense_module_entry

#endif
