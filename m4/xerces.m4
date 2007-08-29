AC_DEFUN([ARABICA_HAS_XERCES],
[ AC_ARG_WITH([xerces],
	      AS_HELP_STRING([--with-xerces=PREFIX],[Specify xerces library location]),
	      [], 
              [with_xerces=yes])

  XERCES_CFLAGS=
  XERCES_LIBS=
  if test $with_xerces != no; then
    if test $with_xerces != yes; then
      xerces_possible_path="$with_xerces"
    else
      xerces_possible_path="/usr/local /usr /opt /var" 
    fi
    AC_MSG_CHECKING([for Xerces headers])
    xerces_save_CXXFLAGS="$CXXFLAGS"
    xerces_found=no
    for xerces_path_tmp in $xerces_possible_path ; do
      CXXFLAGS="$CXXFLAGS -I$xerces_path_tmp/include"
      AC_COMPILE_IFELSE([@%:@include <xercesc/sax2/SAX2XMLReader.hpp>],
                        [XERCES_CFLAGS="-I$xerces_path_tmp/include"
                         XERCES_LIBS="-L$xerces_path_tmp/lib"
                         xerces_found=yes]
                        [])
      CXXFLAGS="$xerces_save_CXXFLAGS"
      if test $xerces_found = yes; then
        break;
      fi
    done                
    AC_MSG_RESULT($xerces_found)
    if test $xerces_found = yes; then
      AC_MSG_CHECKING([for XMLPlatformUtils::Initialize in -lxerces-c])
      xerces_save_LIBS="$LDFLAGS"
      CXXFLAGS="$CXXFLAGS $XERCES_CFLAGS"
      LIBS="$LIBS $XERCES_LIBS -lxerces-c"
      AC_LINK_IFELSE([AC_LANG_PROGRAM([[#include <xercesc/util/PlatformUtils.hpp>]],
                                     [[XERCES_CPP_NAMESPACE::XMLPlatformUtils::Initialize()]])],
                     [ XERCES_LIBS="$XERCES_LIBS -lxerces-c"
                       xerces_found=yes],
                     [ xerces_found=no])
      CXXFLAGS="$xerces_save_CXXFLAGS"
      LIBS="$xerces_save_LIBS"
      AC_MSG_RESULT($xerces_found)
      if test $xerces_found = yes; then
        HAVE_XERCES=1
      fi
      LIBS="$xerces_save_LIBS"
    fi  
  fi
])
