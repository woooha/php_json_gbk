--TEST--
Check for decoding the long.
--FILE--
<?php
$num = "987654321";
echo gbk_json_decode($num);
?>
--EXCPECT--
987654321