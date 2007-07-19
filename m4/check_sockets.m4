AC_DEFUN([ARABICA_CHECK_SOCKETS],
[
  AC_SEARCH_LIBS([gethostbyname], [nsl])
  AC_SEARCH_LIBS([socket], [socket], [], [
                AC_CHECK_LIB([socket], [socket], [LIBS="-lsocket -lnsl $LIBS"],
                [], [-lnsl])])

  AC_LINK_IFELSE([AC_LANG_PROGRAM([extern "C" char socket();], [socket();])], 
                 [AS_VAR_SET(has_sockets, yes)],
                 [AS_VAR_SET(has_sockets, no)])


  AC_MSG_CHECKING([for winsock])
  if test $has_sockets = yes; then
    AC_MSG_RESULT([skipped])
  fi
  if test $has_sockets = no; then
    winsock_save_LIBS="$LIBS"
    LIBS="$LIBS -lwsock32"
    AC_LINK_IFELSE([AC_LANG_PROGRAM([[#include <winsock.h>]],
                           [[closesocket(1);]])],
                    [AS_VAR_SET(has_winsock, yes)],
                    [AS_VAR_SET(has_winsock, no)])
    LIBS="$winsock_save_LIBS"
    AC_MSG_RESULT($has_winsock)
    if test $has_winsock = yes; then
      AC_DEFINE([ARABICA_USE_WINSOCK], ,[defined for Windows builds using Winsock rather than BSD-style sockets])
      LIBS="-lwsock32 $LIBS"
    fi
  fi
])

