--TEST--
Check for decode the GBK json.
--FILE--
<?php
$gbk_json = '{"name":"�ʻ�","age":17,"sex":"�С�","like":"Ů"}';
$data = gbk_json_decode($gbk_json, true);
echo $data['name'], $data['like'], $data['sex'];
?>
--EXPECT--
�ʻ�Ů�С�
