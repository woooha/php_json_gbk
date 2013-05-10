--TEST--
Try to decode a non-gbk json.
--SKIPIF--
<?php if (!extension_loaded("php_json_gbk")) print "skip"; ?>
--FILE--
<?php
$gbk_json = '{"name":"Yang Fan"}';
$data = gbk_json_decode($gbk_json, true);
var_dump( $data );
echo $data["name"];
echo json_last_error();
?>
--EXPECT--
Yang Fan