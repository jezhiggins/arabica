AC_DEFUN([ARABICA_HAS_STD_WSTRING],
[
  AC_MSG_CHECKING([for std::wstring support])
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <iostream>]],
                                     [[std::wcout << std::wstring(L"test");]])],
                    [wchar_t_available=yes],
                    [wchar_t_available=no])
  AC_MSG_RESULT([$wchar_t_available])
  if test $wchar_t_available = no; then
    AC_DEFINE([ARABICA_NO_WCHAR_T], ,[disables wchar_t])
  fi
  AM_CONDITIONAL([HAS_STD_WSTRING], [test "$wchar_t_available" = "yes"])
])
