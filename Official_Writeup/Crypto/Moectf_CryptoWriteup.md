# MoeCTF2022 Crypto Writeup

**Crypto出题组：LGLJ，Langge，b0y4nz，dbt，Polarnova**

## 前言

MoeCTF2022 Crypto试题 ~~ 落实立德树人根本任务，遵循德智体美劳全面发展要求，贯彻《深化新时代CTF改革总体方案》，体现了MoeCTF改革的方向。试卷突出密码学学科特点，加强基础性与关键能力考查，充分发挥密码学学科的选拔与引导功能。MoeCTF2022 Crypto坚持立德树人，体现CTF文化的育人价值，突出理性思维的价值，注重数学的基础性，引导学生对CTF概念、方法更深刻的认知，在基础性、综合性、应用性、创新性等方面都进行了深入的考查。CTF稳中有变，变中有新，难度设计科学， ~~ 较好的发挥了MoeCTF的选拔功能，对萌新学习密码知识发挥了积极的引导和促进作用。

## Signin

给出了 $p,q,e,c$ ,发现

 $e|(q-1)$ ,因此无法求出 $e$在 $\phi(n)$下的逆元,但是 $e、p-1$ 互素，可以求出 $d\equiv e^{-1} \ (mod\ p-1)$ 

$c:=c\%p$

$m:=c^d\%p$

即可求出 $m$ 



## Ez_factor

工作量证明(`proof_of_work`)：给定一个大偶数 $S$ ，要求分解为两个素数之和。一个朴素的想法是不断枚举素数 $a$ ，判断 $S-a$ 是不是素数即可。

注意到

```python
from static_secret import flag,P
```

猜测在每次交互中 $N$ 的因子 $P$ 是不变的，故可用两次交互得到的 $N$ 求最大公因数，可得  $P$ 

Exp:

```python
from pwn import *
from gmpy2 import next_prime,is_prime,gcd,invert
from Crypto.Util.number import long_to_bytes
REMOTE=""
PORT=

def getmn():
    sh=remote(REMOTE,PORT)
    prestr=sh.recvuntil(b'== ')
    bigeven=int(sh.recvuntil(b'\n',drop=True))
    a=1
    while True:
        a=next_prime(a)
        if is_prime(bigeven-a):
            sh.sendafter(b'A=',str(bigeven-a).encode())
            sh.sendafter(b'B=',str(a).encode())
            break
    prestr=sh.recvuntil(b'm=')
    m=int(sh.recvuntil(b'\n').decode(),16)
    prestr=sh.recvuntil(b'N=')
    n=int(sh.recvuntil(b'\n').decode(),16)
    sh.close()
    return m,n


m1,n1=getmn()
m2,n2=getmn()
p=gcd(n1,n2)
q=n2//p
phi=(p-1)*(q-1)
d=invert(0x10001,phi)
m=pow(m2,d,n2)
print(long_to_bytes(m))
```



## Weird_E_Revenge

跟signin类似，但是 $p,q,r<m<p*q,p*r,q*r$

可以解出 $m_1\equiv m(mod\ p),m_2\equiv m(mod\ r) $

再用中国剩余定理，求出 $m=m_1\cdot r\cdot inv_1+m_2\cdot p \cdot inv_2$ ,其中 $inv_1\equiv r^{-1}(mod\ p),inv_2\equiv p^{-1}(mod\ r)$.



## 一次就好

设定：与**不止一次**为一套题，原本想让大家了解一次加密。

分析可知，flag经过一次加密后，经过了RSA加密。

### 第一部分——RSA

- |p-q| 很小

$$
\frac{(p+q)^2}{4} - N = \frac{(p+q)^2}{4} -pq = \frac{(p-q)^2}{4}
$$

由于$ |p-q|$ 很小，进而 $\frac{(p-q)^2}{4}$ 很小， 即 $\frac{(p+q)^2}{4} $与 N 相差很小，从而 $\frac{p+q}{2}$ 与 $\sqrt{N} $相差很小

因此，我们可以爆破差值 $delt$，即 $\frac{(p-q)^2}{4}$，计算 $delt + N $是否为完全平方数

如果为完全平方数，那么 $delt + N = \frac{(p+q)^2}{4}$

$$
\sqrt{delt} = \frac{p-q}{2} \\
\sqrt{delt + N } = \frac{p+q}{2}
$$

联立即得 $p,q$，之后正常解密即可。

### 第二部分——一次加密

直接根据 key 异或解密即可

```python
from Crypto.Util.strxor import strxor
from Crypto.Util.number import *
from gmpy2 import *
import codecs

c = b'Just once,I will accompany you to see the world'
gift = 127749242340004016446001520961422059381052911692861305057396462507126566256652316418648339729479729456613704261614569202080544183416817827900318057127539938899577580150210279291202882125162360563285794285643498788533366420857232908632854569967831654923280152015070999912426044356353393293132914925252494215314
N = 164395171965189899201846744244839588935095288852148507114700855000512464673975991783671493756953831066569435489213778701866548078207835105414442567008315975881952023037557292470005621852113709605286462434049311321175270134326956812936961821511753256992797013020030263567313257339785161436188882721736453384403
e = 0x10001

delt = 0
while True:
    if iroot(N+delt**2, 2)[1] == True:
        x = iroot(N+delt**2, 2)[0]
        p = delt + x
        break
    delt += 1
q = N//p
d = invert(e,(p-1)*(q-1))
m = powmod(gift, d, N)
key = long_to_bytes(m)
print(key)
flag = strxor(key, c)
print(flag)
```

## 不止一次

设定：与**一次就好**为一套题——多次加密

### 方法一：已知部分key

由于flag格式的缘故，我们获得了密钥的前一部分，由加密脚本可知，是同一个key对不同明文加密。

通过这一部分密钥，可以解密出每一个密文的前部分明文，发现十余个明文中有**两个明文仅相差一个字符**，则通过爆破key，即可获得全部的key。

代码来自**鲤唐可可** 

```python
from Crypto.Util.strxor import strxor
from string import printable

A = bytes.fromhex("05010c1201035b3909530d7f3750035d304d41063a18021c3e550e3a075e41014211440f")
B = bytes.fromhex("0306141611460f250046593c355f035c2b1903017f5b130f3c5d003b4f52031643451618")

known = "moectf{"
flag_len = 36
while len(known) < flag_len:
    for c in printable:
        flag = known + c + "a"*(flag_len - 1 - len(known))
        flag = flag.encode()
        a = strxor(A,flag)
        b = strxor(B,flag)
        if a[len(known)] == b[len(known)-1]:
            known+=c
            break
```

### 方法二：攻击多次加密

- 由异或的性质，对于密文之间的异或，异或两有：

$$
C_1 \bigoplus C_2 = (M_1 \bigoplus key) \bigoplus (M_2 \bigoplus key) = M_1 \bigoplus M_2
$$

- 密文之间的异或就为明文之间的异或。

- 大部分异或后都为特殊字符（不可打印字符），但其中也出现了许多大小写字母。

- 考虑大小写字母出现的原因
  
  - 空格 `0x20`，$\bigoplus$小写字母`0x61~0x7A` $\rightarrow$ 大写字母`0x41~0x5A`
  
  - 空格 `0x20`，$\bigoplus$大写字母`0x41~0x5A` $\rightarrow$ 小写字母`0x61~0x7A`

- 则如果一个明文某个位置是空格，则这个明文异或其他明文，这个位置大概率全是小写字母或者大写字母

- 以此进行还原。

- 如果有的地方没有空格，则会导致不能复原全部明文
  
  - 这里为了简便，则构造了特殊数据，保证了每个位置都有空格，更方便求解。

```python
import numpy
from Crypto.Util.strxor import strxor

def many_time_pad():
    def infer(index, pos):
        if mt[index, pos] != 0:
            return
        mt[index, pos] = ord(' ')
        for x in range(len(c)):
            if x != index:
                mt[x][pos] = strxor(c[x], c[index])[pos] ^ ord(' ')

    def cnt(pos,res):
        sum = 0
        for s in res:
            if chr(s[pos]).isalpha():
                sum+=1
        return sum
    
    def getSpace():
        for index, x in enumerate(c):
            res = [strxor(x, y) for y in c if x != y]
            for pos in range(len(x)):
                dat.append((cnt(pos,res), index, pos))

    dat = []
    
    c = [bytes.fromhex(x.strip()) for x in
         open(r'D:\~~~CTF\moectf2022\不止一次\test.txt', 'r').readlines()]
    print(c)

    mt = numpy.zeros([len(c), len(c[0])], dtype=int)
    
    getSpace()

    dat = sorted(dat)[::-1]

    for x in dat:
        infer(x[1], x[2])

    for s in mt:
        for x in s:
            print(chr(x),end='')
        print()
    print()

    key = strxor(c[0], ''.join([chr(x) for x in mt[0]]).encode())
    print(key)
    

if __name__ == '__main__':
    many_time_pad()
```



