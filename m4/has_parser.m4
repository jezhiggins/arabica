
AC_DEFUN([ARABICA_HAS_XML_PARSER],
[
  if test "$HAVE_EXPAT" = "1"; then
    AC_DEFINE([USE_EXPAT], ,[define to build against Expat])
    AC_SUBST([PARSER_HEADERS], $EXPAT_CFLAGS)
    AC_SUBST([PARSER_LIBS], $EXPAT_LIBS)
  elif test "$HAVE_LIBXML2" = "1"; then
    AC_DEFINE(USE_LIBXML2, ,[define to build against LibXML2])
    AC_SUBST([PARSER_HEADERS], $LIBXML2_CFLAGS)
    AC_SUBST([PARSER_LIBS], $LIBXML2_LIBS)
  elif test "$HAVE_XERCES" = "1"; then
    AC_DEFINE(USE_XERCES, ,[define to build against Xerces])
    AC_SUBST([PARSER_HEADERS], $XERCES_CFLAGS)
    AC_SUBST([PARSER_LIBS], $XERCES_LIBS)
  elif test "$USE_GARDEN" = "1"; then
    AC_DEFINE(USE_GARDEN, ,[define to build using Garden])
    AC_SUBST([PARSER_HEADERS], [])
    AC_SUBST([PARSER_LIBS], [])
  else 
    AC_MSG_ERROR([[Cannot find an XML parser library.  Arabica needs one of Expat, LibXML2 or Xerces]])
  fi
])
