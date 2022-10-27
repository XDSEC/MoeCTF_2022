FROM ctftraining/base_image_nginx_mysql_php_73
COPY src /tmp

RUN cp -rf /tmp/html /var/www/ \
    && chown -R www-data:www-data /var/www/html \
    && cp -f /tmp/flag.sh /flag.sh 