改自 `[AFCTF2018]你听过一次一密么？`



## EZ_CBC

分组加密、采用CBC的分组模式

解密过程
$$
{\displaystyle P_{i}=D_{K}(C_{i})\oplus C_{i-1},}\\{\displaystyle C_{0}=IV}
$$
由于第一块密文我们已知，即 $P_1$ ，根据第一条我们可以得到 $D_K(C_1)$ 此处即为 $k|C_1$，进而得到 $k$，依次解密即可。

```python
c = [748044282, 2053864743, 734492413, 675117672, 1691099828, 1729574447, 1691102180, 657669994, 1741780405, 842228028, 1909206003, 1797919307]
m = [bytes_to_long(b'moec')]
k = IV ^ m[0] ^ c[0]

for i in range(1,len(c)):
    m.append(k^c[i]^c[i-1])

for i in range(len(m)):
    print(long_to_bytes(m[i]).decode(),end='')
```



## Smooth

考察：

-  $p-1$ 光滑：*Pollard‘s p-1 method*

- 威尔逊(Wilson)定理： $p$ 是素数，则 $(p-1)! \equiv -1 \pmod p$ 

彩蛋：拉马努金发现  **1729**  可以用两种不同的方式写成两个数字的立方和，而且是有这种特性的数字中最小的一个

Exp:

```python
from gmpy2 import powmod,gcd
from Crypto.Util.number import long_to_bytes,inverse

c= ...
N= ...

def p_1_smooth(N):
    a = 2;n = 2
    while True:
        a = powmod(a, n, N)
        res = gcd(a-1, N)
        if res != 1 and res != N:
            return res
        n += 1

p=p_1_smooth(N)
q=N//p
phi=(p-1)*(q-1)
d=inverse(0x10001,phi)
m=pow(c,d,N)

for i in range(p-1729,p):
    m=m*i%p
m=(-m)%p

print(long_to_bytes(m))
```



## Baby NET

主要是学习一下与服务器交互。

proof of work 工作量证明，直接爆破未知字符即可。

Feistel 分组加密结构：

参考3DES 加解密结构：

密文 = EK3(DK2(EK1(明文)))

明文 = DK1(EK2(DK3(密文)))

脚本如下：

```python
from pwn import *
from string import *
from hashlib import sha256
from Crypto.Util.number import *
from Crypto.Cipher import AES

table = ascii_letters+digits

net = remote('49.232.141.239',10001)

pres = net.recvuntil(b"[+] sha256(XXX+")
s = net.recvuntil(b") == ",drop=True).decode()
sha = net.recvuntil(b'\n',drop=True).decode()

for i in table:
    for j in table:
        for k in table:
            proof = i+j+k+s
            if sha256(proof.encode()).hexdigest() == sha:
                net.sendline((i+j+k).encode())
                break

pres = net.recvuntil(b'\n')
pres = net.recvuntil(b'[+] key1 = ')
key1 = net.recvuntil(b'\n',drop=True)
pres = net.recvuntil(b'[+] key2 = ')
key2 = net.recvuntil(b'\n',drop=True)
pres = net.recvuntil(b'[+] cipher = ')
cipher = net.recvuntil(b'\n',drop=True).decode()
cipher = long_to_bytes(int(cipher,16))

def encrypt(plaintext,key):
    assert len(plaintext) == 32
    assert len(key) == 16

    left = plaintext[:16]
    right = plaintext[16:]

    for i in range(3):
        aes = AES.new(key,AES.MODE_ECB)
        new_right = long_to_bytes(bytes_to_long(aes.encrypt(right)) ^ bytes_to_long(left))
        new_left = right
        left = new_left
        right = new_right
    return left + right

def decrypt(ciphertext,key):
    assert len(ciphertext) == 32
    assert len(key) == 16

    left = ciphertext[:16]
    right = ciphertext[16:]

    for i in range(3):
        aes = AES.new(key,AES.MODE_ECB)
        last_right = left
        last_left = long_to_bytes(bytes_to_long(right) ^ bytes_to_long(aes.encrypt(left)))
        left = last_left
        right = last_right
    return left + right

# cipher = encrypt(M,key1)
# cipher = decrypt(cipher,key2)
# cipher = encrypt(cipher,key1)

cipher = decrypt(cipher,key1)
cipher = encrypt(cipher,key2)
M = decrypt(cipher,key1)

pres = net.recvuntil(b'[+] plz give me the K||IV (K+IV):\n')

net.send(M)

pres = net.recvuntil(b'You win! Give you my encdata: ')
enc = net.recvuntil(b'\n',drop=True).decode()
enc = long_to_bytes(int(enc,16))

data = 'Congratulations!_You_have_get_the_flag!'
pres = net.recvuntil(b'[+] plz give me data:')

net.send(data)
pres = net.recvuntil(b'[+] flag is:')
flag = net.recvuntil('\n')
print(flag)
```

