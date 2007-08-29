AC_DEFUN([ARABICA_SELECT_XML_PARSER],
[
  AC_ARG_WITH([parser], 
              AS_HELP_STRING([--with-parser=expat|libxml2|xerces|garden],
                             [Specify a particular parser library]),
              , )

  if test "$with_parser" != ""; then
    if test "$with_parser" = "expat"; then 
      with_libxml2=no
      with_xerces=no
      with_garden=no
      AC_MSG_NOTICE([[--with-parser=expat specified]]) 
    elif test "$with_parser" = "libxml2"; then 
      with_expat=no
      with_xerces=no
      with_garden=no
      AC_MSG_NOTICE([[--with-parser=libxml2 specified]]) 
    elif test "$with_parser" = "xerces"; then 
      with_expat=no
      with_libxml2=no
      with_garden=no
      AC_MSG_NOTICE([[--with-parser=xerces specified]]) 
    elif test "$with_parser" = "garden"; then 
      with_garden=yes
      with_expat=no
      with_libxml2=no
      with_xerces=no
      AC_MSG_NOTICE([[--with-parser=garden specified]]) 
    else
      AC_MSG_ERROR([[Unrecognised --with-parser parameter]])
    fi
  else
    if test "$with_expat" != ""; then
      if test "$with_expat" != "no"; then
        with_libxml2=no
        with_xerces=no
        with_garden=no
        AC_MSG_NOTICE([[--with-expat specified]]) 
      fi
    elif test "$with_libxml2" != ""; then
      if test "$with_libxml2" != "no"; then
        with_expat=no
        with_xerces=no
        with_garden=no
        AC_MSG_NOTICE([[--with-libxml2 specified]]) 
      fi
    elif test "$with_xerces" != ""; then
      if test "$with_xerces" != "no"; then
        with_expat=no
        with_libxml2=no
        with_garden=no
        AC_MSG_NOTICE([[--with-xerces specified]]) 
      fi
    elif test "$with_garden" != ""; then
      if test "$with_garden" != "no"; then
        with_expat=no
        with_libxml2=no
        with_xerces=no
        AC_MSG_NOTICE([[--with-garden specified]]) 
      fi
    fi
  fi
])

