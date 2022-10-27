# MoeCTF 2022 / ez_hash

## 初见

看附件，稍微看一下整个流程

刚开始就是一个hash丢脸上，直接暴力破解

```python
for x in product(string.ascii_letters+string.digits,repeat=4):
    if sha256(("".join(x)+"o0SLYkQEgfMPbiAZ").encode("utf-8")).hexdigest() == \
                "b8bc0f0d3b58314b29e4fcb8c779432eeb1285b1764501670601b517790f4aa8":
        print("".join(x))
        break
```

轻松秒杀第一关

第二部分也是一个hash碰撞，只不过不能采用第一部分的硬碰，只能取巧绕过

## 研究

仔细看这个hash的实现

```python
def pad(m): # 将m的长度补为64的倍数
    return m + bytes([64-len(m)%64 for _ in range(64-len(m)%64)])

def F(x,y,z): # 这里把xyz三个数相乘，并取后128bits，这里交换xyz的顺序不影响结果
    return (x * y * z) & 0xffffffffffffffffffffffffffffffff

def R(x,y,z,t): # 对 x y z t xyt xzt yzt 做异或运算，并取后128bits，
                # 这里可以转化为几个操作数先取后128bits再异或
                # 改变xyz的顺序不影响结果
    return (x ^ y ^ z ^ t ^ F(y,z,t) ^ F(z,t,x) ^ F(t,x,y)) & 0xffffffffffffffffffffffffffffffff

def hash(m:bytes) -> str:
    m = pad(m)
    H = b""
    for _ in range(len(m)//64): # 将m分块
        round_m = m[_*64:_*64+64] # 每个区块长度为64bytes
        a,b,c,d =   int.from_bytes(round_m[:16],byteorder='little'),\
                    int.from_bytes(round_m[16:16*2],byteorder='little'),\
                    int.from_bytes(round_m[16*2:16*3],byteorder='little'),\
                    int.from_bytes(round_m[16*3:16*4],byteorder='little') # 将64bytes长的区块继续分为四块
        tmpH = hex(R(a,b,c,d))[2:].rjust(8,'0').encode() # 进行一次R运算后，转化为16进制字符并格式化
        H = md5(H + tmpH).hexdigest().encode() # 将上一步得到的内容与之前的H进行合并取md5
    return H.decode()
```

通过观察，发现再每个64bits区块中，任意交换前三个16bytes长的小区块，对R运算的结果没有影响

长度16bytes，每个ASCII编码的字母长度为1bytes，则可以交换前16个字符与17到32的字符，即

```python
assert hash(b"@_string_w1th_thc4n_y0u_g1v3_m3_3_same_h4sh_a5_th1s_m3ss4ge?1f_u_g1ve_m3_i_wi11_giv3_y$u_@_flag!") \
    == hash(b"c4n_y0u_g1v3_m3_@_string_w1th_th3_same_h4sh_a5_th1s_m3ss4ge?1f_u_g1ve_m3_i_wi11_giv3_y$u_@_flag!")
```

然后将构造的字符串提交，即可获得flag