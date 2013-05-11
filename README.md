php_json_gbk
============

A php extension to decode json string in GBK.

This extension only have the gbk_json_decode function, and only write for php 5.2.17.

I write this extension just because I need a gbk_json_decode function effciently and robust.
Json decode the GBK string use mb_convert_encoding or iconv is too slow for me.


The build.sh is to help you compile, install or modify this extension, you can use build.sh clean|phpize|make|install etc.
