--TEST--
gbk_json_decode() tests
--FILE--
<?php

var_dump(gbk_json_decode());
var_dump(gbk_json_decode(""));
var_dump(gbk_json_decode("", 1));
var_dump(gbk_json_decode("", 0));
var_dump(gbk_json_decode(".", 1));
var_dump(gbk_json_decode(".", 0));
var_dump(gbk_json_decode("<?>"));
var_dump(gbk_json_decode(";"));
var_dump(gbk_json_decode("руссиш"));
var_dump(gbk_json_decode("blah"));
var_dump(gbk_json_decode(NULL));
var_dump(gbk_json_decode('{ "test": { "foo": "bar" } }'));
var_dump(gbk_json_decode('{ "test": { "foo": "" } }'));
var_dump(gbk_json_decode('{ "": { "foo": "" } }'));
var_dump(gbk_json_decode('{ "": { "": "" } }'));
var_dump(gbk_json_decode('{ "": { "": "" }'));
var_dump(gbk_json_decode('{ "": "": "" } }'));

?>
===DONE===
--EXPECTF--
Warning: gbk_json_decode() expects at least 1 parameter, 0 given in %s on line %d
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
NULL
object(stdClass)#%d (1) {
  ["test"]=>
  object(stdClass)#%d (1) {
    ["foo"]=>
    string(3) "bar"
  }
}
object(stdClass)#%d (1) {
  ["test"]=>
  object(stdClass)#%d (1) {
    ["foo"]=>
    string(0) ""
  }
}
object(stdClass)#%d (1) {
  ["_empty_"]=>
  object(stdClass)#%d (1) {
    ["foo"]=>
    string(0) ""
  }
}
object(stdClass)#%d (1) {
  ["_empty_"]=>
  object(stdClass)#%d (1) {
    ["_empty_"]=>
    string(0) ""
  }
}
NULL
NULL
===DONE===
