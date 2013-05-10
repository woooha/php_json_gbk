--TEST--
Check for whether the function php_json_gbk exists.
--SKIPIF--
<?php if (!extension_loaded("php_json_gbk")) print "skip"; ?>
--FILE--
<?php
if( function_exists("gbk_json_decode") ){
	echo "true";
}
?>
--EXPECT--
true
