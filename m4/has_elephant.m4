AC_DEFUN([HAS_LIB_ELEPHANT],
         [ AC_ARG_WITH([elephant],
	 AS_HELP_STRING([--with-elephant=PREFIX],[Specify elephant library location]),
	 [], 
         [with_elephant=yes])

  ELEPHANT_CFLAGS=
  ELEPHANT_LIBS=
  if test $with_elephant != no; then
    if test $with_elephant != yes; then
      elephant_possible_path="$with_elephant"
    else
      elephant_possible_path="/usr/local /usr /opt /var" 
    fi
    AC_MSG_CHECKING([for Elephant headers])
    elephant_save_CXXFLAGS="$CXXFLAGS"
    elephant_found=no
    for elephant_path_tmp in $elephant_possible_path ; do
      CXXFLAGS="$CXXFLAGS -I$elephant_path_tmp/include"
      AC_COMPILE_IFELSE([@%:@include <elephant/memorymonitor.h>],
                        [ELEPHANT_CFLAGS="-I$elephant_path_tmp/include"
                         ELEPHANT_LIBS="-L$elephant_path_tmp/lib"
                         elephant_found=yes]
                        [])
      CXXFLAGS="$elephant_save_CXXFLAGS"
      if test $elephant_found = yes; then
        break;
      fi
    done                
    AC_MSG_RESULT($elephant_found)
    if test $elephant_found = yes; then
      AC_MSG_CHECKING([for elephant::MemoryMonitorHolder in -lelephant])
      elephant_save_LIBS="$LDFLAGS"
      CXXFLAGS="$CXXFLAGS $ELEPHANT_CFLAGS"
      LIBS="$LIBS $ELEPHANT_LIBS -lelephant"
      AC_LINK_IFELSE([AC_LANG_PROGRAM([[#include <elephant/memorymonitorholder.h>]],
                                     [[elephant::MemoryMonitorHolder().Instance().AddObserver(0)]])],
                     [ ELEPHANT_LIBS="$ELEPHANT_LIBS -lelephant"
                       elephant_found=yes],
                     [ elephant_found=no])
      CXXFLAGS="$elephant_save_CXXFLAGS"
      LIBS="$elephant_save_LIBS"
      AC_MSG_RESULT($elephant_found)
      LIBS="$elephant_save_LIBS"
      if test "$elephant_found" = "yes"; then
        HAVE_ELEPHANT=1
      fi
      AC_DEFINE([HAVE_ELEPHANT], ,[define to use the Elephant memory leak detector])
      AC_SUBST([ELEPHANT_INCLUDES], $ELEPHANT_CFLAGS)
      AC_SUBST([ELEPHANT_LIBS], $ELEPHANT_LIBS)
    fi  
  fi
])
