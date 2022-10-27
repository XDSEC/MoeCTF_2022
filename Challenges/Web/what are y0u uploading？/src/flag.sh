#!/bin/sh

sed -i "s/moectf{A0_Qua1_D0ne!}/$FLAG/" /var/www/html/upload.php

export FLAG=not_flag
FLAG=not_flag

