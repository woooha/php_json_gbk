--TEST--
Check for decode the GBK json.
--FILE--
<?php
$gbk_json = '{"name":"鲜花","age":17,"sex":"男』","like":"女"}';
$data = gbk_json_decode($gbk_json, true);
echo $data['name'], $data['like'], $data['sex'];
?>
--EXPECT--
鲜花女男』
