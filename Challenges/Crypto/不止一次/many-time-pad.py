import libnum, codecs, numpy
from Crypto.Util.strxor import strxor

def many_time_pad():

    def isChr(x):
        if ord('a') <= x and x <= ord('z'): return True
        if ord('A') <= x and x <= ord('Z'): return True
        return False

    def infer(index, pos):
        if msg[index, pos] != 0:
            return
        msg[index, pos] = ord(' ')
        for x in range(len(c)):
            if x != index:
                msg[x][pos] = strxor(c[x], c[index])[pos] ^ ord(' ')

    def know(index, pos, ch):
        msg[index, pos] = ord(ch)
        for x in range(len(c)):
            if x != index:
                msg[x][pos] = strxor(c[x], c[index])[pos] ^ ord(ch)

    dat = []

    def getSpace():
        for index, x in enumerate(c):
            res = [strxor(x, y) for y in c if x != y]
            f = lambda pos: len(list(filter(isChr, [s[pos] for s in res])))
            cnt = [f(pos) for pos in range(len(x))]
            for pos in range(len(x)):
                dat.append((f(pos), index, pos))

    c = [codecs.decode(x.strip().encode(), 'hex') for x in
         open('D:\~~~CTF\moectf2022\多次也不错\附件.txt', 'r').readlines()]
    print(c)

    msg = numpy.zeros([len(c), len(c[0])], dtype=int)      # len(c) * len(c[0]) 的 0 矩阵

    getSpace()

    dat = sorted(dat)[::-1]
    for w, index, pos in dat:
        infer(index, pos)


    print('\n'.join([''.join([chr(c) for c in x]) for x in msg]))


    key = strxor(c[0], ''.join([chr(c) for c in msg[0]]).encode())

    print(key)
    with open('key.txt','w') as f:
        f.write(key.decode())

if __name__ == '__main__':
    many_time_pad()