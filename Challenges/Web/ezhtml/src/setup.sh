#!/bin/sh

sed -i "s/moectf{this_is_a_fake_flag}/$FLAG/g" /var/www/html/evil.js
export FLAG=not_flag
FLAG=not_flag

nginx -g "daemon off;"


