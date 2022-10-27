# MoeCTF 2022 / 小小凯撒

## 初见

描述说大小写都有，那就考虑最大偏移52的凯撒密码（即含大小写）

没找到在线工具，就5分钟手搓了一个

```python
def c2n(c):
    if ord('A')<=ord(c) and ord(c)<=ord('Z'):
        return ord(c)-ord("A")
    elif ord('a')<=ord(c) and ord(c)<=ord('z'):
        return ord(c)-ord("a") + 26
    else:
        return 114514+ord(c)
def n2c(n):
    if 0<=n and n<26:
        return chr(n+ord("A"))
    else:
        n-=26
        if 0<=n and n<256:
            return chr(n+ord("a"))
        else:
            return chr(n-114514)
def mov(c,offset):
    return n2c((c2n(c)-offset)%52)
cipher = "kqEftuEUEftqOADDqoFRxmsOAzsDmFGxmFuAzE"
for x in range(52):
    print("".join([mov(c,x) for c in cipher]))
```

得到输出
```
kqEftuEUEftqOADDqoFRxmsOAzsDmFGxmFuAzE
jpDestDTDespNzCCpnEQwlrNzyrClEFwlEtzyD
ioCdrsCSCdroMyBBomDPvkqMyxqBkDEvkDsyxC
hnBcqrBRBcqnLxAAnlCOujpLxwpAjCDujCrxwB
gmAbpqAQAbpmKwzzmkBNtioKwvoziBCtiBqwvA
flzaopzPzaolJvyyljAMshnJvunyhABshApvuz
ekyZnoyOyZnkIuxxkizLrgmIutmxgzArgzouty
djxYmnxNxYmjHtwwjhyKqflHtslwfyzqfyntsx
ciwXlmwMwXliGsvvigxJpekGsrkvexypexmsrw
bhvWklvLvWkhFruuhfwIodjFrqjudwxodwlrqv
aguVjkuKuVjgEqttgevHnciEqpitcvwncvkqpu
ZftUijtJtUifDpssfduGmbhDpohsbuvmbujpot
YesThisIsTheCorrectFlagCongratulations
XdrSghrHrSgdBnqqdbsEkZfBnmfqZstkZshnmr
WcqRfgqGqRfcAmppcarDjYeAmlepYrsjYrgmlq
VbpQefpFpQebzloobZqCiXdzlkdoXqriXqflkp
UaoPdeoEoPdayknnaYpBhWcykjcnWpqhWpekjo
TZnOcdnDnOcZxjmmZXoAgVbxjibmVopgVodjin
SYmNbcmCmNbYwillYWnzfUawihalUnofUncihm
RXlMablBlMaXvhkkXVmyeTZvhgZkTmneTmbhgl
QWkLZakAkLZWugjjWUlxdSYugfYjSlmdSlagfk
PVjKYZjzjKYVtfiiVTkwcRXtfeXiRklcRkZfej
OUiJXYiyiJXUsehhUSjvbQWsedWhQjkbQjYedi
NThIWXhxhIWTrdggTRiuaPVrdcVgPijaPiXdch
MSgHVWgwgHVSqcffSQhtZOUqcbUfOhiZOhWcbg
LRfGUVfvfGURpbeeRPgsYNTpbaTeNghYNgVbaf
KQeFTUeueFTQoaddQOfrXMSoaZSdMfgXMfUaZe
JPdESTdtdESPnZccPNeqWLRnZYRcLefWLeTZYd
IOcDRScscDROmYbbOMdpVKQmYXQbKdeVKdSYXc
HNbCQRbrbCQNlXaaNLcoUJPlXWPaJcdUJcRXWb
GMaBPQaqaBPMkWZZMKbnTIOkWVOZIbcTIbQWVa
FLZAOPZpZAOLjVYYLJamSHNjVUNYHabSHaPVUZ
EKYzNOYoYzNKiUXXKIZlRGMiUTMXGZaRGZOUTY
DJXyMNXnXyMJhTWWJHYkQFLhTSLWFYZQFYNTSX
CIWxLMWmWxLIgSVVIGXjPEKgSRKVEXYPEXMSRW
BHVwKLVlVwKHfRUUHFWiODJfRQJUDWXODWLRQV
AGUvJKUkUvJGeQTTGEVhNCIeQPITCVWNCVKQPU
zFTuIJTjTuIFdPSSFDUgMBHdPOHSBUVMBUJPOT
yEStHISiStHEcORRECTfLAGcONGRATULATIONS
xDRsGHRhRsGDbNQQDBSeKzFbNMFQzSTKzSHNMR
wCQrFGQgQrFCaMPPCARdJyEaMLEPyRSJyRGMLQ
vBPqEFPfPqEBZLOOBzQcIxDZLKDOxQRIxQFLKP
uAOpDEOeOpDAYKNNAyPbHwCYKJCNwPQHwPEKJO
tzNoCDNdNoCzXJMMzxOaGvBXJIBMvOPGvODJIN
syMnBCMcMnByWILLywNZFuAWIHALuNOFuNCIHM
rxLmABLbLmAxVHKKxvMYEtzVHGzKtMNEtMBHGL
qwKlzAKaKlzwUGJJwuLXDsyUGFyJsLMDsLAGFK
pvJkyzJZJkyvTFIIvtKWCrxTFExIrKLCrKzFEJ
ouIjxyIYIjxuSEHHusJVBqwSEDwHqJKBqJyEDI
ntHiwxHXHiwtRDGGtrIUApvRDCvGpIJApIxDCH
msGhvwGWGhvsQCFFsqHTzouQCBuFoHIzoHwCBG
lrFguvFVFgurPBEErpGSyntPBAtEnGHynGvBAF
```

emmmmmm，然后找出最像flag的那个吧www