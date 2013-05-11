--TEST--
Check for decoding an array.
--FILE--
<?php
$arr_json = '[1,2,3,4,5,6,7,8,9]';
$data = gbk_json_decode($arr_json);
echo $data[8];
?>
--EXPECT--
9