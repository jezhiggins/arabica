AC_INIT(src/arabica.cpp)
AC_CANONICAL_SYSTEM
AC_CONFIG_HEADERS(include/SAX/ArabicaConfig.h)

AM_INIT_AUTOMAKE(arabica, Sept2006-3)

AC_PROG_CXX
AM_PROG_LIBTOOL

AC_LANG_CPLUSPLUS


ARABICA_HAS_BOOST([1.32])
ARABICA_WANT_DOM
ARABICA_SELECT_XML_PARSER
ARABICA_HAS_EXPAT
ARABICA_HAS_LIBXML2
ARABICA_HAS_XERCES
ARABICA_USE_GARDEN
ARABICA_HAS_XML_PARSER
ARABICA_HAS_STD_WSTRING
ARABICA_CHECK_CODECVT_SPECIALISATIONS
ARABICA_CHECK_SOCKETS

AC_OUTPUT(Makefile \
          arabica.pc \
          src/Makefile \
          tests/Makefile \
          tests/DOM/Makefile \
          tests/SAX2DOM/Makefile \
          tests/XPath/Makefile \
          examples/Makefile \
          examples/SAX/Makefile \
          examples/DOM/Makefile \
          examples/Utils/Makefile \
          examples/XPath/Makefile 
)

