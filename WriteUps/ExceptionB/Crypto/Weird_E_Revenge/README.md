# MoeCTF 2022 / Weird_E_Revenge

## 初见

~~不会~~

看到给了两组模和密文，但是按照常规的rsa解法发现phi与e不互质，似乎是和[signin](../signin/)类似的题型

## 探索

(!!!警告 以下将有暴力非预期出现!!!)

### 解法一：AMM暴力破解（非预期）

时间成本太大了，跑了两个小时没出结果就没跑了，理论上能出结果（

脚本与[signin](../signin/amm.py)那题的amm脚本一致，只需替换pqec即可

### 解法二：还是暴力解（非预期）

用云服务器跑，大概花了8个小时跑出了结果

脚本与[signin](../signin/exp2.py)那题的脚本一致，只需替换pqec即可

### 解法三：CRT 中国剩余定理

[oi-wiki上的条目](https://oi-wiki.org/math/number-theory/crt/)

对于RSA，有`m^e = c (mod n)`

在本题，即为`m^e = c1 (mod p*q)`和`m^e = c2 (mod r*q)`，满足CRT定理

先编写CRT的python实现（我的写法与oi-wiki上有些不同，~~但结果是一致的~~，这里实现的是ExCRT拓展中国剩余定理）

```python
from math import prod
from itertools import combinations
from Crypto.Util.number import inverse,GCD
def CRT(args):
    A = [a for n,a in args] # 余数
    N = [n for n,a in args] # 模数
    N_ = prod(N)
    M = [N_ // n for n in N]
    I = [inverse(m,n) for m,n in zip(M,N)]
    C = [m*i for m,i in zip(M,I)]
    G_ = prod([GCD(x,y) for x,y in combinations(N,2)]) # 最大公约数
    return (sum([a*c % N_ for a,c in zip(A,C)]) % N_) // G_
```

利用CRT可以求得一个 `c` 满足 `m^e = c (mod p*q*r)`

接着便可以利用CRT的结果，按照与signin类似的方法进行求解

```python
t = CRT([(p*q,c1),(q*r,c2)])
d = inverse(e,(p-1)*(r-1))
m = pow(t,d,p*r)
```
得到flag
