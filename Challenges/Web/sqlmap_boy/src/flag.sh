#!/bin/bash

mysql -e "CREATE DATABASE IF NOT EXISTS moectf; USE moectf; CREATE TABLE IF NOT EXISTS \`flag\` (\`flAg\` varchar(255) NOT NULL) ENGINE=MyISAM  DEFAULT CHARSET=utf8; INSERT INTO \`flag\` VALUES ('$FLAG');" -uroot -proot

export FLAG=not_flag
FLAG=not_flag

flag{ea3f3d0b-1d32-4bee-b473-97bb50143047}