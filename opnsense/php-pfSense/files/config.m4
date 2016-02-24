PHP_ARG_ENABLE(pfSense, whether to enable pfSense support,
[ --enable-pfSense   Enable pfSense support])

PHP_SUBST(PFSENSE_SHARED_LIBADD)
if test "$PHP_PFSENSE" = "yes"; then
  AC_DEFINE(HAVE_PFSENSE, 1, [Whether you have pfSense])
  PHP_NEW_EXTENSION(pfSense, pfSense.c, $ext_shared)
fi
