--TEST--
Test gbk_json_decode() function : error conditions
--FILE--
<?php
/* Prototype  : mixed gbk_json_decode  ( string $json  [, bool $assoc  ] )
 * Description: Decodes a JSON string
 * Source code: ext/json/php_json.c
 * Alias to functions: 
 */
echo "*** Testing gbk_json_decode() : error conditions ***\n";

echo "\n-- Testing gbk_json_decode() function with no arguments --\n";
var_dump( gbk_json_decode() );

echo "\n-- Testing gbk_json_decode() function with more than expected no. of arguments --\n";
$extra_arg = 10;
var_dump( gbk_json_decode('"abc"', TRUE, $extra_arg) );

?>
===Done===
--EXPECTF--
*** Testing gbk_json_decode() : error conditions ***

-- Testing gbk_json_decode() function with no arguments --

Warning: gbk_json_decode() expects at least 1 parameter, 0 given in %s on line %d
NULL

-- Testing gbk_json_decode() function with more than expected no. of arguments --

Warning: gbk_json_decode() expects at most 2 parameters, 3 given in %s on line %d
NULL
===Done===
