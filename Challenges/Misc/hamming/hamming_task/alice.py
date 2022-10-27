from secret import mytext#It's in alice's device. We can't know!
from polar_router import send_over_weak_noisy_channel#how it works doesn't matter, u don't need this lib
from Crypto.Util.number import bytes_to_long
from functools import reduce

def hamming_encode(bitsblock):#do u know how it works?
    for t in range(4):
        bitsblock[1<<t]=reduce(
            lambda x,y:x^y ,
            [bit for i,bit in enumerate(bitsblock) if i&(1<<t)]
            )
    return bitsblock

bintxt=bin(bytes_to_long(mytext))[2:]
lenbintxt=len(bintxt)
assert lenbintxt%11==0
blocks=lenbintxt//11
bitlist=list(map(int,bintxt))
raw_msg=[[0]*3+[bitlist[i]]+[0]+bitlist[i+1:i+4]+[0]+bitlist[i+4:i+11] for i in range(0,lenbintxt,11)]

encoded_msg=[hamming_encode(raw_msg[i]) for i in range(blocks)]

send_over_weak_noisy_channel(encoded_msg)#send it