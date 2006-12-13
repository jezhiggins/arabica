AC_DEFUN([ARABICA_IS_MINGW],
[
  AC_MSG_CHECKING([for MinGW])
  if test x$target_os = xmingw32; then
    is_mingw="yes"
  else
    is_mingw="no"
  fi 
  if test $is_mingw = yes; then
    AC_DEFINE(ARABICA_USE_WINSOCK, ,[defined for Windows builds using Winsock rather than BSD-style sockets])
    PARSER_LIBS="$PARSER_LIBS -lwsock32"
  fi
  AC_MSG_RESULT($is_mingw)
])
