AC_DEFUN([ARABICA_WANT_DOM],
[
  AC_ARG_WITH([dom],
              AS_HELP_STRING([--with-dom=yes|no],
              [Control whether DOM tests and examples are built.  --with-dom=no to disable]),
              [if test "$withval" = "no"; then
                 want_dom="no"
               else
                 want_dom="yes"
               fi],
              [want_dom="yes"])
  if test x$want_dom = xno; then
    AC_MSG_NOTICE([[DOM disabled.  DOM components will not be built.]])
  fi
  AM_CONDITIONAL([WANT_DOM], [test "$want_dom" = "yes"])
  if test "$want_dom" = "yes"; then
    if test "$boost_is_available" = "yes"; then
      want_xpath="yes"
    fi
  fi
  if test "$want_xpath" != "yes"; then
    AC_MSG_NOTICE([[XPath disabled.  XPath components will not be built.]])
  fi
  AM_CONDITIONAL([WANT_XPATH], [test "$want_xpath" = "yes"])
])
