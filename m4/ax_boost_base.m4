
AC_DEFUN([ARABICA_HAS_BOOST],
[
    AC_ARG_WITH([boost],
                AS_HELP_STRING([--with-boost=DIR],
                [Specify the root directory for Boost library.  --with-boost=no to disable]),
                [
                if test "$withval" = "no"; then
                            want_boost="no"
                elif test "$withval" = "yes"; then
                    want_boost="yes"
                    ac_boost_path=""
                else
                                want_boost="yes"
                        ac_boost_path="$withval"
                        fi
                ],
                [want_boost="yes"])

        if test "x$want_boost" = "xyes"; then
        AC_REQUIRE([AC_PROG_CC])
                boost_lib_version_req=ifelse([$1], ,1.20.0,$1)
                boost_lib_version_req_shorten=`expr $boost_lib_version_req : '\([[0-9]]*\.[[0-9]]*\)'`
                boost_lib_version_req_major=`expr $boost_lib_version_req : '\([[0-9]]*\)'`
                boost_lib_version_req_minor=`expr $boost_lib_version_req : '[[0-9]]*\.\([[0-9]]*\)'`
                boost_lib_version_req_sub_minor=`expr $boost_lib_version_req : '[[0-9]]*\.[[0-9]]*\.\([[0-9]]*\)'`
                if test "x$boost_lib_version_req_sub_minor" = "x" ; then
                        boost_lib_version_req_sub_minor="0"
        fi
                WANT_BOOST_VERSION=`expr $boost_lib_version_req_major \* 100000 \+  $boost_lib_version_req_minor \* 100 \+ $boost_lib_version_req_sub_minor`
                AC_MSG_CHECKING(for boostlib >= $boost_lib_version_req)
                succeeded=no

                dnl first we check the system location for boost libraries
                dnl this location ist chosen if boost libraries are installed with the --layout=system option
                dnl or if you install boost with RPM
                if test "$ac_boost_path" != ""; then
                        BOOST_CPPFLAGS="-I$ac_boost_path"
                else
                        for ac_boost_path_tmp in /usr/include /usr/local/include /opt /opt/include ; do
                                if test -d "$ac_boost_path_tmp/boost" && test -r "$ac_boost_path_tmp/boost"; then
                                        BOOST_CPPFLAGS="-I$ac_boost_path_tmp"
                                        break;
                                fi
                        done
                fi

                CPPFLAGS_SAVED="$CPPFLAGS"
                CPPFLAGS="$CPPFLAGS $BOOST_CPPFLAGS"
                export CPPFLAGS

        AC_LANG_PUSH(C++)
        AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
@%:@include <boost/version.hpp>
]],
       [[
#if BOOST_VERSION >= $WANT_BOOST_VERSION
// Everything is okay
#else
#  error Boost version is too old
#endif

                ]])],
        [
         AC_MSG_RESULT(yes)
                 succeeded=yes
                 found_system=yes
         ifelse([$2], , :, [$2])
       ],
       [
       ])
       AC_LANG_POP([C++])
                dnl if we found no boost with system layout we search for boost libraries
                dnl built and installed without the --layout=system option or for a staged(not installed) version
                if test "x$succeeded" != "xyes"; then
                        _version=0
                        if test "$ac_boost_path" != ""; then
                BOOST_LDFLAGS="-L$ac_boost_path/lib"
                                if test -d "$ac_boost_path" && test -r "$ac_boost_path"; then
                                        for i in `ls -d $ac_boost_path/include/boost-* 2>/dev/null`; do
                                                _version_tmp=`echo $i | sed "s#$ac_boost_path##" | sed 's/\/include\/boost-//' | sed 's/_/./'`
                                                V_CHECK=`expr $_version_tmp \> $_version`
                                                if test "$V_CHECK" = "1" ; then
                                                        _version=$_version_tmp
                                                fi
                                                VERSION_UNDERSCORE=`echo $_version | sed 's/\./_/'`
                                                BOOST_CPPFLAGS="-I$ac_boost_path/include/boost-$VERSION_UNDERSCORE"
                                        done
                                fi
                        else
                                for ac_boost_path in /usr /usr/local /opt ; do
                                        if test -d "$ac_boost_path" && test -r "$ac_boost_path"; then
                                                for i in `ls -d $ac_boost_path/include/boost-* 2>/dev/null`; do
                                                        _version_tmp=`echo $i | sed "s#$ac_boost_path##" | sed 's/\/include\/boost-//' | sed 's/_/./'`
                                                        V_CHECK=`expr $_version_tmp \> $_version`
                                                        if test "$V_CHECK" = "1" ; then
                                                                _version=$_version_tmp
                                                                best_path=$ac_boost_path
                                                        fi
                                                done
                                        fi
                                done

                                VERSION_UNDERSCORE=`echo $_version | sed 's/\./_/'`
                                BOOST_CPPFLAGS="-I$best_path/include/boost-$VERSION_UNDERSCORE"

                        if test "x$BOOST_ROOT" != "x"; then
                    if test -d "$BOOST_ROOT" && test -r "$BOOST_ROOT" && test -d "$BOOST_ROOT/stage/lib" && test -r "$BOOST_ROOT/stage/lib"; then
                                                version_dir=`expr //$BOOST_ROOT : '.*/\(.*\)'`
                                                stage_version=`echo $version_dir | sed 's/boost_//' | sed 's/_/./g'`
                                                stage_version_shorten=`expr $stage_version : '\([[0-9]]*\.[[0-9]]*\)'`
                                                V_CHECK=`expr $stage_version_shorten \>\= $_version`
                                                if test "$V_CHECK" = "1" ; then
                                                        AC_MSG_NOTICE(We will use a staged boost library from $BOOST_ROOT)
                                                        BOOST_CPPFLAGS="-I$BOOST_ROOT"
                                                fi
                                        fi
                        fi
                        fi

                        CPPFLAGS="$CPPFLAGS $BOOST_CPPFLAGS"
                        export CPPFLAGS

            AC_LANG_PUSH(C++)
            AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
@%:@include <boost/version.hpp>
]],
       [[
#if BOOST_VERSION >= $WANT_BOOST_VERSION
// Everything is okay
#else
#  error Boost version is too old
#endif

                ]])],
        [
         AC_MSG_RESULT(yes ($_version))
                 succeeded=yes
         ifelse([$2], , :, [$2])
       ],
       [
         AC_MSG_RESULT(no ($_version))
         ifelse([$3], , :, [$3])
       ])
        AC_LANG_POP([C++])
                fi

                if test "$succeeded" != "yes" ; then
                        if test "$_version" = "0" ; then
                                AC_MSG_NOTICE([[Could not detect the Boost libraries (version $boost_lib_version_req_shorten or higher).  If you do have Boost installed, then check your version number looking in <boost/version.hpp>. ]])
                        else
                                AC_MSG_NOTICE('Your Boost libraries seems to old (version $_version).  We need at least $boost_lib_version_shorten')
                        fi
                        AC_MSG_NOTICE([[Arabica will build, but some features will not be available]]) 
                else
                       AC_SUBST(BOOST_CPPFLAGS)
                        AC_DEFINE(HAVE_BOOST,,[define if the Boost library is available])
                fi
        CPPFLAGS="$CPPFLAGS_SAVED"
        else
                        AC_MSG_NOTICE([[Not searching for Boost.  Arabica will build, but some features will not be available]]) 
        fi
        if test "$succeeded" = "yes"; then
          boost_is_available=yes
        else
          boost_is_available=no
        fi
])


