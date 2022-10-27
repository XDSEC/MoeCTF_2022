# Begin

写在前面。这次对萌新非常友好的moectf真的对我这种大菜鸟来说是一次获得进步的大好机会。从感兴趣到不断找资料再到做不出来锤出题人（不是），最终把题目做出来是真的一次大大的快乐。

感谢Rx Dx 云哥（云姐）三位大神在rev方面的指点（主要还是我太蠢了）

还感谢 polarnova b0y4nz 安权 大佬的指点！

总之是确实学到了什么的一场比赛，真的很开心！

# Classic crypto

## ABCDEFG~

`moectf{18 24 26 13 08 18 13 20 26 15 11 19 26 25 22 07 08 12 13 20}`

数字较小且都在 26 及以下，猜测是按照字母表排序，不过需要反着来下字母表即可。

```python
ascs = [18,24,26,13,8,18,13,20,26,15,11,19,26,25,22,7,8,12,13,20]
dict1="ABCDEFGHIJKLMNOPQRSTUVWXYZ"
dict2 = dict1[::-1]
for a in ascs:
    print(dict2[int(a-1)],end='')
#ICANSINGALPHABETSONG
```

`moectf{ICANSINGALPHABETSONG}`

## 小小凯撒

原文`kqEftuEUEftqOADDqoFRxmsOAzsDmFGxmFuAzE`

刚开始确实是尝试了很多办法，没办法解出来。后来逐渐放出了很多提示:

```
<0> 尝试若干次不正确的话，不妨换个思路？关注一下字母表，建议自己写脚本
<1> 解出flag之后请手动加上moectf{}
<2> 每个单词首字母大写，其余小写，无分隔
```

借助 quipquip 发现了` des this is the correct flag congratulations`，于是猜测原文是`yes this is the correct flag congratulations`。

但是这似乎不太符合出题人的意思。

于是编写脚本，检测每个字符的偏移量。最终将字典定为

```python
strings = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
```

这时将再去枚举所有偏移情况，终于发现了最终flag.

 `moectf{YesThisIsTheCorrectFlagCongratulations}`

## 凯撒变异了

原文`ZpyLfxGmelDeftewJwFbwDGssZszbliileadaa`

题目提示了 114514 用途应该是对字符进行偏移，但是规则不知。

好了，被折磨无限次后终于解出来了。

这个 114514 是用来对每个字符进行偏移的，但是我这个蠢蛋一直在尝试加法。把算法改成减法后一次就出来答案了。

```python
orgAll = 'ZpyLfxGmelDeftewJwFbwDGssZszbliileadaa'
strings = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
def getindex(text):
    x= strings.find(text)
    return x
def all52():
    for k in range(52):
        for i in range(len(orgAll)):
            index = getindex(orgAll[i])
            keyF = key[i%len(key)]
            if(index == -1):
                print(' ',end = '')
            else:
                print(strings[(index + k - keyF)%52],end ='')
        print()
        print()
all52()
```

`moectf{YouGetFlagCaesarIsEasyForYouahhhhZZZZZ}`

## 叫我棋王

原文:

```
1432145551541131233313542541343435232145215423541254443122112521452323
```

目测是一种棋盘密码，且最大不超过5. 于是用经典的波利比奥斯方阵按照默认编码得到了`qhqzeuacmnluwdssxmbybumufutcgawbymm`

再放入 quipquip 发现了其中某一条把最后一个词解码成了 chess， 而本题就与棋有关。 所以这很可能是正确的。

再拿到脚本分析偏移量，发现偏移量是 `20 6 20 6 6` 不是20就是6. 

```
m1: wnw fkaf is tracj yyds he has alazimf chess
m2: xox glbg jt usbdk zzet if ibt bmbajng diftt
mix:wow flag is track yyds he has amazing chess
```

人工混合得到了flag `moectf{wow_flag_is_track_yyds_he_has_amazing_chess}`

## Vigenère

`密文不贴了`

其中的 123456 说明很可能来自一篇文章。先上 quipquip 分析，发现它并不能解决。于是再去寻找其他工具(手撸可以等等，万一赌出来了呢？) 于是直接爆出来了`key = tfdvsjuz`

原文为:

```
information security, sometimes shortened to infosec, is the practice of protecting information by mitigating information risks. it is part of information risk management. it typically involves preventing or reducing the probability of unauthorized/inappropriate access to data, or the unlawful use, disclosure, disruption, deletion, corruption, modification, inspection, recording, or devaluation of information. it also involves actions intended to reduce the adverse impacts of such incidents. protected information may take any form, e.g. electronic or physical, tangible (e.g. paperwork) or intangible (e.g. knowledge). information security's primary focus is the balanced protection of the confidentiality, integrity, and availability of data (also known as the cia triad) while maintaining a focus on efficient policy implementation, all without hampering organization productivity. this is largely achieved through a structured risk management process that involves:
1. identifying information and related assets, plus potential threats, vulnerabilities, and impacts;
2. evaluating the risks
3. deciding how to address or treat the risks i.e. to avoid, mitigate, share or accept them
4. where risk mitigation is required, selecting or designing appropriate security controls and implementing them
5. monitoring the activities, making adjustments as necessary to address any issues, changes and improvement opportunities
6. i won't tell you that the flag is moectf attacking the vigenere cipher is interesting
to standardize this discipline, academics and professionals collaborate to offer guidance, policies, and industry standards on password, antivirus software, firewall, encryption software, legal liability, security awareness and training, and so forth. this standardization may be further driven by a wide variety of laws and regulations that affect how data is accessed, processed, stored, transferred and destroyed. however, the implementation of any standards and guidance within an entity may have limited effect if a culture of continual improvement isn't adopted.
```

来源为《Fundamental concepts of information security》的文章。

`moectf{attacking_the_vigenere_cipher_is_interesting}`

# Misc

## Hide-and-seek

