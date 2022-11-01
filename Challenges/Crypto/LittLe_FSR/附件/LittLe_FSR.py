from Crypto.Util.number import *
from gmpy2 import *
from secret import FLAG, key
import string
import random

assert FLAG[:7] == b'moectf{'
assert FLAG[-1:]== b'}'
table = string.ascii_letters+string.digits+string.punctuation
for _ in range(50-len(FLAG)):
    FLAG += random.choice(table).encode()
assert len(FLAG) == 50
assert len(key) == 5

class LFSR:
    def __init__(self):
        self.data = list(map(int,list(bin(bytes_to_long(FLAG))[2:].rjust(400,'0'))))
        for _ in range(2022):
            self.cycle()

    def cycle(self):
        bit = self.data[0]
        new = 0
        for i in key:
            new ^= self.data[i]
        self.data = self.data[1:] + [new]
        return bit

ILOVEMOECTF = LFSR()
for _ in range(2022):
    print(ILOVEMOECTF.cycle(), end='')

