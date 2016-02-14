AC_INIT([Arabica],[2016-January],[jez@jezuk.co.uk])

AM_INIT_AUTOMAKE([1.9 tar-ustar dist-bzip2 dist-zip subdir-objects])
 
AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CXX
LT_INIT

AC_LANG([C++])

ARABICA_SELECT_XML_PARSER
ARABICA_HAS_EXPAT
ARABICA_HAS_LIBXML2
ARABICA_HAS_XERCES
ARABICA_USE_GARDEN
ARABICA_HAS_XML_PARSER
ARABICA_HAS_MBSTATE_T
ARABICA_HAS_STD_WSTRING
ARABICA_CHECK_CODECVT_SPECIALISATIONS
ARABICA_CHECK_SOCKETS
ARABICA_HAS_BOOST([1.33])
ARABICA_WANT_DOM
ARABICA_WANT_TESTS

HAS_LIB_ELEPHANT

AC_CONFIG_HEADERS([include/SAX/ArabicaConfig.hpp])
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([arabica.pc])
AC_CONFIG_FILES([include/Makefile])
AC_CONFIG_FILES([src/Makefile])
AC_CONFIG_FILES([examples/Makefile])
AC_CONFIG_FILES([examples/Utils/Makefile])
AC_CONFIG_FILES([examples/Taggle/Makefile])
AC_CONFIG_FILES([examples/SAX/Makefile])
AC_CONFIG_FILES([examples/DOM/Makefile])
AC_CONFIG_FILES([examples/XPath/Makefile])
AC_CONFIG_FILES([examples/XSLT/Makefile])
AC_CONFIG_FILES([tests/Makefile])
AC_CONFIG_FILES([tests/CppUnit/Makefile])
AC_CONFIG_FILES([tests/Utils/Makefile])
AC_CONFIG_FILES([tests/Taggle/Makefile])
AC_CONFIG_FILES([tests/SAX/Makefile])
AC_CONFIG_FILES([tests/DOM/Makefile])
AC_CONFIG_FILES([tests/DOM/test_path.hpp])
AC_CONFIG_FILES([tests/XPath/Makefile])
AC_CONFIG_FILES([tests/XSLT/Makefile])
AC_CONFIG_FILES([tests/XSLT/test_path.hpp])

AC_OUTPUT

ARABICA_PREFIX_CONFIG_H([ARABICA],
                        [include/SAX/ArabicaConfig.hpp])
