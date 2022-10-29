#!/bin/sh

sed -i "s/moectf{Wa0g_Yi1g_Chu0}/$FLAG/" /var/www/html/index.php

export FLAG=not_flag
FLAG=not_flag
