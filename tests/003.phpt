--TEST--
Check for decode json string for boolean value
--SKIPIF--
<?php if (!extension_loaded("php_json_gbk")) print "skip"; ?>
--FILE--
<?php
if( true === gbk_json_decode("true") ){
	echo "Boolean true is ok","\n";
}
if( false === gbk_json_decode("false") ){
	echo "Boolean false is ok";
}
?>
--EXPECT--
Boolean true is ok
Boolean false is ok
