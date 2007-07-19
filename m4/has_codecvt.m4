AC_DEFUN([ARABICA_CHECK_CODECVT_SPECIALISATIONS],
[
  if test $wchar_t_available = yes; then
    AC_MSG_CHECKING([for std::codecvt specialisations])
    AC_LINK_IFELSE([AC_LANG_PROGRAM([[#include <codecvt>]],
                             [[std::codecvt<char, wchar_t, std::mbstate_t> test;]])],
                    [codecvt_available=yes],
                    [codecvt_available=no])
    AC_MSG_RESULT([$codecvt_available])
    if test $codecvt_available = yes; then
      AC_DEFINE([ARABICA_NO_CODECVT_SPECIALISATIONS], [], [defined if we don't need extra codecvt template specialisations])
    fi
  fi
])
