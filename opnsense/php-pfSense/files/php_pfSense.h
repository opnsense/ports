#ifndef PHP_PFSENSE_H
#define PHP_PFSENSE_H 1

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_BEGIN_MODULE_GLOBALS(pfSense)
	int locals;
	int ngsock;
ZEND_END_MODULE_GLOBALS(pfSense)

#ifdef ZTS
#define PFSENSE_G(v) TSRMG(pfSense_globals_id, zend_pfSense_globals *, v)
extern int pfSense_globals_id;
#else
#define PFSENSE_G(v) (pfSense_globals.v)
#endif

PHP_MINIT_FUNCTION(pfSense_module_init);
PHP_MSHUTDOWN_FUNCTION(pfSense_module_exit);

PHP_FUNCTION(pfSense_get_interface_stats);
PHP_FUNCTION(pfSense_get_interface_addresses);
PHP_FUNCTION(pfSense_getall_interface_addresses);
PHP_FUNCTION(pfSense_ngctl_name);
PHP_FUNCTION(pfSense_ngctl_attach);
PHP_FUNCTION(pfSense_ngctl_detach);

extern zend_module_entry pfSense_module_entry;
#define phpext_pfSense_ptr &pfSense_module_entry

#endif
