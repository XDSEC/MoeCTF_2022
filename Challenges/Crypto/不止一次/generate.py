
import libnum, codecs, numpy
from Crypto.Util.strxor import strxor
from random import randrange

key  = 'moectf{Ma2y_T1m3_9ad_8an_6e_crac7ed}'

m = 'In cryptography, the one-time pad (OTP) is an encryption technique that cannot be cracked, but requires the use of a single-use pre-shared key that is not smaller than the message being sent.'

f = open("附件.txt",'w')


for i in range(15):
    start = randrange(0,len(m)-2*len(key))
    mi = m[start : start+len(key)]
    ci = codecs.encode(strxor(mi.encode(),key.encode()) ,'hex').decode()
    #print(ci)
    f.write(ci)
    f.write('\n')


