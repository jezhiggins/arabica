AC_INIT(src/arabica.cpp)
AC_CONFIG_HEADERS(include/SAX/ArabicaConfig.h)

AM_INIT_AUTOMAKE(arabica, Sept2006)

AC_PROG_CXX
AM_PROG_LIBTOOL

AC_LANG_CPLUSPLUS

ARABICA_HAS_BOOST([1.32])
ARABICA_HAS_EXPAT
ARABICA_HAS_LIBXML2
ARABICA_HAS_XERCES
ARABICA_HAS_XML_PARSER
ARABICA_HAS_STD_WSTRING
ARABICA_CHECK_CODECVT_SPECIALISATIONS

AC_OUTPUT(Makefile \
          arabica.pc \
          src/Makefile \
          test/Makefile \
          test/DOM/Makefile \
          test/SAX2DOM/Makefile \
          test/XPath/Makefile \
          examples/Makefile \
          examples/SAX/Makefile \
          examples/DOM/Makefile \
          examples/Utils/Makefile \
          examples/XPath/Makefile 
)

