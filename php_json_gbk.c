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
#include <zend_exceptions.h>

ZEND_DECLARE_MODULE_GLOBALS(php_json_gbk)


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

/* {{{ php_php_json_gbk_init_globals
 */

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
	long depth = JSON_PARSER_DEFAULT_DEPTH;
	long options = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|bll", &str, &str_len, &assoc, &depth, &options) == FAILURE){
		return;
	}
	if( !str_len ){
		RETURN_NULL();
	}

	/* For BC reasons, the bool $assoc overrides the long $options bit for PHP_JSON_OBJECT_AS_ARRAY */
	if(assoc) {
		options != PHP_JSON_OBJECT_AS_ARRAY;
	} else {
		options &= ~PHP_JSON_OBJECT_AS_ARRAY;
	}

	php_gbk_json_decode_ex(return_value, str, str_len, options, depth TSRMLS_DC);
}
/* }}} */

PHP_PHP_JSON_GBK_API void php_gbk_json_decode_ex(zval *return_value, char *str, int str_len, long options, long depth TSRMLS_DC) /* {{{ */
{
	zval *z;
	gbk_JSON_parser jp;

	if( str_len <= 0 ){
		RETURN_NULL();
	}
	
	if(depth <= 0){
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Depth must be greater than zero");
		RETURN_NULL();
	}

	ALLOC_INIT_ZVAL(z);

	jp = new_gbk_JSON_parser(depth);

	if (parse_gbk_JSON_ex(jp, z, str, str_len, options TSRMLS_CC)){
		*return_value = *z;
		FREE_ZVAL(z);
	} else {
		double d;
		int type, overflow_info;
		long p;
		
		RETVAL_NULL();
		if( str_len == 4 ){
			if(!strcasecmp(str, "null")){
				jp->error_code = PHP_JSON_ERROR_NONE;
				RETVAL_NULL();
			} else if( !strcasecmp(str, "true")) {
				RETVAL_BOOL(1);
			}
		} else if (str_len == 5 && !strcasecmp(str, "false")) {
			RETVAL_BOOL(0);
		}

		if((type = is_numeric_string_ex(str, str_len, &p, &d, 0, &overflow_info)) != 0) {
			if( type == IS_LONG){
				RETVAL_LONG(p);
			} else if (type == IS_DOUBLE) {
				if( options & PHP_JSON_BIGINT_AS_STRING && overflow_info){
					int i;
					zend_bool is_float = 0;
					for (i = (str[0] == '-' ? 1:0); i < str_len; i++){
						if( str[i] < '0' || str[i] > '9'){
							is_float = 1;
							break;
						}
					}

					if (is_float) {
						RETVAL_DOUBLE(d);
					} else {
						RETVAL_STRINGL(str, str_len, 1);
					}
				} else {
					RETVAL_DOUBLE(d);
				}
			}
		}

		if(Z_TYPE_P(return_value) != IS_NULL) {
			jp->error_code = PHP_JSON_ERROR_NONE;
		}

		zval_dtor(z);
	}
	FREE_ZVAL(z);
	free_gbk_JSON_parser(jp);
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
