
AC_DEFUN([ARABICA_HAS_XML_PARSER],
[
  if test "$HAVE_LIBXML2-$HAVE_EXPAT-$HAVE_XERCES-$USE_GARDEN" = "---"; then
    AC_MSG_ERROR([[Cannot find an XML parser library.  Arabica needs one of Expat, LibXML2 or Xerces]])
  fi

  if test "$HAVE_EXPAT-" != "-"; then
    AC_DEFINE(USE_EXPAT, ,[define to build against Expat])
    PARSER_HEADERS=$EXPAT_CFLAGS
    PARSER_LIBS=$EXPAT_LIBS
  elif test "$HAVE_LIBXML2-" != "-"; then
    AC_DEFINE(USE_LIBXML2, ,[define to build against LibXML2])
    PARSER_HEADERS=$LIBXML2_CFLAGS
    PARSER_LIBS=$LIBXML2_LIBS
  elif test "$HAVE_XERCES-" != "-"; then
    AC_DEFINE(USE_XERCES, ,[define to build against Xerces])
    PARSER_HEADERS=$XERCES_CFLAGS
    PARSER_LIBS=$XERCES_LIBS
  elif test "$USE_GARDEN-" != "-"; then
    AC_DEFINE(USE_GARDEN, ,[define to build using Garden])
    PARSER_HEADERS=
    PARSER_LIBS=
  fi

  AC_SUBST(PARSER_HEADERS)
  AC_SUBST(PARSER_LIBS)
])