## 0RSA0

### level 1 

明文只有16字节，并且加密指数为3，而模数n为1024bit，直接开三次根即可

### level 2

泄露 $d_p$ ，e=65537
$$
ed = k\phi(n)+1\\
ed_p=k(q-1)+1 \ mod\ (p-1)
$$
由于私钥 $d$ 的比特数和n相差不大，因此k大约在 $(1,e)$ 之间。直接爆破 $k$ 分解 $n$

```python
def getd(n,e,dp):
    '''python2'''
    for i in range(1,e):
        if (dp*e-1)%i == 0:
            if n%(((dp*e-1)/i)+1)==0:
                p=((dp*e-1)/i)+1
                q=n/(((dp*e-1)/i)+1)
                phi = (p-1)*(q-1)
                d = gmpy2.invert(e,phi)%phi
                return d

n1,e1,c1 = enc1(m1)
n2,e2,c2,dp2 = enc2(m2)
m1 = gmpy2.iroot(c1,3)[0]
print(long_to_bytes(m1))
d2 = getd(n2,e2,dp2)
m2 = long_to_bytes(pow(c2,d2,n2))
print(m2)
```

## ezhash

对称性⇔不变量

本题考察观察能力，注意到函数$R$的轮换对称性

再考虑到hash函数中的循环只执行了一次，因此交换变量的值，hash值不变。

也就是变换字符串开头16个字母和中间16个字母的位置即可

```python
from pwn import *
from hashlib import sha256
HOST, PORT = ... , ...
sh=remote(HOST, PORT)

table = string.ascii_letters+string.digits

def proof_of_work(s,tsha):
    for i in table:
        for j in table:
            for k in table:
                for l in table:
                    proof=i+j+k+l+s
                    if(sha256(proof.encode()).hexdigest()==tsha):
                        sh.sendline((i+j+k+l).encode())
                        return

pres=sh.recvuntil(b'sha256(XXXX+',drop=True)
s=sh.recvuntil(b') == ',drop=True).decode()
tsha=sh.recvuntil(b'\n',drop=True).decode()

proof_of_work(s,tsha)
pres=sh.recvuntil(b'message1 = ',drop=True)
msg=sh.recvuntil(b'\n',drop=True)
forge_msg = msg[32:48] + msg[16:32] + msg[:16] + msg[48:]
sh.sendline(forge_msg)
sh.interactive()
```



## MiniMiniBackPack

设定：背包前置题

### 超递增序列

称一个序列 $r = (r_1,r_2,\cdots,r_n)$  是超级递增序列，当且仅当满足

$$
r_{i+1} \geq 2r_i,\forall 1\leq i \leq n-1
$$

则有性质：

$$
r_k>\sum^{k-1}_{i=1}r_i
$$

则对于解密，即贪心求解即可：从大到小，如果可以减去当前大数，则减去，并且对应二进制明文为 **1**。

```python
from gmpy2 import *
from Crypto.Util.number import *
import random

txt = open("MiniMiniBackPack\附件.txt",'r').readlines()
key = eval(txt[0])
c = int(txt[1])
m = ''

for i in reversed(key):
    if c - i>=0:
        m += '1'
        c -= i
    else:
        m += '0'
print(long_to_bytes(int(m,2)))
```

