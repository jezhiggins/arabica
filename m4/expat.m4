AC_DEFUN([ARABICA_HAS_EXPAT],
[ 
  AC_ARG_WITH([expat],
	      AS_HELP_STRING([--with-expat=PREFIX],[Specify expat library location]),
	      [], 
              [with_expat=yes])

  EXPAT_CFLAGS=
  EXPAT_LIBS=
  if test $with_expat != no; then
    if test $with_expat != yes; then
      expat_possible_path="$with_expat"
    else
      expat_possible_path="/usr/local /usr /opt /var" 
    fi
    AC_MSG_CHECKING([for expat headers])
    expat_save_CXXFLAGS="$CXXFLAGS"
    expat_found=no
    for expat_path_tmp in $expat_possible_path ; do
      CXXFLAGS="$CXXFLAGS -I$expat_path_tmp/include"
      AC_COMPILE_IFELSE([@%:@include <expat.h>],
                        [EXPAT_CFLAGS="-I$expat_path_tmp/include"
                         EXPAT_LIBS="-L$expat_path_tmp/lib"
                         expat_found=yes],
                        [expat_found=no])
      CXXFLAGS="$expat_save_CXXFLAGS"
      if test $expat_found = yes; then
        break;
      fi
    done                
    AC_MSG_RESULT($expat_found)
    if test $expat_found = yes; then
      AC_CHECK_LIB([expat], 
                   [XML_ParserCreate],
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
