dnl $Id$
dnl config.m4 for extension php_json_gbk

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(php_json_gbk, for php_json_gbk support,
dnl Make sure that the comment is aligned:
dnl [  --with-php_json_gbk             Include php_json_gbk support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(php_json_gbk, whether to enable php_json_gbk support,
dnl Make sure that the comment is aligned:
[  --enable-php_json_gbk           Enable php_json_gbk support])

if test "$PHP_PHP_JSON_GBK" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-php_json_gbk -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/php_json_gbk.h"  # you most likely want to change this
  dnl if test -r $PHP_PHP_JSON_GBK/$SEARCH_FOR; then # path given as parameter
  dnl   PHP_JSON_GBK_DIR=$PHP_PHP_JSON_GBK
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for php_json_gbk files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PHP_JSON_GBK_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PHP_JSON_GBK_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the php_json_gbk distribution])
  dnl fi

  dnl # --with-php_json_gbk -> add include path
  dnl PHP_ADD_INCLUDE($PHP_JSON_GBK_DIR/include)

  dnl # --with-php_json_gbk -> check for lib and symbol presence
  dnl LIBNAME=php_json_gbk # you may want to change this
  dnl LIBSYMBOL=php_json_gbk # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PHP_JSON_GBK_DIR/lib, PHP_JSON_GBK_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PHP_JSON_GBKLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong php_json_gbk lib version or lib not found])
  dnl ],[
  dnl   -L$PHP_JSON_GBK_DIR/lib -lm -ldl
  dnl ])
  dnl
  dnl PHP_SUBST(PHP_JSON_GBK_SHARED_LIBADD)

  PHP_NEW_EXTENSION(php_json_gbk, php_json_gbk.c, $ext_shared)
fi