## LittLe_FSR

LFSR流密码。

通过分析可得：

加密方式为

$$
newbit = data_{key[0]}\bigoplus data_{key[1]}\bigoplus \cdots \bigoplus data_{key[m]}
$$

### 方法一：爆破

通过给的数据进行爆破，我们知道key的个数，我们爆破key，然后通过数据验证key的正确性。

CPU:AMD Ryzen 7 5800H with Radeon Graphics

实测爆破时间 2h 48min：数量级：$8*400^4$  约等于 1e10

```python
from Crypto.Util.number import *
from gmpy2 import *
from tqdm import *

class Decode3():
    def __init__(self):
        self.data = list(map(int,open("附件.txt","r").read().strip()))
        self.key = [0,0,0,0,0]

    def calc(self,i):
        x = 0
        for index in self.key:
            x ^= self.data[index+i-400]
        return x

    def check(self):
        for i in range(400,len(self.data)):
            x = self.data[i]
            if x != self.calc(i):
                return False
        return True

    def brute(self):
        for i in trange(400):
            self.key[0] = i
            for j in trange(i+1,400):
                self.key[1] = j
                for k in range(j+1,400):
                    self.key[2] = k
                    for l in range(k+1,400):
                        self.key[3] = l
                        for m in range(l+1,400):
                            self.key[4] = m
                            if self.check():
                                print(self.key)
                                return

    def recover(self):
        Len = 400 - self.key[0]
        self.m = list(map(int, self.data[:Len]))

        for _ in range(2022):
            c = 0
            for t in self.key:
                c ^= self.m[t - self.key[0] - 1]
            self.m = [c] + self.m[:Len - 1]

    def getflag(self):
        flag = ''.join(str(i) for i in self.m)
        print(long_to_bytes(int(flag, 2)))

    def work(self):
        #self.brute()

        self.key = [8, 23, 114, 211, 360]
        self.recover()
        self.getflag()

if __name__ == '__main__':
    x = Decode3()
    x.work()
```

### 方法二：求解线性同余方程组

通过加密方程，建立 400 个**模2意义下**的同余方程，通过sage求解方程即可。

```python
#sage
data = open("D:\~~~CTF\moectf2022\Decode3\附件.txt",'r').read().strip()
b = list(data[400:800])
B =vector(Zmod(2),b)
mt = matrix(Zmod(2),0,400)
for i in range(400):
    mt = mt.stack(vector(Zmod(2),list(data[i:i+400])))
x = mt \ B
key = []
for index,i in enumerate(x):
    if i == 1:
        key.append(index)
print(key)
# [8, 23, 114, 211, 360]

Len = 400 - key[0]
m = list(map(int,data[:Len]))

for _ in range(2022):
    c = 0
    for t in key: c = c^^m[t-key[0]-1]
    m = [c] + m[:Len-1]

flag = ''.join(str(i) for i in m)


from Crypto.Util.number import *
print(long_to_bytes(int(flag,2)))
```

- 值得注意的是，由于**key**其中没有**1**，也就是明文前一部分（最小的key前）的二进制数未参与后续的加密，所以无法推出，因此需要自动补全前一部分的flag（其实也就是一个`m`)

- 本来应该设置更长的损失，但为了保留爆破方法，所以就取得较小，仅为8。

（这也是为什么题目中`LFSR`中缺失了`L`)

## Knapsack

模板题，应用LLL算法即可

```python
from Crypto.Util.number import *
f=open("pubKey.txt",'r')
temp=f.read()
f.close()
pubKey=eval(temp)
length = len(pubKey)
f = open("cipher.txt", 'r')
cipher =int(f.read())
f.close()
print("start")
A = Matrix(ZZ, length + 1, length + 1)
for i in range(length):
    A[i, i] = 1
for i in range(length):
    A[i, length] = pubKey[i]
A[length, length] = -cipher
print(cipher)
res = A.LLL()
for i in range(0, length + 1):
    M = res.row(i).list()
    flag = True
    for m in M:
        if m < 0 or m > 255:
            flag = False
            break
    if flag:
        print(i, M)
        answer=b''
        for j in M:
            answer+=bytes([j])
        print(answer)
```

