from gmpy2 import *
from Crypto.Util.number import *
import random
from FLAG import flag

def gen_key(size):
    s = 1000
    key = []
    for _ in range(size):
        a = random.randint(s + 1, 2 * s)
        assert a > sum(key)
        key.append(a)
        s += a
    return key


m = bytes_to_long(flag)
L = len(bin(m)[2:])
key = gen_key(L)
c = 0

for i in range(L):
    c += key[i]**(m&1)
    m >>= 1

print(key)
print(c)


