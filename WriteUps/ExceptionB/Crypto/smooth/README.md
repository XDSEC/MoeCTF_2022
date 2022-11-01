# MoeCTF 2022 / Smooth

## 初见

看不懂，查百科去了

## 探索

可知这里涉及到了光滑数（[ctf-wiki上的条目](https://ctf-wiki.org/crypto/asymmetric/rsa/rsa_module_attack/#p-1)）

可以直接复制对于的代码，稍作修改

```python
def smooth(c,e,N):
    a = 2
    n = 2
    while True:
        a = pow(a, n, N)
        p = GCD(a-1, N)
        if p != 1 and p != N:
            q = N // p
            assert isPrime(p) and isPrime(q) and p*q == N
            d = inverse(e, (p-1)*(q-1))
            m = pow(c, d, N)
            return (p,q,m) 
        n += 1

p,q,m = smooth(c,0x10001,N)
assert c == pow(m,0x10001,p*q)
```
即可求得p q m，但是这里的m并不是真正意义上的明文，因为加密时对明文进行了一些操作

```python
for i in range(1,P-1729):
    flag=flag*i%P
```

也就是说我们还要根据这个m去求flag，这里涉及到一个考点，数论四大定理中的威尔逊定理（[oi-wiki上的条目](http://oi-wiki.com/math/number-theory/wilson/)）

对m继续进行操作，使 m = (flag * (p-2)) % p

```python 
for x in range(p-1729,p-1):
    m *= x
    m %= p
```

根据威尔逊定理，此时一定有 `flag = m mod p`

则有`flag = k * p + m`，其中k为整数，直接进行搜索

```python
for k in range(2<<16):
    flag = k * p + m
    if b"moectf" in long_to_bytes(flag):
        print(long_to_bytes(flag))
        break
```

得到flag

## 反思

我还是太菜了，数论基础不够，密码学做的云里雾里qwq