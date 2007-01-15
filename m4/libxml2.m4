AC_DEFUN([ARABICA_HAS_LIBXML2],
[ AC_ARG_WITH(libxml2,
	      [  --with-libxml2=PREFIX     Specify libxml2 library location],
	      , with_libxml2=yes)

  AM_CONDITIONAL(LIBXML2_INSTALLED, test $with_libxml2 != no)

  LIBXML2_CFLAGS=
  LIBXML2_LIBS=
  if test $with_libxml2 != no; then
    if test $with_libxml2 != yes; then
      libxml2_possible_path="$with_libxml2"
    else
      libxml2_possible_path="/usr /usr/local /opt /var" 
    fi
    AC_MSG_CHECKING([for libxml2 headers])
    libxml2_save_CXXFLAGS="$CXXFLAGS"
    libxml2_found=no
    for libxml2_path_tmp in $libxml2_possible_path ; do
      CXXFLAGS="$CXXFLAGS -I$libxml2_path_tmp/include"
      AC_COMPILE_IFELSE([AC_LANG_SOURCE(@%:@include <libxml/parser.h>)],
                            [AS_VAR_SET(libxml2_found, yes)],
                            [AS_VAR_SET(libxml2_found, no)])
      if test $libxml2_found = yes; then
        LIBXML2_CFLAGS="-I$libxml2_path_tmp/include/libxml2"
        LIBXML2_LIBS="-L$libxml2_path_tmp/lib"
        break;
      fi
      CXXFLAGS="$libxml2_save_CXXFLAGS"
    done                
    CXXFLAGS="$libxml2_save_CXXFLAGS"
    AC_MSG_RESULT($libxml2_found)
    if test $libxml2_found = yes; then
      AC_CHECK_LIB(xml2, xmlInitParser,
		     [ LIBXML2_LIBS="$LIBXML2_LIBS -lxml2"
		       libxml2_found=yes ],
		     [ libxml2_found=no ],
		     "$LIBXML2_LIBS")
      if test $libxml2_found = yes; then
        HAVE_LIBXML2=1
      fi
    fi  
  fi
])
