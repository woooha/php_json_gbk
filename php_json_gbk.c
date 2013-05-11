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

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "ext/standard/php_smart_str.h"
#include "gbk_JSON_parser.h"
#include "php_php_json_gbk.h"

/* True global resources - no need for thread safety here */
static int le_php_json_gbk;

/* {{{ php_json_gbk_functions[]
 *
 * Every user visible function must have an entry in php_json_gbk_functions[].
 */
zend_function_entry php_json_gbk_functions[] = {
	PHP_FE(gbk_json_decode, NULL)
	{NULL, NULL, NULL}	/* Must be the last line in php_json_gbk_functions[] */
};
/* }}} */

/* {{{ php_json_gbk_module_entry
 */
zend_module_entry php_json_gbk_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"php_json_gbk",
	php_json_gbk_functions,
	NULL,
	NULL,
	NULL,	/* Replace with NULL if there's nothing to do at request start */
	NULL,	/* Replace with NULL if there's nothing to do at request end */
	NULL,   //PHP_MINFO(php_json_gbk),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PHP_JSON_GBK
ZEND_GET_MODULE(php_json_gbk)
#endif

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(php_json_gbk)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "php_json_gbk support", "enabled");
	php_info_print_table_end();
}
/* }}} */


/* {{{ proto mixed gbk_json_decode(string json [, bool assoc])
	Decodes the JSON representation into a PHP value */
static PHP_FUNCTION(gbk_json_decode)
{
	char *str;
	int str_len;
	zend_bool assoc = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|b", &str, &str_len, &assoc) == FAILURE){
		return;
	}
	if( !str_len ){
		RETURN_NULL();
	}

	php_gbk_json_decode(return_value, str, str_len, assoc TSRMLS_DC);
}
/* }}} */

PHP_PHP_JSON_GBK_API void php_gbk_json_decode(zval *return_value, char *str, int str_len, zend_bool assoc TSRMLS_DC) /* {{{ */
{
	zval *z;

	if( str_len <= 0 ){
		RETURN_NULL();
	}
	
	ALLOC_INIT_ZVAL(z);


	if (gbk_JSON_parser(z, str, str_len, assoc TSRMLS_CC)){
		*return_value = *z;
		FREE_ZVAL(z);
	} else {
		double d;
		int type;
		long p;
		
		if( str_len == 4 ){
			if(!strcasecmp(str, "null")){
				RETURN_NULL();
			} else if( !strcasecmp(str, "true")) {
				RETURN_BOOL(1);
			}
		} else if (str_len == 5 && !strcasecmp(str, "false")) {
			RETURN_BOOL(0);
		}

		if((type = is_numeric_string(str, str_len, &p, &d, 0)) != 0) {
			if( type == IS_LONG){
				RETURN_LONG(p);
			} else if (type == IS_DOUBLE) {
				RETURN_DOUBLE(d);
			}
		}
		RETURN_NULL();
	}
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
