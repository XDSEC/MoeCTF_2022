from random import randint
from Crypto.Util.number import bytes_to_long,long_to_bytes,GCD,inverse
from secret import flag
def bitlength(n):#判断消息长度
	length=len(bin(bytes_to_long(n))[2:])
	return length
def makeKey(n):#生成超递增序列，得到私钥、公钥
	length=len(n)
	privKey = [randint(1, 65536**length)]
	sum = privKey[0]
	for i in range(1, length):
		privKey.append(randint(sum*255 + 1, 65536**(length + i)))
		sum += privKey[i]
	q = 255*randint(privKey[length-1] + 1, 2*privKey[length-1])
	r = randint(1, q)
	while GCD(r, q) != 1:
		r = randint(1, q)
	pubKey = [ r*w % q for w in privKey ]#将超递增序列变为非超递增序列，作为公钥
	return privKey, q, r, pubKey

def encrypt(msg, pubKey):#用公钥加密消息
	cipher = 0
	i = 0
	for bit in msg:
		cipher += bit*pubKey[i]
		i += 1
	return cipher

def decrypt(cipher, privKey, q, r):#用私钥求得超递增序列并解密
	d = inverse(r, q)
	msg = cipher*d % q
	res = b''
	n = len(privKey)
	for i in range(n - 1, -1, -1):
		temp=0
		if msg >= privKey[i]:
			while msg >= privKey[i]:
				temp=temp+1
				msg -= privKey[i]
			res =  bytes([temp]) + res
		else:
			res =  bytes([0]) + res 
	return res
privKey, q, r, pubKey=makeKey(flag)
cipher=encrypt(flag,pubKey)
f=open("pubKey.txt",'w')
f.write(str(pubKey))
f.close()
f=open("cipher.txt",'w')
f.write(str(cipher))
f.close()
print(decrypt(encrypt(flag,pubKey),privKey,q,r))
assert decrypt(encrypt(flag,pubKey),privKey,q,r)==flag