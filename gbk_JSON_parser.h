/* GBK_JSON_parser.h */

#ifndef GBK_JSON_PARSER_H
#define GBK_JSON_PARSER_H

#include "php.h"
#include "ext/standard/php_smart_str.h"
#include "php_php_json_gbk.h"

#define JSON_PARSER_DEFAULT_DEPTH 512

typedef struct gbk_JSON_parser_struct {
    int state;
    int depth;
    int top;
	int error_code;
    int* stack;
    zval **the_zstack;
    zval *the_static_zstack[JSON_PARSER_DEFAULT_DEPTH];
} * gbk_JSON_parser;

enum error_codes {
	PHP_JSON_ERROR_NONE = 0,
    PHP_JSON_ERROR_DEPTH, 
    PHP_JSON_ERROR_STATE_MISMATCH,  
    PHP_JSON_ERROR_CTRL_CHAR,   
    PHP_JSON_ERROR_SYNTAX,
    PHP_JSON_ERROR_GBK
};

extern gbk_JSON_parser new_gbk_JSON_parser(int depth);
extern int parse_gbk_JSON_ex(gbk_JSON_parser jp, zval *z, char gbk_json[], int length, int options TSRMLS_DC);
extern int free_JSON_parser(gbk_JSON_parser jp);

static inline int parse_gbk_JSON(gbk_JSON_parser jp, zval *z, char gbk_json[], int length, int assoc TSRMLS_DC)
{
	return parse_gbk_JSON_ex(jp, z, gbk_json, length, assoc ? PHP_JSON_OBJECT_AS_ARRAY : 0 TSRMLS_CC);
}

#endif
