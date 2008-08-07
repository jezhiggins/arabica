AC_DEFUN([ARABICA_WANT_TESTS],
[
  AC_ARG_WITH([tests],
              AS_HELP_STRING([--with-tests=yes|no],
              [Control whether make check runs tests after they are built.  --with-tests=no to disable]),
              [if test "$withval" = "no"; then
                 want_tests="no"
               else
                 want_tests="yes"
               fi],
              [want_tests="yes"])
  if test "$want_tests" = "no"; then
    AC_MSG_NOTICE([[Tests disabled.  make check will build the tests but not run them.]])
  fi
  if test "$want_tests" = yes; then
    if test "$cross_compiling" = "maybe"; then
      AC_MSG_NOTICE([[Are we cross-compiling?  If so, consider --want-tests=no, which means make check will build the tests but not run them.]])
    fi
    if test "$cross_compiling" = "yes"; then
      AC_MSG_NOTICE([[Tests disabled because cross-compiling.  make check will build the tests but not run them.]])
      want_tests="no"
    fi
  fi
  AM_CONDITIONAL([WANT_TESTS], [test "$want_tests" = "yes"])
])
