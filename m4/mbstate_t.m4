AC_DEFUN([ARABICA_HAS_MBSTATE_T],
[
  AC_MSG_CHECKING([for std::mbstate_t])
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <cwchar>]],
                                     [[std::mbstate_t mb; return sizeof(mb);]])],
                    [mbstate_available=yes],
		    [mbstate_available=no])
  AC_MSG_RESULT([$mbstate_available])
  if test $mbstate_available = no; then
    AC_DEFINE([ARABICA_NO_STD_MBSTATE_T], ,[no std::mbstate_t])

    AC_MSG_CHECKING([for mbstate_t])
    AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <wchar.h>]],
                                       [[mbstate_t mb; return sizeof(mb);]])],
                      [mbstate_available=yes],
	  	      [mbstate_available=no])
    AC_MSG_RESULT([$mbstate_available])
    if test $mbstate_available = no; then
      AC_DEFINE([ARABICA_NO_MBSTATE_T], ,[no mbstate_t])
    fi
  fi
])