![1661168763059.png](https://cdn.liil.cc/2022/08/22/63036c7bd20a7.png)

给了一份 pdf. 使用编辑器缩小图片即可得到flag.

## Misc方向指北

`.-- . .-.. ..--- --- -- . ..--.- ....- --- ..--.- -- .. ...-- -.-. ..--.- .---- ..- -.-. -.- -.-- -.-.--`

```
moectf{wel2ome_4o_mi3c_1ucky!}
```

## Rabbit

在文件尾找到了

```
########(=^-^=)###
U2FsdGVkX1+EPlLmNvaJK4Pe06nW0eLquWsUpdyv3fjXM2PcDBDKlXeKupnnWlFH
ewFEGmqpGyC1VdX8
```

后一串很像 base64 但前方 + 号很可能经过加密。于是在线搜索 `rabbit 解密`

输入原文即可。 我还以为前面的颜文字是 key, 试了好几次, 原来是可以不输入密码的。

`moectf{We1c0m3_t0_moectf_an7_3n7oy_y0urse1f}`

## 小纸条

![1661169133429.png](https://cdn.liil.cc/2022/08/22/63036deeb2bc9.png)

看出是猪圈密码。但是在边缘加了很多笔画，不太好辨认。尤其是最后一个方块，那竟然只是个左开的方框，折磨了我1个小时。

`moectf{ILOVEMYBIGBED}`

## 寻找黑客的家

```
大黑阔Mikato期末结束就迫不及待的回了家，并在朋友圈发出了“这次我最早”的感叹。那么你能从这条朋友圈找到他的位置吗？

moectf{照片拍摄地市名区名路名} (字母均小写)
例如：西安市长安区西沣路：moectf{xian_changan_xifeng}
```

![1661169355267.png](https://cdn.liil.cc/2022/08/22/63036ecd16459.png)

社工题。

最明显的应该是右上角的店名了 “汉明宫足浴理疗” 通过地图软件搜索找到了是深圳的一个地方。

![Screenshot_20220822-201438_高德地图.png](https://cdn.liil.cc/2022/08/22/63037351e2e70.png)

电话也没问题。

`moectf{shenzhen_longhua_qingquan}`

## Locked bass

zip 伪加密，直接踹开得到 base64`bW9lY3Rme04wd190aDFzX2k0X2FfYkBzc19VX2Nhbl91M2VfdG9fcGxhOX0=`

`moectf{N0w_th1s_i4_a_b@ss_U_can_u3e_to_pla9}`

## Nyanyanya!

在文件尾找到 LSB, 接着使用 stegsolve 得到flag.

`moectf{A_go0d_way_t0_h14e_in50rmation_in_ima9e3}`

## What do you recognize me by?

修复 PNG 文件头, 得到了一张二维码.

`moectf{You_r4c0gnize_%e!}`

## 想听点啥？

搜索`.mscz`文件怎么打开。发现是一款叫 MuseScore 3 的软件。

![1661174875095.png](https://cdn.liil.cc/2022/08/22/63038460300db.png)

得到压缩包密码: `MOECTFI1iKE`

```python
# this is not flag, but real flag will be encrypted in same algorithm.
flag = 'moectf{xxxxxxxxxxxxxxxxxxxxx}'

def encrypt(src: str) -> bytes:
    return bytes([ord(src[i]) ^ ord(src[i-1]) for i in range(1, len(src))])

with open('flag.txt', 'wb') as out:
    out.write(encrypt(flag))
```

对 flag 进行了一次简单的异或加密。 编写还原脚本得到 flag.

```python
# this is not flag, but real flag will be encrypted in same algorithm.
flag = 'moectf{xxxxxxxxxxxxxxxxxxxxx}'

def encrypt(src: str) -> bytes:
    return bytes([ord(src[i]) ^ ord(src[i-1]) for i in range(1, len(src))])

f = open("functions\\mister\\flag.txt",'rb')
bits = f.read()
f.close()
print(len(bits))

pre = ord('m')
print('m',end='')
for b in bits:
    c = b ^ pre
    print(chr(c),end='')
    pre = c
#moectf{Want_s0me_mor3_mus1c?}
```

`moectf{Want_s0me_mor3_mus1c?}`

## H■m■i■g

题目就给出了提示，汉明码。

这方面知识基础几乎为0，只知道可以用于纠错。于是去B站找[3b1b的视频](https://www.bilibili.com/video/BV1WK411N7kz?)学习一下。

题目只要求补充找到错误位置的函数，于是编写

```python
from functools import reduce
import numpy as np
err = reduce(lambda x,y : x^y , [i for i ,bit in enumerate(bitblock) if bit])
```

即可完成目标

> Once upon a time, there were 1023 identical bottles, 1022 of which were plain water and one of which was poison. Any creature that drinks the poison will die within a week. Now, with 10 mice and a week, how do you tell which bottle has poison in it? **moectf{Oh_Bin4ry_Mag1c_1s_s0o_c0O1!}** Great!

`moectf{Oh_Bin4ry_Mag1c_1s_s0o_c0O1!}`

## Bell202

安装 http://www.whence.com/minimodem/

```plain
minimodem --rx -f encoded.wav 1200
```

`moectf{zizi_U_he@rd_the_meanin9_beh1nd_the_s0und}`

# Reverse

## check in

拖入 IDA 寻找字符串直接找到 flag.

`moectf{Enjoy_yourself_in_Reverse_Engineering!!!}`

## Hex

010 Editor 找到文件尾的flag.

`moectf{Hello_Hex}`

## begin

还原程序:

```python
a = 'tv|zmA)kF(jFj)Fpwm*k*jmpw~88888d'
bit = bytes(a,encoding='ascii')

for i in a:
    k = 0x19
    c = k ^ ord(i)
    print(chr(c),end='')
#moectX0r_1s_s0_int3r3sting!!!!!}
```

可能是我程序写的有点问题，但还是能看出原 flag 的

`moectf{X0r_1s_s0_int3r3sting!!!!!}`

## base

拖入 IDA 后可以发现是对字符串进行了一个 base64 解码。可是不是标准的，又不想照抄一个解码函数出来。

于是选择动态调试，在解码后断点，直接提取 flag.

![1661176014971.png](https://cdn.liil.cc/2022/08/22/630388d26d267.png)

`moectf{qwqbase_qwq}`

## EquationPy

反编译 pyc 得到源码。

```python
#!/usr/bin/env python
# visit https://tool.lu/pyc/ for more information
# Version: Python 3.8

print('Maybe z3 can help you solve this challenge.')
print('Now give me your flag, and I will check for you.')
flag = input('Input your flag:')
if ...... {{ 源码这里是一大串判断函数 }}
    print('Congratulate!!!You are right!')
else:
    print('What a pity...Please try again >__<')

```

好家伙，竟然要解一个22元一次方程。引入 z3，然后格式化判断区域，交给 z3 即可得到 flag.

```python
from z3 import *


flag_0,flag_1,flag_2,flag_3,flag_4,flag_5,flag_6,flag_7,flag_8,flag_9,flag_10,flag_11,flag_12,flag_13,flag_14,flag_15,flag_16,flag_17,flag_18,flag_19,flag_20,flag_21, = Ints('flag_0 flag_1 flag_2 flag_3 flag_4 flag_5 flag_6 flag_7 flag_8 flag_9 flag_10 flag_11 flag_12 flag_13 flag_14 flag_15 flag_16 flag_17 flag_18 flag_19 flag_20 flag_21')

x = Solver()

x.add(flag_0 * 7072 + flag_1 * 2523 + flag_2 * 6714 + flag_3 * 8810 + flag_4 * 6796 + flag_5 * 2647 + flag_6 * 1347 + flag_7 * 1289 + flag_8 * 8917 + flag_9 * 2304 + flag_10 * 5001 + flag_11 * 2882 + flag_12 * 7232 + flag_13 * 3192 + flag_14 * 9676 + flag_15 * 5436 + flag_16 * 4407 + flag_17 * 6269 + flag_18 * 9623 + flag_19 * 6230 + flag_20 * 6292 + flag_21 * 57 == 10743134 )
x.add( flag_0 * 3492 + flag_1 * 1613 + flag_2 * 3234 + flag_3 * 5656 + flag_4 * 9182 + flag_5 * 4240 + flag_6 * 8808 + flag_7 * 9484 + flag_8 * 4000 + flag_9 * 1475 + flag_10 * 2616 + flag_11 * 2766 + flag_12 * 6822 + flag_13 * 1068 + flag_14 * 9768 + flag_15 * 1420 + flag_16 * 4528 + flag_17 * 1031 + flag_18 * 8388 + flag_19 * 2029 + flag_20 * 2463 + flag_21 * 32 == 9663091 )
x.add( flag_0 * 9661 + flag_1 * 1108 + flag_2 * 2229 + flag_3 * 1256 + flag_4 * 7747 + flag_5 * 5775 + flag_6 * 5211 + flag_7 * 2387 + flag_8 * 1997 + flag_9 * 4045 + flag_10 * 7102 + flag_11 * 7853 + flag_12 * 5596 + flag_13 * 6952 + flag_14 * 8883 + flag_15 * 5125 + flag_16 * 9572 + flag_17 * 1149 + flag_18 * 7583 + flag_19 * 1075 + flag_20 * 9804 + flag_21 * 72 == 10521461 )
x.add( flag_0 * 4314 + flag_1 * 3509 + flag_2 * 6200 + flag_3 * 5546 + flag_4 * 1705 + flag_5 * 9518 + flag_6 * 2975 + flag_7 * 2689 + flag_8 * 2412 + flag_9 * 8659 + flag_10 * 5459 + flag_11 * 7572 + flag_12 * 3042 + flag_13 * 9701 + flag_14 * 4697 + flag_15 * 9863 + flag_16 * 1296 + flag_17 * 1278 + flag_18 * 5721 + flag_19 * 5116 + flag_20 * 4147 + flag_21 * 52 == 9714028 )
x.add( flag_0 * 2310 + flag_1 * 1379 + flag_2 * 5900 + flag_3 * 4876 + flag_4 * 5329 + flag_5 * 6485 + flag_6 * 6610 + flag_7 * 7179 + flag_8 * 7897 + flag_9 * 1094 + flag_10 * 4825 + flag_11 * 8101 + flag_12 * 9519 + flag_13 * 3048 + flag_14 * 3168 + flag_15 * 2775 + flag_16 * 4366 + flag_17 * 4066 + flag_18 * 7490 + flag_19 * 5533 + flag_20 * 2139 + flag_21 * 87 == 10030960 )
x.add( flag_0 * 1549 + flag_1 * 8554 + flag_2 * 6510 + flag_3 * 6559 + flag_4 * 5570 + flag_5 * 1003 + flag_6 * 8562 + flag_7 * 6793 + flag_8 * 3509 + flag_9 * 4965 + flag_10 * 6111 + flag_11 * 1229 + flag_12 * 5654 + flag_13 * 2204 + flag_14 * 2217 + flag_15 * 5039 + flag_16 * 5657 + flag_17 * 9426 + flag_18 * 7604 + flag_19 * 5883 + flag_20 * 5285 + flag_21 * 17 == 10946682 )
x.add( flag_0 * 2678 + flag_1 * 4369 + flag_2 * 7509 + flag_3 * 1564 + flag_4 * 7777 + flag_5 * 2271 + flag_6 * 9696 + flag_7 * 3874 + flag_8 * 2212 + flag_9 * 6764 + flag_10 * 5727 + flag_11 * 5971 + flag_12 * 5876 + flag_13 * 9959 + flag_14 * 4604 + flag_15 * 8461 + flag_16 * 2350 + flag_17 * 3564 + flag_18 * 1831 + flag_19 * 6088 + flag_20 * 4575 + flag_21 * 9 == 10286414 )
x.add( flag_0 * 8916 + flag_1 * 8647 + flag_2 * 4522 + flag_3 * 3579 + flag_4 * 5319 + flag_5 * 9124 + flag_6 * 9535 + flag_7 * 5125 + flag_8 * 3235 + flag_9 * 3246 + flag_10 * 3378 + flag_11 * 9221 + flag_12 * 1875 + flag_13 * 1008 + flag_14 * 6262 + flag_15 * 1524 + flag_16 * 8851 + flag_17 * 4367 + flag_18 * 7628 + flag_19 * 9404 + flag_20 * 2065 + flag_21 * 9 == 11809388 )
x.add( flag_0 * 9781 + flag_1 * 9174 + flag_2 * 3771 + flag_3 * 6972 + flag_4 * 6425 + flag_5 * 7631 + flag_6 * 8864 + flag_7 * 9117 + flag_8 * 4328 + flag_9 * 3919 + flag_10 * 6517 + flag_11 * 7165 + flag_12 * 6895 + flag_13 * 3609 + flag_14 * 3878 + flag_15 * 1593 + flag_16 * 9098 + flag_17 * 6432 + flag_18 * 2584 + flag_19 * 8403 + flag_20 * 4029 + flag_21 * 30 == 13060508 )
x.add( flag_0 * 2511 + flag_1 * 8583 + flag_2 * 2428 + flag_3 * 9439 + flag_4 * 3662 + flag_5 * 3278 + flag_6 * 8305 + flag_7 * 1100 + flag_8 * 7972 + flag_9 * 8510 + flag_10 * 8552 + flag_11 * 9993 + flag_12 * 6855 + flag_13 * 1702 + flag_14 * 1640 + flag_15 * 3787 + flag_16 * 8161 + flag_17 * 2110 + flag_18 * 5320 + flag_19 * 3313 + flag_20 * 9286 + flag_21 * 74 == 10568195 )
x.add( flag_0 * 4974 + flag_1 * 4445 + flag_2 * 7368 + flag_3 * 9132 + flag_4 * 5894 + flag_5 * 7822 + flag_6 * 7923 + flag_7 * 6822 + flag_8 * 2698 + flag_9 * 3643 + flag_10 * 8392 + flag_11 * 4126 + flag_12 * 1941 + flag_13 * 6641 + flag_14 * 2949 + flag_15 * 7405 + flag_16 * 9980 + flag_17 * 6349 + flag_18 * 3328 + flag_19 * 8766 + flag_20 * 9508 + flag_21 * 65 == 12514783 )
x.add( flag_0 * 4127 + flag_1 * 4703 + flag_2 * 6409 + flag_3 * 4907 + flag_4 * 5230 + flag_5 * 3371 + flag_6 * 5666 + flag_7 * 3194 + flag_8 * 5448 + flag_9 * 8415 + flag_10 * 4525 + flag_11 * 4152 + flag_12 * 1467 + flag_13 * 5254 + flag_14 * 2256 + flag_15 * 1643 + flag_16 * 9113 + flag_17 * 8805 + flag_18 * 4315 + flag_19 * 8371 + flag_20 * 1919 + flag_21 * 2 == 10299950 )
x.add( flag_0 * 6245 + flag_1 * 8783 + flag_2 * 6059 + flag_3 * 9375 + flag_4 * 9253 + flag_5 * 1974 + flag_6 * 8867 + flag_7 * 6423 + flag_8 * 2577 + flag_9 * 6613 + flag_10 * 2040 + flag_11 * 2209 + flag_12 * 4147 + flag_13 * 7151 + flag_14 * 1011 + flag_15 * 9446 + flag_16 * 4362 + flag_17 * 3073 + flag_18 * 3006 + flag_19 * 5499 + flag_20 * 8850 + flag_21 * 23 == 11180727 )
x.add( flag_0 * 1907 + flag_1 * 9038 + flag_2 * 3932 + flag_3 * 7054 + flag_4 * 1135 + flag_5 * 5095 + flag_6 * 6962 + flag_7 * 6481 + flag_8 * 7049 + flag_9 * 5995 + flag_10 * 6233 + flag_11 * 1321 + flag_12 * 4455 + flag_13 * 8181 + flag_14 * 5757 + flag_15 * 6953 + flag_16 * 3167 + flag_17 * 5508 + flag_18 * 4602 + flag_19 * 1420 + flag_20 * 3075 + flag_21 * 25 == 10167536 )
x.add( flag_0 * 1489 + flag_1 * 9236 + flag_2 * 7398 + flag_3 * 4088 + flag_4 * 4131 + flag_5 * 1657 + flag_6 * 9068 + flag_7 * 6420 + flag_8 * 3970 + flag_9 * 3265 + flag_10 * 5343 + flag_11 * 5386 + flag_12 * 2583 + flag_13 * 2813 + flag_14 * 7181 + flag_15 * 9116 + flag_16 * 4836 + flag_17 * 6917 + flag_18 * 1123 + flag_19 * 7276 + flag_20 * 2257 + flag_21 * 65 == 10202212 )
x.add( flag_0 * 2097 + flag_1 * 1253 + flag_2 * 1469 + flag_3 * 2731 + flag_4 * 9565 + flag_5 * 9185 + flag_6 * 1095 + flag_7 * 8666 + flag_8 * 2919 + flag_9 * 7962 + flag_10 * 1497 + flag_11 * 6642 + flag_12 * 4108 + flag_13 * 6892 + flag_14 * 7161 + flag_15 * 7552 + flag_16 * 5666 + flag_17 * 4060 + flag_18 * 7799 + flag_19 * 5080 + flag_20 * 8516 + flag_21 * 43 == 10435786 )
x.add( flag_0 * 1461 + flag_1 * 1676 + flag_2 * 4755 + flag_3 * 7982 + flag_4 * 3860 + flag_5 * 1067 + flag_6 * 6715 + flag_7 * 4019 + flag_8 * 4983 + flag_9 * 2031 + flag_10 * 1173 + flag_11 * 2241 + flag_12 * 2594 + flag_13 * 8672 + flag_14 * 4810 + flag_15 * 7963 + flag_16 * 7749 + flag_17 * 5730 + flag_18 * 9855 + flag_19 * 5858 + flag_20 * 2349 + flag_21 * 71 == 9526385 )
x.add( flag_0 * 9025 + flag_1 * 9536 + flag_2 * 1515 + flag_3 * 8177 + flag_4 * 6109 + flag_5 * 4856 + flag_6 * 6692 + flag_7 * 4929 + flag_8 * 1010 + flag_9 * 3995 + flag_10 * 3511 + flag_11 * 5910 + flag_12 * 3501 + flag_13 * 3731 + flag_14 * 6601 + flag_15 * 6200 + flag_16 * 8177 + flag_17 * 5488 + flag_18 * 5957 + flag_19 * 9661 + flag_20 * 4956 + flag_21 * 48 == 11822714 )
x.add( flag_0 * 4462 + flag_1 * 1940 + flag_2 * 5956 + flag_3 * 4965 + flag_4 * 9268 + flag_5 * 9627 + flag_6 * 3564 + flag_7 * 5417 + flag_8 * 2039 + flag_9 * 7269 + flag_10 * 9667 + flag_11 * 4158 + flag_12 * 2856 + flag_13 * 2851 + flag_14 * 9696 + flag_15 * 5986 + flag_16 * 6237 + flag_17 * 5845 + flag_18 * 5467 + flag_19 * 5227 + flag_20 * 4771 + flag_21 * 72 == 11486796 )
x.add( flag_0 * 4618 + flag_1 * 8621 + flag_2 * 8144 + flag_3 * 7115 + flag_4 * 1577 + flag_5 * 8602 + flag_6 * 3886 + flag_7 * 3712 + flag_8 * 1258 + flag_9 * 7063 + flag_10 * 1872 + flag_11 * 9855 + flag_12 * 4167 + flag_13 * 7615 + flag_14 * 6298 + flag_15 * 7682 + flag_16 * 8795 + flag_17 * 3856 + flag_18 * 6217 + flag_19 * 5764 + flag_20 * 5076 + flag_21 * 93 == 11540145 )
x.add( flag_0 * 7466 + flag_1 * 8442 + flag_2 * 4822 + flag_3 * 7639 + flag_4 * 2049 + flag_5 * 7311 + flag_6 * 5816 + flag_7 * 8433 + flag_8 * 5905 + flag_9 * 4838 + flag_10 * 1251 + flag_11 * 8184 + flag_12 * 6465 + flag_13 * 4634 + flag_14 * 5513 + flag_15 * 3160 + flag_16 * 6720 + flag_17 * 9205 + flag_18 * 6671 + flag_19 * 7716 + flag_20 * 1905 + flag_21 * 29 == 12227250 )
x.add( flag_0 * 5926 + flag_1 * 9095 + flag_2 * 2048 + flag_3 * 4639 + flag_4 * 3035 + flag_5 * 9560 + flag_6 * 1591 + flag_7 * 2392 + flag_8 * 1812 + flag_9 * 6732 + flag_10 * 9454 + flag_11 * 8175 + flag_12 * 7346 + flag_13 * 6333 + flag_14 * 9812 + flag_15 * 2034 + flag_16 * 6634 + flag_17 * 1762 + flag_18 * 7058 + flag_19 * 3524 + flag_20 * 7462 + flag_21 * 11 == 11118093)

check = x.check()
print(check)
model = x.model()
print(model)
```

`moectf{z3_i5_he1pful!}`

## D_flat

题目提醒这是个 C#.

但是我根本不懂这玩意的特殊性，无脑放到 IDA ，找了半天也不能找到正常的东西。

后来经过DX和Rx提醒，找到了 .NET 专用的反编译工具。

遂得到了正常点的反编译代码

```c#
private static void Main()
{
    int num2 = 0;
    int[] numArray = new int[] { 
        0x6d, 0x6f, 0x65, 0x63, 0x74, 0x66, 0x7b, 0x44, 0x5f, 0x66, 0x6c, 0x61, 0x74, 0x65, 0x5f, 0x69,
        0x73, 0x5f, 0x43, 0x5f, 0x73, 0x68, 0x61, 0x72, 0x70, 0x21, 0x7d
    };
    Console.WriteLine("In music theory, there is a note that has the same pitch as D flat.");
    Console.WriteLine("Do you know it?\nNow plz input your flag:");
    string str = Console.ReadLine();
    byte[] bytes = Encoding.get_ASCII().GetBytes(str);
    for (int i = 0; i < str.Length; i++)
    {
        if (numArray[i] == bytes[i])
        {
            num2++;
        }
    }
    if (num2 == numArray.Length)
    {
        Console.WriteLine("TTTTTQQQQQQLLLLLLL!!! This is your flag!");
    }
    else
    {
        Console.WriteLine("QwQ, plz try again.");
    }
}
```

接下来就简单了。

```python
l = [0x6d, 0x6f, 0x65, 0x63, 0x74, 0x66, 0x7b, 0x44, 0x5f, 0x66, 0x6c, 0x61, 0x74, 0x65, 0x5f, 0x69,0x73, 0x5f, 0x43, 0x5f, 0x73, 0x68, 0x61, 0x72, 0x70, 0x21, 0x7d]

for i in l:
    print(chr(int(i)),end='')
#moectf{D_flate_is_C_sharp!}
```

`moectf{D_flate_is_C_sharp!}`

## Android Cracker

安卓的事情当然在安卓系统更趁手啦(打死)

![1661176858208.png](https://cdn.liil.cc/2022/08/22/63038c2a19dd9.png)

`moectf{Andr01d_1s_so00oo_e@sy_t0_cr4ck!!!}`

## ezTea

标准的 Tea 加密算法。

还需要处理的就是字符方面的大小端序的逆转。

```python
from ctypes import *
from Crypto.Util.number import *
import binascii
def decrypt(v, k):
    v0, v1 = c_uint32(v[0]), c_uint32(v[1])
    delta = 0xd33b470 
    k0, k1, k2, k3 = k[0], k[1], k[2], k[3]
    total = c_uint32(delta * 32)
    for i in range(32):                       
        v1.value -= ((v0.value<<4) + k2) ^ (v0.value + total.value) ^ ((v0.value>>5) + k3) 
        v0.value -= ((v1.value<<4) + k0) ^ (v1.value + total.value) ^ ((v1.value>>5) + k1)  
        total.value -= delta
    return v0.value, v1.value   
key = [1, 2, 3, 4]
v01 = ['17', '65', '54', '89']
v02 = ['ed', '65', '46', '32']
v11 = ['3d', '58', 'a9', 'fd']
v12 = ['e2', '5e', '61', '97']
v21 = ['e4', '60', 'f1', '91']
v22 = ['73', 'e9', 'e9', 'a2']
v31 = ['59', 'cb', '9a', '99']
v32 = ['ec', 'b1', 'e1', '7d']
data = ''
for i in v01:
    data += i
data = binascii.unhexlify(data)
data = data[::-1]
v0 = bytes_to_long(data)
data2 = ''
for i in v02:
    data2 += i
data2 = binascii.unhexlify(data2)
data2 = data2[::-1]
v1 = bytes_to_long(data2)
value = [v0,v1]
res = decrypt(value, key)
print(str(long_to_bytes(res[0])[::-1],encoding='ascii'),end='')
print(str(long_to_bytes(res[1])[::-1],encoding='ascii'),end='')
data = ''
for i in v11:
    data += i
data = binascii.unhexlify(data)
data = data[::-1]
v0 = bytes_to_long(data)
data2 = ''
for i in v12:
    data2 += i
data2 = binascii.unhexlify(data2)
data2 = data2[::-1]
v1 = bytes_to_long(data2)
value = [v0,v1]
res = decrypt(value, key)
print(str(long_to_bytes(res[0])[::-1],encoding='ascii'),end='')
print(str(long_to_bytes(res[1])[::-1],encoding='ascii'),end='')
data = ''
for i in v21:
    data += i
data = binascii.unhexlify(data)
data = data[::-1]
v0 = bytes_to_long(data)
data2 = ''
for i in v22:
    data2 += i
data2 = binascii.unhexlify(data2)
data2 = data2[::-1]
v1 = bytes_to_long(data2)
value = [v0,v1]
res = decrypt(value, key)
print(str(long_to_bytes(res[0])[::-1],encoding='ascii'),end='')
print(str(long_to_bytes(res[1])[::-1],encoding='ascii'),end='')
data = ''
for i in v31:
    data += i
data = binascii.unhexlify(data)
data = data[::-1]
v0 = bytes_to_long(data)
data2 = ''
for i in v32:
    data2 += i
data2 = binascii.unhexlify(data2)
data2 = data2[::-1]
v1 = bytes_to_long(data2)
value = [v0,v1]
res = decrypt(value, key)
print(str(long_to_bytes(res[0])[::-1],encoding='ascii'),end='')
print(str(long_to_bytes(res[1])[::-1],encoding='ascii'),end='')
```

有很大优化空间的不想动的烂代码。

`moectf{Th3_TEA_!S_s0_t4s7y~~!!!}`

## chicken_soup

### 去除花指令

由于是完全初学，这里记录一下去除过程。

![1661666181955.png](https://cdn.liil.cc/2022/08/28/630b03881e7f8.png)

第一个加密函数爆红。发现两个跳转都指向一个地址，所以先把这个 jmp 按 d 拆开。

![1661666262819.png](https://cdn.liil.cc/2022/08/28/630b03de24d1e.png)

对垃圾部分按 Ctrl + n NOP 掉，然后在拖选中这一行，右键分析。

![1661666328647.png](https://cdn.liil.cc/2022/08/28/630b041b3e566.png)

就会变成上图这样。

接下来再用同样的方法 NOP 上面的 1009 100B 两行。

![1661666399226.png](https://cdn.liil.cc/2022/08/28/630b04613a2f4.png)

接下来对着 1000 行按 p。 让它变成正常可解析函数。

![1661666449320.png](https://cdn.liil.cc/2022/08/28/630b049a260d0.png)

![1661666474227.png](https://cdn.liil.cc/2022/08/28/630b04ad10008.png)

就可以愉快的查看伪代码啦。

### 写出还原代码

#### Step 1

第一部分的逆向代码还算简单。

已知：

```python
c1 = x1 + x2   恢复方法: x1 = c1 - x2
c2 = x2 + x3   恢复方法: x2 = c2 - x3
cn = xn + xn+1 恢复方法: xn = cn - x(n+1)
```

得到：

```python
t  =[220,212,200,215,218,225,235,164,168,215,203,199,207,226,162,151,217,166,161,204,211,164,143,195,151,150,147,157,221,217,154,150,196,200,221,149,158,125] # 从Step 2 获得。

i = 37
while 1:
    i-=1
    if(i == 0):
        break
    t[i] = t[i] - t[i+1]
print(len(t))

for p in t:
    print(chr(p),end='')
#Üoectf{p4tch_pr0gr4m_t0_d3c0mpi1e_it!}
#手动修改第一个即可 moectf{p4tch_pr0gr4m_t0_d3c0mpi1e_it!}
```

#### Step 2

源代码：

```c++
unsigned int __cdecl sub_401080(const char *a1)
{
  unsigned int result; // eax
  unsigned int i; // [esp+18h] [ebp-8h]

  for ( i = 0; ; ++i )
  {
    result = i;
    if ( i >= strlen(a1) )
      break;
    a1[i] = (16 * a1[i]) | ((int)(unsigned __int8)a1[i] >> 4);
  }
  return result;
```

这里主要坑在于 char 的长度只有 8 位. 超过会溢出。

而第 11 行代码 OR 运算的左边相当于左移4位，OR 运算的右边相当于右移4位。再加上中间的 OR 运算，相当于把这 8 位数的前后4位互换了位置。(感谢云之君和DX3906两位大佬的引导和提醒，在这卡死了好久，没发现类型问题QAQ)

接下来就可以很顺利的写出还原代码了:

```python
c = [205,  77, 140, 125, 173,  30, 190,  74, 138, 125, 188, 124, 252,  46,  42, 121, 157,  106,  26, 204, 61,  74, 248,  60, 121, 105,  57, 217, 221, 157, 169, 105,  76, 140, 221,  89, 233, 215] # 来自 IDA 提取被比较的字符串

for y in c:
  char = bin(y).replace('0b','').rjust(8,'0')
  char2 = char[4:] + char[:4]
  # print(char,char2)
  y2 = int('0b'+char2,2)
  print(y2,end=',')
# 220,212,200,215,218,225,235,164,168,215,203,199,207,226,162,151,217,166,161,204,211,164,143,195,151,150,147,157,221,217,154,150,196,200,221,149,158,125
```

`moectf{p4tch_pr0gr4m_t0_d3c0mpi1e_it!}`

## fake_key

提示：`Unless you debug to get the key and random numbers...`t

说明需要得到完整的 key 和相关的随机数才能还原 flag.

![1661681628702.png](https://cdn.liil.cc/2022/08/28/630b3fde85a38.png)

对 key 进行一次提取，就可以得到完整的key了 `key = "yunzh1junTCL,trackYYDS"`

接下来的第一段加密很好理解，直接贴出还原代码:

```python
# re p1
strM = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
for i in range(len(str)): # str 来自接下来的第二段脚本
    strM[i] = keylist[i%len(keylist)] ^ org[i]

# 打印
for i in strM:
    print(chr(i),end='')
print()
```

第二段是做了一次与随机数的求和操作。

可以通过先输入一段已知字符(如`12312312312312312312312323123`)，然后再写脚本，判断每个值偏移了多少。

再把这个值记下即可。 尝试两次发现一样，所以是伪随机，直接从被比较的文本减去这个值即可。脚本如下:

```python
# Env -----START-----
key = 'yunzh1junTCL,trackYYDS'
keylist = []
for k in key:
    keylist.append(ord(k))

str = '12312312312312312312312323123'
strlist = []
for s in str:
    strlist.append(ord(s))
# Env -----END-----


# p1
for i in range(len(str)):
    strlist[i] ^= keylist[i%len(keylist)]

# 打印
for i in strlist:
    print(chr(i),end=',')
print()

# re p1
strM = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
for i in range(len(str)):
    strM[i] = keylist[i%len(keylist)] ^ strlist[i]

# 打印
for i in strM:
    print(chr(i),end='')
print()

str2list = [73,  78,  97,  75,  99,   6,  99,  79,  95, 105, 
  118, 132,  30,  77,  66,  81,  86,  90, 111, 113, 
  120, 102,  77,  73,  94,  75,  90,   9,  97]

for i in range(len(str2list)):
    print(strlist[i] - str2list[i],end=',')
    
print()
# randomList = [-1,-7,-4,0,-9,-4,-8,-8,-2,-4,-5,-5,-1,-7,-1,-1,-5,-2,-7,-6,-1,-4,-2,-3,-2,-2,-1,-6,-8]
```

结合第一步，第二部和已知的随机数表，即可写出最终脚本

```python
# Env -----START-----
key = 'yunzh1junTCL,trackYYDS'
keylist = []
for k in key:
    keylist.append(ord(k))

str = '12312312312312312312312323123'
strlist = []
for s in str:
    strlist.append(ord(s))
# Env -----END-----
randomList = [-1,-7,-4,0,-9,-4,-8,-8,-2,-4,-5,-5,-1,-7,-1,-1,-5,-2,-7,-6,-1,-4,-2,-3,-2,-2,-1,-6,-8,]

org=  [ 21,  33,  15,  25,  37,  91,  25,  57,  95,  58, 
   59,  48, 116,   7,  67,  63,   9,  90,  52,  12, 
  116,  63,  30,  45,  39,  33,  18,  22,  31,]

# print(randomList)
for i in range(len(org)):
    org[i] = org[i] - -1*randomList[i] 

# re p1
strM = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
for i in range(len(str)):
    strM[i] = keylist[i%len(keylist)] ^ org[i]

# 打印
for i in strM:
    print(chr(i),end='')
print()
#moectf{D3bug_t0_g3t_7he_Key!}
```

## Art

使用 UPX 解压工具后就可以轻松查看反编译伪代码了。

![1661750685058.png](https://cdn.liil.cc/2022/08/29/630c4d9d68d84.png)

主要解题思路在红框内。

于是只需要提取出来被比较的 Str2. 然后写一个脚本，枚举前后两个是否符合条件，再直接输出。

这里会出现下一个问题就是对于每一个字都会有2个字的多解。由于已知 flag 的固定格式 `moectf{...}` 再由于这个过程的连续性。只需要在第一组解后找到结果为 m,o 的组，接下来全程都找第二个字符，并且最终连接起来即可。

`moectf{Art_i5_b14s7ing!!!!!}`

## gogogo!

![1661503114518.png](https://cdn.liil.cc/2022/08/26/6308868d18c1a.png)

首先从 main_flagHandler 看起。发现在输入 flag 后会进入 main_check 检查 flag. 然后输出正确与否。

![1661503223751.png](https://cdn.liil.cc/2022/08/26/630886fac8868.png)

跟进去发现进行了一次 AES CBC 加密，同时还送了初始向量。

![1661503265647.png](https://cdn.liil.cc/2022/08/26/63088723bd697.png)

F5 后直接给了 IV 好开心。 `IV = "---moeCTF2022---"`

但是接下来死活没找到 K 值。

![1661503416597.png](https://cdn.liil.cc/2022/08/26/630887bb70178.png)

继续往下看找到了很像密文的东西，但是进去看了下发现长度不太对 只有 95。

![1661503718637.png](https://cdn.liil.cc/2022/08/26/630888e930543.png)

把下面的 c 接上去后才是96. 

同时这里应当注意大小端序，但这里好像是正常的。 实在不行后面倒着试一次就行。

```go
k = 200c2c3ef00f31999df93d6919aa33e42dde307be02017ebf47067099ed0bddc525d5dba0f83c122159b89ae715907c
```

得到了上述两个信息，到现在唯一不知道的就是 K 了。



![1661503675320.png](https://cdn.liil.cc/2022/08/26/630888be50e78.png)

于是在胡乱尝试(人工爆破)时发现突然能解密成功了

当时差点直接跳过去，还好出现了这个魔法棒提醒。点一下，HEX 就变成文本 flag 啦！

`moeCTF{g0l@ng_1s_4n_1nte^est1n9_lan9ua9e}`

# Web

## ezhtml

![1661177153731.png](https://cdn.liil.cc/2022/08/22/63038d4360d1a.png)

`moectf{W3lc0me_to_theWorldOf_Web!}`

## God_of_Aim

第一段只需要得到10分，正常点一点就能得到前一段 flag `moectf{Oh_you_can_a1m_`

第二段的话，我真的在群里见到了一位通过脚本一直点到100000分获得后半段。

当然也可以使用我们的法二：

aimtrainer.js 经过了一次混淆，首先试试能不能一次就逆向出来。

```javascript
class AimTrainer {
    constructor({
        _0xf777x2,
        _0xf777x3
    }) {
        this['aimTrainerEl'] = document['getElementById']('aim-trainer');
        this['scoreEl'] = document['getElementById']('score');
        this['score'] = 0;
        this['aimscore'] = 0;
        this['delay'] = _0xf777x2 || 1000;
        this['targetSize'] = _0xf777x3 || 30;
        this['aimscoreEL'] = document['getElementById']('aimscore')
    }
    createTarget() {
        const _0xf777x5 = new Target({
            delay: this['delay'],
            targetSize: this['targetSize'],
            aimTrainerEl: this['aimTrainerEl'],
            onTargetHit: () = > {
                this['setScore'](this['score'] + 1)
            }
        });
        _0xf777x5['start']()
    }
    setScore(_0xf777x7) {
        this['score'] = _0xf777x7;
        this['scoreEl']['innerHTML'] = this['score']
    }
    setAimScore(_0xf777x7) {
        this['aimscore'] = _0xf777x7;
        this['aimscoreEL']['innerHTML'] = _0xf777x7
    }
    start1() {
        this['setScore'](0);
        this['setAimScore'](10);
        this['aimTrainerEl']['style']['position'] = 'relative';
        if (!this['timer']) {
            this['timer'] = setInterval(() = > {
                this['createTarget']();
                this['scoreEl']['innerHTML'] = this['score'];
                this['checkflag1']()
            }, this['delay'])
        } else {
            return
        }
    }
    start2() {
        this['targetSize'] = 10;
        this['delay'] = 400;
        this['setScore'](0);
        this['setAimScore'](100000);
        this['aimTrainerEl']['style']['position'] = 'relative';
        if (!this['timer']) {
            this['timer'] = setInterval(() = > {
                this['createTarget']();
                this['scoreEl']['innerHTML'] = this['score'];
                this['checkflag2']()
            }, this['delay'])
        } else {
            return
        }
    }
    checkflag1() {
        if (this['score'] == this['aimscore']) {
            this['stop']();
            alert('moectf{Oh_you_can_a1m_');
            alert('\u4F60\u5DF2\u7ECF\u5B66\u4F1A\u7784\u51C6\u4E86\uFF01\u8BD5\u8BD5\u770B:');
            this['start2']()
        }
    }
    checkflag2() {
        if (this['score'] == this['aimscore']) {
            this['stop']();
            alert('and_H4ck_Javascript}')
        }
    }
    stop() {
        this['aimTrainerEl']['innerHTML'] = '';
        if (this['timer']) {
            clearInterval(this['timer']);
            this['timer'] = 0
        } else {
            return
        }
    }
}
```

直接找到了后半段`and_H4ck_Javascript}`

`moectf{Oh_you_can_a1m_and_H4ck_Javascript}`

## cookiehead

主要坑在了修改 `X-Forwarded-For:127.0.0.1` 后没有继续给提示(结果在我写wp的时候又正常了)。

![1661692391072.png](https://cdn.liil.cc/2022/08/28/630b69e8d0c34.png)

接下来应该把 cookie 中 login 的值修改为1.

![1661692464991.png](https://cdn.liil.cc/2022/08/28/630b6a331eb15.png)

接下来修改`Referer:http://127.0.0.1/index.php`即可得到 flag.

`moectf{th1s_is_http_protocolllll}`

## What are you uploading

![1661682392529.png](https://cdn.liil.cc/2022/08/28/630b42da61dd7.png)

先随便上传一个图片，然后把文件名改成`f1lg.php`即可

`moectf{A0_Qua1_D0ne!}`

## baby_file

payload:`?file=php://filter/convert.base64-encode/resource=flag.php`

```php
<?php
Hey hey, reach the highest city in the world! Actually I am ikun!!;
moectf{Y0u_are_t00_baby_la};
?>
```

## ezphp

![1661692649841.png](https://cdn.liil.cc/2022/08/28/630b6af058e9c.png)

payload:

GET: `giveme=flag&flag=giveme`

POST: `flag=$giveme`

`moectf{Wan0g_Yi1g_Chu0}`

# Crypto

说实话从0开始学密码学确实相比其他部分来讲痛苦太多了。

于是找了找看有没有能做的题，慢慢来咯。

## 一次就好

仔细研究了下，其实这道似乎是比较正常的简单题。

给了n e c 求 m. 那么目标是先分解 N 得到 p,q.  使用在线工具就可以了。顺手算一下d

接下来就好办了，已知`key = strxor(flag.encode(), c)` 

那么这一步的逆向方法是 `msg=strxor(c,key)`

```python
crypto = 127749242340004016446001520961422059381052911692861305057396462507126566256652316418648339729479729456613704261614569202080544183416817827900318057127539938899577580150210279291202882125162360563285794285643498788533366420857232908632854569967831654923280152015070999912426044356353393293132914925252494215314
N = 164395171965189899201846744244839588935095288852148507114700855000512464673975991783671493756953831066569435489213778701866548078207835105414442567008315975881952023037557292470005621852113709605286462434049311321175270134326956812936961821511753256992797013020030263567313257339785161436188882721736453384403

p=12821668064849826676074701213910298504451620184307130249376361333490782040849300923713647818247010549622664747770828229853003308659470956068108542842690393
q=12821668064849826676074701213910298504451620184307130249376361333490782040849300923713647818247010549622664747770828229853003308659470956068108542842690571
d = 105494657249615124293648880418099298903739375741427859304146652393328230073526928459558544660915976003412487280992030106439103803608781500424337345287421389493495735389457682135637699745021382802466553575614359848312291960153737214222158032304698209920162981491266433689104734041346213344207132627364583352193

m = 23509113917433969361844992588522336728834624213530516390210963742924904254640889821566186341742563884273817964359

kk = long_to_bytes(m)
print(len(kk))
print(kk)
print(strxor(c,kk))
#moectf{W0w_y02_k5ow_w6at_1s_one_t1m3_pa7}######'
```

代入，得结果。`moectf{W0w_y02_k5ow_w6at_1s_one_t1m3_pa7}`

## 0rsa0

前一段做一次低质数攻击

```python
import gmpy2
from Crypto.Util.number import *
def di(c,e,n):
    k=0
    while 1:
        mm=c+ n*k
        result,flag= gmpy2.iroot(mm,e)
        if flag==1:
            return result
        k+=1

n1=133024413746207623787624696996450696028790885302997888417950218110624599333002677651319135333439059708696691802077223829846594660086912881559705074934655646133379015018208216486164888406398123943796359972475427652972055533125099746441089220943904185289464863994194089394637271086436301059396682856176212902707
e1=3
c1=1402983421957507617092580232325850324755110618998641078304840725502785669308938910491971922889485661674385555242824
m1 = di(c1,e1,n1)

print(long_to_bytes(m1))
'T8uus_23jkjw_asr'
```

后一段来一次暴力破p

```python
import gmpy2
from Crypto.Util.number import *

n=159054389158529397912052248500898471690131016887756654738868415880711791524038820158051782236121110394481656324333254185994103242391825337525378467922406901521793714621471618374673206963439266173586955520902823718942484039624752828390110673871132116507696336326760564857012559508160068814801483975094383392729
e=65537
c=37819867277367678387219893740454448327093874982803387661058084123080177731002392119369718466140559855145584144511271801362374042596420131167791821955469392938900319510220897100118141494412797730438963434604351102878410868789119825127662728307578251855605147607595591813395984880381435422467527232180612935306
dp=947639117873589776036311153850942192190143164329999603361788468962756751774397111913170053010412835033030478855001898886178148944512883446156861610917865
d=112673132292809952049452029981578534975449327708485137447651022715075844687657754621934358333371357724250505462769056545752204665017972795824545230202262258523689376620751673768750777043617063994934859824389979754140336649898358655901474231057638977010424916030921144337867991777837053005298636406581858927521

for x in range(1, e):
    if(e*dp%x==1):
        p=(e*dp-1)//x+1
        if(n%p!=0):
            continue
        print("p:{}".format(p))
        q=n//p
        print("q:{}".format(q))
        phin=(p-1)*(q-1)
        d=gmpy2.invert(e, phin)
        m=pow(c, d, n)
        
            
        print("m:",m)
        #print(hex(m)[2:])
        print(long_to_bytes(m))
'_3d32awd!5f&#@sd'
```

连起来就是 flag 了 `moectf{T8uus_23jkjw_asr_3d32awd!5f&#@sd}`

## ez_cbc

首先是看到块加密想了想能不能正向爆破，经过尝试flag花括号内部分长度为 37-41 正向暴力破解不太现实。

于是找到了加密的两个关键部分

```
c0 = (IV ^ bytes_to_long(plain_block[0])) ^ K
```

这里做出了第一个块:  `密文块 = 明文块 ^ IV ^ k `

所以，想要逆向得到明文块: `明文块 = 密文块 ^ IV ^ k`

现在唯一的问题是 k 未知。

k 的取值范围是`1 ~ 1073741824` 虽然也是个非常大的数，但比起正向爆破来讲，硬跑还是有可能走出来的。 

于是先按间隔大点的数跳着跑了一段，发现是有一定规律的。

```python
b'Ol\xca[' 10000000
b'OS\x84\x1b' 11000000
b'OCG\xdb' 12000000
b'O2\x01\x9b' 13000000
b'O!\xc3[' 14000000
b'O\x10\xbd\x1b' 15000000
b'O\x00x\xdb' 16000000
b'N\xf7:\x9b' 17000000
b'N\xe6\xf4[' 18000000
b'N\xd5\xb6\x1b' 19000000
b'N\xc5q\xdb' 20000000
b'N\xb43\x9b' 21000000
b'N\xbb\xed[' 22000000
b'N\xaa\xaf\x1b' 23000000
b'N\x9aj\xdb' 24000000
b'N\x89$\x9b' 25000000
b'Nx\xe6[' 26000000
b'No\xa0\x1b' 27000000
b'N_c\xdb' 28000000
```

所以目标变成了锁定开头是小写 m 所在的区域.

```python
b'm\xb0e\x8c' 574896471
b'm\xb0<\xbc' 574906471
b'm\xb0\xdb\xac' 574916471
b'm\xb0\xf2\\' 574926471
b'm\xb0\x89L' 574936471
b'm\xb0\xa0|' 574946471
b'm\xb1\x7fl' 574956471
```

经过不断尝试，总算是找到了。

接下来交给暴力代码硬跑即可，坐等 k 值.

```python
# 找出 k 的精确值
for trying in range(578806471,1073741824):
    block0 = 748044282 
    re =  block0 ^ IV ^ trying
    bytes = long_to_bytes(re)
    print(bytes)
    if(b'moec' == bytes):
        print(trying)
        break
# k = 580598200
```

很好，接下来处理后面的几个块，先来看加密算法。

```
c[i] ^ bytes_to_long(plain_block[i+1]) ^ K*
```

加密：后加密块 = 前加密块 ^ 后明文块 ^ k 

解密：后明文块 = 后加密块 ^ 前加密块 ^ k

```python
c = [748044282, 2053864743, 734492413, 675117672, 1691099828, 1729574447, 1691102180, 657669994, 1741780405, 842228028, 1909206003, 1797919307]

kk = 580598200

result = []
result.append(long_to_bytes(c[0] ^ IV ^ kk))
print(result)

for i in range(len(cry)-1):
    # print(i)
    result.append(long_to_bytes(c[i+1] ^ c[i] ^kk))

for bb in result:
    print(str(bb,encoding='ascii'),end = '')
#moectf{es72b!a5-njad!@-#!@$sad-6bysgwy-1adsw8}
```

`moectf{es72b!a5-njad!@-#!@$sad-6bysgwy-1adsw8}`

## ezhash

做出来后表示心情苦涩，以及再次感觉自己好蠢。

直接看图吧:

![1661777458320.png](https://cdn.liil.cc/2022/08/29/630cb63726a09.png)

`moectf{w0w!U_f1nd_@_c0l1isi0n!U_2_th3_m4ster_of_ARX!}`

## MiniMiniBackPack

查看出题脚本，发现是将flag转换为二进制后，可以理解成：

再将`key[i]` ，与 `flag二进制的后i位` 进行一次幂运算。即，为1则加上key[i]，否则加1.

于是编写一个简单的逆向脚本，即可得到flag的二进制文本。

再将二进制数据转换为文本即可。

```py
from key import key
key = key[::-1]
cip = 2396891354790728703114360139080949406724802115971958909288237002299944566663978116795388053104330363637753770349706301118152757502162

for i in range(len(key)):
    if(cip-key[i] > 0):
        cip = cip - key[i]
        print(1,end='')
        
        
    else:
        print(0,end='')
        cip = cip - 1

e = '0110110101101111011001010110001101110100011001100111101101000011011011110010001101100111010100100110000100110111011101010011000101100001011101000011000101101111010111100111001101011111011110010100111101110101010111110110001100110110011011100101111101100100001100110110001100110000011001000110010101011111001100010111010001111100'

#moectf{Co#gRa7u1at1o^s_yOu_c6n_d3c0de_1t}
```

## baby NET

### Step 1

```python
self.send(b'[+] cipher = ' + hex(bytes_to_long(cipher)).encode())
```

```python
from hashlib import sha256

table = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789'
ending = 'qDXGaCpph'
correctSHA = 'f761979f41432cdc8986c6d0f69888833fecd1ce4dd88eedd7889e6dbf534d6d'
def getSha(ending,trying):
    re = sha256((trying + ending).encode('ascii')).hexdigest()
    # print(re)
    return  re

for i in range(62):
    for j in range(62):
        for k in range(62):
            trying = table[i] + table[j] + table[k]
            trying_encoded = trying
            if(getSha(ending,trying) == correctSHA):
                print(trying)
                break
# XXX -> 1Wv
```

### Step 2

在 Feistel.py 下续写

```python
key1 = b'this_is_the_key~'
key2 = b'to_enlength_key!'

hexed = 0x8b6d863f3e89fd2698ff90e8409502ebf485e17449cdaceb6f5cb2e781524ce4
deced = int(hexed)
c3 = long_to_bytes(deced)
M = decrypt(encrypt(decrypt(c3,key1),key2),key1)
print(M) 
# it_is_just_the_fy0u_can_d0_what?
```

### Step 3

已知 K + IV = it_is_just_the_fy0u_can_d0_what?

由于 AES 的规则，两边长度可能的取值应当是 16,16 (排除 0,32 & 32,0)

在 aes.py 下续写

```python
encdatahex = 0x1fe9c9b13b8af4f59857d9bc5df1bfbc9df34b8a4a33455b244fb0d857f98c3ea8a62b0190e7336dde76365e65e955c4
encdata = long_to_bytes( int(encdatahex))

kiv = b'it_is_just_the_fy0u_can_d0_what?'
K = kiv[:16]
IV = kiv[16:]
control = AES_CBC(K,IV)
data = control.decrypt(encdata)
print(data)
#Congratulations!_You_have_get_the_flag!   
```

`[+] flag is:moectf{sa3d_SD2a@sd_sa44@#d2sa_ad132$aw3_a23d}`

## 不止一次

```
05010c1201035b3909530d7f3750035d304d41063a18021c3e550e3a075e41014211440f
0306141611460f250046593c355f035c2b1903017f5b130f3c5d003b4f52031643451618
050e1143170715230e46593d31110e413e5a0a013b14410c2a42452d0603140a4500175d
080106110d160f240e5c592b3152055d364814017f4c090f2b16063e0d1c0e171707015d
050e1143170715230e46593d31110e413e5a0a013b14410c2a42452d0603140a4500175d
0f1a114306030a3808401c2c744505567f4c12017f57074e3e1616360d150d061a101718
1e0a450c12461a6d125b1738385440462c5c41142d5d4c1d3757173a07520a064e451015
414f110b11461423041f0d3639544d433e5d414c106c31477f5f167f021c410659061604
4d000b06591212200412093e3011457c0b694844364b410f3116003100001813430c0b13
0e0400075846193815120b3a254404413a4a4110375d411b2c53453005520043440c0a1a
0b4f0443070f152a0d57542a27544d432d5c4c173759130b3b160e3a1a52150b56114414
1906080654161a29411a360b04184d5a2c19000a7f5d0f0d2d4f152b0a1d0f4343000715
4d1c0c0d130a1e6014411c7f2443081e2c5100163a5c41053a4f452b0b1315435e164413
144345171c035b220f57542b3d5c08132f5805447777353e76160c2c43130f43520b070f
094f4d2c2036526d0841593e3a11085d3c4b18142b510e007f42003c0b1c081242004409
```

结合hint中的脚本，可知是将 flag 和 一串明文互相异或后再转hex。

所以要再将这串文本unhex后再与已知的某部分异或得到其他部分。由于已知`moectf{_______}`的格式，先用它来做一次异或。

```
hnique ____________________________r
nique t____________________________e
hat can____________________________
encrypt____________________________
hat can____________________________
but req____________________________e
se of a____________________________h
, the o____________________________y
 one-ti____________________________n
cked, b____________________________g
f a sin____________________________i
time pa____________________________h
 single____________________________n
y, the ____________________________r
d (OTP)____________________________t
```

得到了这样一串，看到` one-ti_____` 和 `d (OTP)` 可以看出这里应该是指 `one-time password` 之类的文本。但是经过测试 `one-time pa` 部分是对的。所以排除是`one-time password (OTP)`，而是另一个p开头的单词。

使用  `one-time pa` 得到`moectf{Ma2y___}` 再用后者继续异或得到 

```
hnique that ____________________________r
nique that c____________________________e
hat cannot b____________________________
encryption t____________________________
hat cannot b____________________________
but requires____________________________e
se of a sing____________________________h
, the one-ti____________________________y
 one-time pa____________________________n
cked, but re____________________________g
f a single-u____________________________i
time pad (OT____________________________h
 single-use ____________________________n
y, the one-t____________________________r
d (OTP) is a____________________________t
```

可以看到，经过这样操作，可以不断破出 flag 和原文。于是经过多次如此操作后，即可得到flag.

脚本如下:

```py
from Crypto.Util.strxor import strxor
import binascii

text = '''05010c1201035b3909530d7f3750035d304d41063a18021c3e550e3a075e41014211440f
0306141611460f250046593c355f035c2b1903017f5b130f3c5d003b4f52031643451618
050e1143170715230e46593d31110e413e5a0a013b14410c2a42452d0603140a4500175d
080106110d160f240e5c592b3152055d364814017f4c090f2b16063e0d1c0e171707015d
050e1143170715230e46593d31110e413e5a0a013b14410c2a42452d0603140a4500175d
0f1a114306030a3808401c2c744505567f4c12017f57074e3e1616360d150d061a101718
1e0a450c12461a6d125b1738385440462c5c41142d5d4c1d3757173a07520a064e451015
414f110b11461423041f0d3639544d433e5d414c106c31477f5f167f021c410659061604
4d000b06591212200412093e3011457c0b694844364b410f3116003100001813430c0b13
0e0400075846193815120b3a254404413a4a4110375d411b2c53453005520043440c0a1a
0b4f0443070f152a0d57542a27544d432d5c4c173759130b3b160e3a1a52150b56114414
1906080654161a29411a360b04184d5a2c19000a7f5d0f0d2d4f152b0a1d0f4343000715
4d1c0c0d130a1e6014411c7f2443081e2c5100163a5c41053a4f452b0b1315435e164413
144345171c035b220f57542b3d5c08132f5805447777353e76160c2c43130f43520b070f
094f4d2c2036526d0841593e3a11085d3c4b18142b510e007f42003c0b1c081242004409'''

lines = text.split("\n")

flag = "moectf{Ma2y_T1m3_9ad_8an___________}"
text = ', the one-time pad (OTP) is an encry'

print()
for line in lines:
    mi = binascii.unhexlify(line)
    # print(mi,flag.encode())
    cipher = str(strxor(mi,flag2.encode()),encoding='ascii')
    # print(cipher)
    print("{}____________________________{}".format(cipher[:12],cipher[35:]))
```

`moectf{Ma2y_T1m3_9ad_8an_6e_crac7ed}`

## knapsack

经搜索，得知这是一种[背包加密](https://ctf-wiki.org/crypto/asymmetric/knapsack/knapsack/)的方法。

破解的话，下方甚至已经附带脚本了。

但是需要修改一些内容。最终sage脚本如下:

```python
###sage
pubKey = [........]
nbit = len(pubKey)
# open the encoded message
encoded = 8703069044064992980691645216228835950106263379927508937942531569993354329986256810732900394653277635213670500295460644516991609330265312463889953990340253229385648685715155806817099739383560576384836321881286500659708484627359616398640033155043949415229969716791144119529632481124333945855399331818083663514841663780792990120053753287317104593060986093346705913852023
print("start")
# create a large matrix of 0's (dimensions are public key length +1)
A = Matrix(ZZ,nbit+1,nbit+1)
# fill in the identity matrix
for i in range(nbit):
    A[i,i] = 1
# replace the bottom row with your public key
for i in range(nbit):
    A[i,nbit] = pubKey[i]
# last element is the encoded message
A[nbit,nbit] = -int(encoded)

res = A.LLL()
# 在此处，需要先输出一次res，然后寻找存在的ascii编码部分，这里刚好就首个
M = res.row(0).list()
for _ in M:
    print(chr(_),end='')
#moectf{In_fact_I_D0nt_KnOw_WhAT_2_SaY}
```

# 电子取证与流量分析

## 肥肠简单的内存取证

提示`<0> flag被base64处理过辣`。

考虑到flag的格式都是`moectf{` 于是查了下这个的base64 encode是`bW9lY3Rme` 

接下来直接执行 `strings /home/br/桌面/memdump.mem | grep bW9lY3Rme `得到`bW9lY3Rme3NvbzBvTzBvME8wT18zYXN5IX0K`

解码得到flag:`moectf{soo0oO0o0O0O_3asy!}`
