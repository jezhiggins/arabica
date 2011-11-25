dnl @synopsis ARABICA_PREFIX_CONFIG_H [(PREFIX [,ORIG-HEADER])]
dnl
dnl takes the usual config.h generated header file; looks for each of
dnl the generated "#define SOMEDEF" lines, and prefixes the defined
dnl name (ie. makes it "#define PREFIX_SOMEDEF". The result overwrites
dnl the input header. The PREFIX is converted to uppercase for the 
dnl conversions. If PREFIX is absent, $PACKAGE will be assumed. If 
dnl the ORIG-HEADER is absent, "config.h" will be assumed. 
dnl
dnl In most cases, the configure.in will contain a line saying
dnl
dnl         AC_CONFIG_HEADER(config.h)
dnl
dnl somewhere *before* AC_OUTPUT and a simple line saying
dnl
dnl        AC_PREFIX_CONFIG_HEADER
dnl
dnl somewhere *after* AC_OUTPUT.
dnl
dnl @author Guido U. Draheim <guidod@gmx.de>, Jez Higgins <jez@jezuk.co.uk>
dnl @version 2006-10-13, 2011-11-25
dnl @license GPLWithACException

AC_DEFUN([ARABICA_PREFIX_CONFIG_H],
[changequote(<<, >>)dnl
ac_prefix_conf_PKG=`echo ifelse($1, , $PACKAGE, $1)`
ac_prefix_conf_PRE=`echo $ac_prefix_conf_PKG | tr 'abcdefghijklmnopqrstuvwxyz-' 'ABCDEFGHIJKLMNOPQRSTUVWXYZ_'`
ac_prefix_conf_PRE=`echo $ac_prefix_conf_PRE | sed -e '/^[0-9]/s/^/_/'`
ac_prefix_conf_INP=`echo ifelse($2, , config.h, $2)`
ac_prefix_conf_OUT=`echo $ac_prefix_conf_INP.out`
ac_prefix_conf_DEF=`echo _$ac_prefix_conf_OUT | tr 'abcdefghijklmnopqrstuvwxyz./,-' 'ABCDEFGHIJKLMNOPQRSTUVWXYZ____'`
changequote([, ])dnl
if test -z "$ac_prefix_conf_PKG" ; then
   AC_MSG_ERROR([no prefix for _PREFIX_CONFIG_H])
else
  AC_MSG_RESULT(Massaging $ac_prefix_conf_INP to add prefix $ac_prefix_conf_PRE)
  if test -f $ac_prefix_conf_INP ; then
    echo '#ifndef '$ac_prefix_conf_DEF >$ac_prefix_conf_OUT
    echo '#define '$ac_prefix_conf_DEF' 1' >>$ac_prefix_conf_OUT
    echo ' ' >>$ac_prefix_conf_OUT
    echo /'*' $ac_prefix_conf_OUT. Generated automatically at end of configure. '*'/ >>$ac_prefix_conf_OUT

    echo 's/#undef  */#undef '$ac_prefix_conf_PRE'_/' >conftest.sed
    echo 's/#define  *\([A-Za-z0-9_]*\)\(.*\)/#ifndef '$ac_prefix_conf_PRE"_\\1 \\" >>conftest.sed
    echo '#define '$ac_prefix_conf_PRE"_\\1 \\2 \\" >>conftest.sed
    echo '#endif/' >>conftest.sed
    sed -f conftest.sed $ac_prefix_conf_INP >>$ac_prefix_conf_OUT
    echo ' ' >>$ac_prefix_conf_OUT
    echo '/*' $ac_prefix_conf_DEF '*/' >>$ac_prefix_conf_OUT
    echo '#endif' >>$ac_prefix_conf_OUT
    rm $ac_prefix_conf_INP
    mv $ac_prefix_conf_OUT $ac_prefix_conf_INP
  else
    AC_MSG_ERROR([input file $ac_prefix_conf_IN does not exist, dnl
    skip generating $ac_prefix_conf_OUT])
  fi
  rm -f conftest.*
fi])

