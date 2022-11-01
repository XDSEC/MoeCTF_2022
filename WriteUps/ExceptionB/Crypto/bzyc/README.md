# MoeCTF 2022 / 不止一次

## 初见

下载并打开附件

我：？

这是什么？？？

第一眼什么都没看出来，第二眼看出来这可能是一堆十六进制

完全没有思路，就直接锤了出题人~~(LGLJ:?)~~

> 我：这题和“一次就好”，是上下文连着的吗
> 
> Lglj：是

于是书接上文(?)，我推断出这些密文应该是通过xor得到的（因为一次就好就用到了xor）

## 探索

但是这完全看不出flag藏在哪里啊！

那就只能硬干了，先转成bytes再说

```python
data = [bytes.fromhex(x) for x in ["05010c1201035b3909530d7f3750035d304d41063a18021c3e550e3a075e41014211440f",
"0306141611460f250046593c355f035c2b1903017f5b130f3c5d003b4f52031643451618",
"050e1143170715230e46593d31110e413e5a0a013b14410c2a42452d0603140a4500175d",
"080106110d160f240e5c592b3152055d364814017f4c090f2b16063e0d1c0e171707015d",
"050e1143170715230e46593d31110e413e5a0a013b14410c2a42452d0603140a4500175d",
"0f1a114306030a3808401c2c744505567f4c12017f57074e3e1616360d150d061a101718",
"1e0a450c12461a6d125b1738385440462c5c41142d5d4c1d3757173a07520a064e451015",
"414f110b11461423041f0d3639544d433e5d414c106c31477f5f167f021c410659061604",
"4d000b06591212200412093e3011457c0b694844364b410f3116003100001813430c0b13",
"0e0400075846193815120b3a254404413a4a4110375d411b2c53453005520043440c0a1a",
"0b4f0443070f152a0d57542a27544d432d5c4c173759130b3b160e3a1a52150b56114414",
"1906080654161a29411a360b04184d5a2c19000a7f5d0f0d2d4f152b0a1d0f4343000715",
"4d1c0c0d130a1e6014411c7f2443081e2c5100163a5c41053a4f452b0b1315435e164413",
"144345171c035b220f57542b3d5c08132f5805447777353e76160c2c43130f43520b070f",
"094f4d2c2036526d0841593e3a11085d3c4b18142b510e007f42003c0b1c081242004409"]]
```

因为bytes没有xor运算符，所以我再定义一个xor函数

```python
def xor(a,b):
    assert type(a) is bytes and type(b) is bytes
    assert len(a) == len(b)
    return bytes([i^j for i,j in zip(a,b)])
```

没活了，那就随便xor点东西看看把

```python
for lin in data:
    print(xor(lin,b"a"*len(lin)))
```

```
b'd`ms`b:Xh2l\x1eV1b<Q, g[yc}_4o[f? `#p%n'
b'bguwp\'nDa\'8]T>b=Jxb`\x1e:rn]<aZ.3bw"$wy'
b'dop"vftBo\'8\\Ppo _;k`Zu mK#$Lgbuk$av<'
b'i`gplwnEo=8JP3d<W)u`\x1e-hnJwg_l}ovvf`<'
b'dop"vftBo\'8\\Ppo _;k`Zu mK#$Lgbuk$av<'
b'n{p"gbkYi!}M\x15$d7\x1e-s`\x1e6f/_wwWltlg{qvy'
b"\x7fk$ms'{\x0cs:vYY5!'M= uL<-|V6v[f3kg/$qt"
b' .pjp\'uBe~lWX5,"_< -q\rP&\x1e>w\x1ec} g8gwe'
b',ajg8ssAesh_Qp$\x1dj\x08)%W* nPwaPaayr"mjr'
b'oeaf9\'xYtsj[D%e [+ qV< zM2$Qd3a"%mk{'
b'j.e"fntKl65KF5,"L=-vV8rjZwo[{3tj7p%u'
b'xgig5w{H {Wjey,;Mxak\x1e<nlL.tJk|n""aft'
b',}mlrk\x7f\x01u }\x1eE"i\x7fM0aw[= d[.$Jjrt"?w%r'
b'u"$v}b:Cn65J\\=irN9d%\x16\x16T_\x17wmM"rn"3jfn'
b'h.,MAW3\x0ci 8_[pi<]*yuJ0oa\x1e#a]j}is#a%h'
```

虽然看起来都是乱七八糟的字符，但暂时可以看出，大部分输出都是printable的字符，所以可以大胆猜测一下，也许参与xor的数据都是printable的字符串

“我就是说，有没有一种可能，这里面某个字符串xor前就是flag”

依题意得flag的格式是`moectf{xxxxxx}`

那我们就构造数据进行xor，试试看

```python
for lin in data:
    print(xor(lin,b"moectf{"+b"x"*(len(lin)-8)+b"}"))
```

```
b'hnique Aq+u\x07O({%H59~B`zdF-vB\x7f&9y:i<r'
b"nique t]x>!DM'{$Sa{y\x07#kwD%xC7*{n;=ne"
b'hat can[v>!EIiv9F"ryCl9tR:=U~{lr=xo '
b'encrypt\\v$!SI*}%N0ly\x074qwSn~Fudvoo\x7fy '
b'hat can[v>!EIiv9F"ryCl9tR:=U~{lr=xo '
b'but req@p8dT\x0c=}.\x074jy\x07/\x7f6FnnNumu~bhoe'
b'se of a\x15j#o@@,8>T$9lU%4eO/oB\x7f*r~6=hh'
b", the o[|guNA,5;F%94h\x14I?\x07'n\x07zd9~!~ny"
b' one-tiX|jqFHi=\x04s\x110<N39wInxIxx`k;tsn'
b'cked, b@mjsB]<|9B29hO%9cT+=H}*x;<trg'
b'f a sinRu/,R_,5;U$4oO!ksCnvBb*ms.i<i'
b'time paQ9bNs|`5"Taxr\x07%wuU7mSrew;;x\x7fh'
b' single\x18l9d\x07\\;pfT)xnB$9}B7=Sskm;&n<n'
b'y, the Zw/,SE$pkW }<\x0f\x0fMF\x0entT;kw;*s\x7fr'
b'd (OTP)\x15p9!FBip%D3`lS)vx\x07:xDsdpj:x<t'
```

可以看到，每行的前面七个字符似乎是有意义的，尤其是有几行甚至出现了完整的单词，也就是说，这个思路也许没有错

再仔细观察，看到第一第二行，`hnique `和`nique t`，似乎是对的上的，只偏移了一个字符

那就按照这个思路进行爆破

```python
from string import printable

A = bytes.fromhex("05010c1201035b3909530d7f3750035d304d41063a18021c3e550e3a075e41014211440f")
B = bytes.fromhex("0306141611460f250046593c355f035c2b1903017f5b130f3c5d003b4f52031643451618")

known = "moectf{"
flag_len = 36
while len(known) < flag_len:
    for c in printable:
        flag = known + c + "a"*(flag_len - 1 - len(known))
        flag = flag.encode()
        a = xor(A,flag)
        b = xor(B,flag)
        if a[len(known)] == b[len(known)-1]:
            known+=c
            break
print(known)
```

激动的心，颤抖的手，按下执行

flag出来了捏