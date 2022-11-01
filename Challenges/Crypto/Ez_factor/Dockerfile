FROM python:3.8-alpine
LABEL Description="Ezfactor_crypto002" VERSION='1.0'

RUN sed -i 's/dl-cdn.alpinelinux.org/mirrors.aliyun.com/g' /etc/apk/repositories && apk update && apk add gcc g++ make openssl-dev python3-dev libffi-dev autoconf && mkdir -p /opt/aes && pip install pycryptodome -i https://pypi.mirrors.ustc.edu.cn/simple

WORKDIR /opt/Ezfactor

COPY static_secret.py .
COPY factor_chal.py .

EXPOSE 10001
CMD ["python", "-u", "factor_chal.py"]
