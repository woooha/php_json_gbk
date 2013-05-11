/* JSON_checker.h */

#include "php.h"
#include "ext/standard/php_smart_str.h"

extern int gbk_JSON_parser(zval *z, char p[], int length, int assoc TSRMLS_DC);
