/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2010 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id: header 297205 2010-03-30 21:09:07Z johannes $ */

#ifndef PHP_PHP_JSON_GBK_H
#define PHP_PHP_JSON_GBK_H

extern zend_module_entry php_json_gbk_module_entry;
#define phpext_php_json_gbk_ptr &php_json_gbk_module_entry

#ifdef PHP_WIN32
#define PHP_PHP_JSON_GBK_API __declspec(dllexport)
#else
#define PHP_PHP_JSON_GBK_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINFO_FUNCTION(php_json_gbk);

static PHP_FUNCTION(gbk_json_decode);

#ifdef ZTS
#define PHP_JSON_GBK_G(v) TSRMG(php_json_gbk_globals_id, zend_php_json_gbk_globals *, v)
#else
#define PHP_JSON_GBK_G(v) (php_json_gbk_globals.v)
#endif


PHP_PHP_JSON_GBK_API void php_gbk_json_decode(zval *return_value, char *str, int str_len, zend_bool assoc TSRMLS_DC);

#endif	/* PHP_PHP_JSON_GBK_H */
/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
