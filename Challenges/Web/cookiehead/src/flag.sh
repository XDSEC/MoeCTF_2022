#!/bin/sh

sed -i "s/flag{this_is_a_fake_flag}/$FLAG/g" /var/www/html/index.php
export FLAG=not_flag
FLAG=not_flag
