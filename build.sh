#!/bin/sh

#Modifies follow to your php path
PHP_BIN_DIR=/Users/woooha/Workspaces/php/bin/
PHPIZE=$PHP_BIN_DIR/phpize
PHP_CONFIG=$PHP_BIN_DIR/php-config
PHP=$PHP_BIN_DIR/php

clean()
{
	if [ -f "Makefile" ]; then
		make clean
	fi
	if [ -f "tmp-php.ini" ]; then
		rm tmp-php.ini
	fi
	$PHPIZE --clean
}

phpize()
{
	$PHPIZE
}


configure()
{
	./configure --with-php-config=$PHP_CONFIG
}



case "$1" in
	"clean")
		clean
		;;
	"phpize")
		clean
		phpize
		;;
	"configure")
		clean
		phpize
		configure
		;;
	"make")
		clean
		phpize
		configure
		make
		;;
	"install")
		clean
		phpize
		configure
		make &&  make install
		;;
	"test")
		$PHP run-tests.php
		;;
	*)
		echo "usage: clean|phpize|configure|make|install|test"
		exit 1
		;;
esac
