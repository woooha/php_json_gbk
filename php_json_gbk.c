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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_php_json_gbk.h"

/* If you declare any globals in php_php_json_gbk.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(php_json_gbk)
*/

/* True global resources - no need for thread safety here */
static int le_php_json_gbk;

/* {{{ php_json_gbk_functions[]
 *
 * Every user visible function must have an entry in php_json_gbk_functions[].
 */
zend_function_entry php_json_gbk_functions[] = {
	PHP_FE(confirm_php_json_gbk_compiled,	NULL)		/* For testing, remove later. */
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

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("php_json_gbk.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_php_json_gbk_globals, php_json_gbk_globals)
    STD_PHP_INI_ENTRY("php_json_gbk.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_php_json_gbk_globals, php_json_gbk_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_php_json_gbk_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_php_json_gbk_init_globals(zend_php_json_gbk_globals *php_json_gbk_globals)
{
	php_json_gbk_globals->global_value = 0;
	php_json_gbk_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(php_json_gbk)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "php_json_gbk support", "enabled");
	php_info_print_table_end();
	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_php_json_gbk_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_php_json_gbk_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "php_json_gbk", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */

/* {{{ proto mixed gbk_json_decode(string json [, bool assoc])
	Decodes the JSON representation into a PHP value */
static PHP_FUNCTION(gbk_json_decode)
{
	char *parameter;
	int parameter_len;
	zend_bool assoc = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|b", &parameter, &parameter_len, &assoc) == FAILURE){
		return;
	}

	if( !parameter_len ){
		RETURN_NULL();
	}

	php_json_decode(return_value, parameter, parameter_len, assoc TSRMLS_CC);
}
/* }}} */

PHP_PHP_JSON_GBK_API void php_json_decode(zval *return_value, char *buf, int buf_len, zend_bool assoc TSRMLS_DC) /* {{{ */
{
	zval *z;

	if( buf_len <= 0 ){
		RETURN_NULL();
	}

	ALLOC_INIT_ZVAL(z);
	if (JSON_parser(z, buf, buf_len, assoc TSRMLS_CC)){
		*return_value = *z;

		FREE_ZVAL(z);
	} else {
		double d;
		int type;
		long p;

		zval_dtor(z);
		FREE_ZVAL(z);

		if( buf_len == 4 ) {
			if (!strcasecmp(buf, "null")) {
				RETURN_NULL();
			} else if(!strcasecmp(buf, "true")) {
				RETURN_BOOL(1);
			}
		} else if (buf_len == 5 && !strcasecmp(buf, "false")) {
			RETURN_BOOL(0);
		}

		if(( type == is_numeric_string(buf, buf_len, &p, &d, 0)) != 0) {
			if(type == IS_LONG) {
				RETURN_LONG(p);
			} else if(type == IS_DOUBLE) {
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
