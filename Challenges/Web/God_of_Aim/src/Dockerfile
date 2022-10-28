FROM alpine:3.16

COPY . /var/www/html
WORKDIR /var/www/html

RUN sed -i 's/dl-cdn.alpinelinux.org/mirrors.ustc.edu.cn/g' /etc/apk/repositories \
    && apk update \
    && apk add --no-cache nginx \
    && echo "Asia/Shanghai" > /etc/timezone \
    && chmod +x setup.sh

COPY default.conf /etc/nginx/http.d/default.conf

CMD ["/bin/sh","-c","/var/www/html/setup.sh"]

