AC_DEFUN([ARABICA_HAS_XERCES],
[ AC_ARG_WITH(xerces,
	      [  --with-xerces=PREFIX     Specify xerces library location],
	      , with_xerces=yes)

  AM_CONDITIONAL(XERCES_INSTALLED, test $with_xerces != no)

  XERCES_CFLAGS=
  XERCES_LIBS=
  if test $with_xerces != no; then
    if test $with_xerces != yes; then
      xerces_possible_path="$with_xerces"
    else
      xerces_possible_path="/usr /usr/local /opt /var" 
    fi
    AC_MSG_CHECKING([for Xerces headers])
    xerces_save_CXXFLAGS="$CXXFLAGS"
    xerces_found=no
    for xerces_path_tmp in $xerces_possible_path ; do
      CXXFLAGS="$CXXFLAGS -I$xerces_path_tmp/include"
      AC_COMPILE_IFELSE([AC_LANG_SOURCE(@%:@include <xercesc/sax2/SAX2XMLReader.hpp>)],
                            [AS_VAR_SET(xerces_found, yes)],
                            [AS_VAR_SET(xerces_found, no)])
      if test $xerces_found = yes; then
        XERCES_CFLAGS="-I$xerces_path_tmp/include"
        XERCES_LIBS="-L$xerces_path_tmp/lib -lxerces-c"
        break;
      fi
      CXXFLAGS="$xerces_save_CXXFLAGS"
    done                
    CXXFLAGS="$xerces_save_CXXFLAGS"
    AC_MSG_RESULT($xerces_found)
    if test $xerces_found = yes; then
      AC_MSG_CHECKING([for XMLPlatformUtils::Initialize in -lxerces-c])
      CXXFLAGS="$CXXFLAGS $XERCES_CFLAGS"
      xerces_save_LIBS="$LIBS"
      LIBS="$LIBS $XERCES_LIBS"
      AC_LINK_IFELSE([AC_LANG_PROGRAM([[#include <xercesc/util/PlatformUtils.hpp>]],
                                     [[XERCES_CPP_NAMESPACE::XMLPlatformUtils::Initialize()]])],
                     [AS_VAR_SET(xerces_found, yes)],
                     [AS_VAR_SET(xerces_found, no)])
      AC_MSG_RESULT($xerces_found)
      if test $xerces_found = yes; then
        HAVE_XERCES=1
      fi
      CXXFLAGS="$xerces_save_CXXFLAGS"
      LIBS="$xerces_save_LIBS"
    fi  
  fi
])
