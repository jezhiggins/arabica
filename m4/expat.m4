AC_DEFUN([ARABICA_HAS_EXPAT],
[ AC_ARG_WITH(expat,
	      [  --with-expat=PREFIX     Use system expat library],
	      , with_expat=yes)

  AM_CONDITIONAL(EXPAT_INSTALLED, test $with_expat != no)

  EXPAT_CFLAGS=
  EXPAT_LIBS=
  if test $with_expat != no; then
    if test $with_expat != yes; then
      expat_possible_path="$with_expat"
    else
      expat_possible_path="/usr /usr/local /opt /var" 
    fi
    AC_MSG_CHECKING([for expat headers])
    expat_save_CXXFLAGS="$CXXFLAGS"
    expat_found=no
    for expat_path_tmp in $expat_possible_path ; do
      CXXFLAGS="$CXXFLAGS -I$expat_path_tmp/include"
      AC_COMPILE_IFELSE([AC_LANG_SOURCE(@%:@include <expat.h>)],
                            [AS_VAR_SET(expat_found, yes)],
                            [AS_VAR_SET(expat_found, no)])
      if test $expat_found = yes; then
        EXPAT_CFLAGS="-I$expat_path_tmp/include"
        EXPAT_LIBS="-L$expat_path_tmp/lib"
        break;
      fi
      CXXFLAGS="$expat_save_CXXFLAGS"
    done                
    CXXFLAGS="$expat_save_CXXFLAGS"
    AC_MSG_RESULT($expat_found)
    if test $expat_found = yes; then
      AC_CHECK_LIB(expat, XML_ParserCreate,
		     [ EXPAT_LIBS="$EXPAT_LIBS -lexpat"
		       expat_found=yes ],
		     [ expat_found=no ],
		     "$EXPAT_LIBS")
      if test $expat_found = yes; then
        HAVE_EXPAT=1
      fi
    fi  
  fi
])
