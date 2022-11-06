~~大家好啊，我是说的道理，今天来点大家想看的啊~~
这里是 Sherkey，一位 XMU 的大一萌新，暑假期间受[ZeroAurora](https://github.com/ZeroAurora)这位佬的邀请来 moectf 玩一玩，~~结果被狠狠按在地上摩擦~~，还是学到了不少东西的

0基础小菜鸡，若wp有错还请轻锤（

~~顺带这位ZeroAurora是个重度迷迭香厨~~

# 作答情况

Web (9/10) ~~差一点ak呜呜~~

Crypto (5/14) 我是废物呜呜

Pwn (4/16) 我还是废物呜呜呜呜

Misc (16/16)  萌新的第一次AK🎉🎉🎉

Classical Cryptography (4/5)

取证 (2/2) ~~这个也算ak~~

Basic (4/4) ~~这个还是可以算ak~~

Reverse (5/16) 呜呜呜呜呜呜呜呜

# Writeup

## Web

### ezhtml

没什么好说的，直接F12看到js里面有flag

~~其实正经解法应该要改成绩的但是管他呢~~

### web安全之入门指北

读完pdf，文档最后就有 flag

### cookiehead

打开网页看到“仅限本地访问”，于是拉到 burpsuite 中添加一行 `X-forwarded-For: 127.0.0.1`，提示变为“请先登录”。看到下面有一行`Cookie: login=0`，把0改为1，提示又变为“You are not from http://127.0.0.1/index.php !”，于是加上`Referer: http://127.0.0.1/index.php`，拿到flag

### God_of_Aim

打开网页，会发现是一个类似练枪法定位的网站，一开始目标分数是10，但是达到10分后会弹窗给出flag的前半部分 ~~你已经学会瞄准啦，现在来试试打魔王曲吧~~，之后目标分数会变成100000 ~~osu玩家直接上手打~~

按下F12，发现aimtrainer.js有点东西，复制到本地格式化一看，显然是有点东西的~~你在说什么废话~~ 将变量_0x78bd的最后一行用hex解码后得到flag的后半部分

（不过更简单的解法应该是直接控制台输入aimTrainer.score=100000

### What are you uploading

打开网页，是经典的上传文件题。随便传一个，发现有格式限制，只能传png/jpg/gif。按照要求随便传一个png上去，提示你只要传一个f1ag.php就会给出flag

于是打开burpsuite，对上传的文件名进行修改，拿到flag

### inclusion

~~一眼include，鉴定为php协议~~

直接`?file=flag.php`果然不行，去网上搜了搜发现可以利用php的filter读出base64编码后的信息，于是`?file=php://filter/read=convert.base64-encode/resource=flag.php`，将信息base64解码后得到flag

> 解题参考 https://blog.csdn.net/vhkjhwbs/article/details/99728785

### sqlmap_boy

~~嗨害嗨，脚本小子来了嗷~~

先F12，看到有注释提示sql语句`<!-- $sql = 'select username,password from users where username="'.$username.'" && password="'.$password.'";'; -->`

根据此语句构造注入语句`'"="'`，这样后面会变成`"'.'"="'.'"`的恒真表达式。·

被定向到secrets.php?id=1  ![草](https://raw.githubusercontents.com/XDSEC/MoeCTF_2022/main/WriteUps/SherkeyXD/images/image-20221006111806382.png)

尝试改了个id=2  ![什么b东西](https://raw.githubusercontents.com/XDSEC/MoeCTF_2022/main/WriteUps/SherkeyXD/images/image-20221006111911358.png)

顺带一提，如果你之前没登进去直接访问secrets.php，会变成这样

![来劲了是吧](https://raw.githubusercontents.com/XDSEC/MoeCTF_2022/main/WriteUps/SherkeyXD/images/image-20221006112033386.png)~~烦死了（恼~~

想到题目的sqlmap，现学了sqlmap的使用方法，~~然后找到一篇基本上是把答案糊你脸上的博客~~。

这里划重点，**一定要带上cookie！**~~有个大冤种浪费了好久我不说是谁~~

先试了下 `sqlmap -u http://82.156.5.200:1045/secrets.php\?id\=1 --cookie="PHPSESSID=d001d48957ce798b041801bfd28fd16e" --dbs`，发现有这么几个数据库 

![image-20221006113116427](https://raw.githubusercontents.com/XDSEC/MoeCTF_2022/main/WriteUps/SherkeyXD/images/image-20221006113116427.png)

然后是`sqlmap -u http://82.156.5.200:1045/secrets.php\?id\=1 --cookie="PHPSESSID=d001d48957ce798b041801bfd28fd16e" -D moectf --tables`，发现有flag

![image-20221006113250098](https://raw.githubusercontents.com/XDSEC/MoeCTF_2022/main/WriteUps/SherkeyXD/images/image-20221006113250098.png)

列出flag中的所有项 `sqlmap -u http://82.156.5.200:1045/secrets.php\?id\=1 --cookie="PHPSESSID=d001d48957ce798b041801bfd28fd16e" -D moectf -T flag --columns`

![image-20221006113558643](https://raw.githubusercontents.com/XDSEC/MoeCTF_2022/main/WriteUps/SherkeyXD/images/image-20221006113558643.png)

将flAg列出，得到flag` sqlmap -u http://82.156.5.200:1045/secrets.php\?id\=1 --cookie="PHPSESSID=d001d48957ce798b041801bfd28fd16e" -D moectf -T flag -C flAg --dump`

> 解题参考 https://blog.csdn.net/weixin_43882862/article/details/119673249

### ezphp

阅读代码，发现有几个要注意的点

+ 要传入flag，get和post都行，否则会执行 `exit($giveme)`

+ flag的内容不能是flag，否则会执行 `exit($getout)`

+ 最后程序会输出flag的值

这里就出现了矛盾的点：当你传入flag值的时候，原来的flag值会被覆盖掉

怎么解决呢？这就涉及到php中双美元变量和单美元变量的区别了。举例来说，如果已经有单美元变量`$ikun=f1ag`，那么双美元变量 `$$ikun=moectf`将会先把里面的`$ikun`替换成`f1ag`，因此，双美元变量的赋值语句也就变成了`$f1ag=moectf`

知道了这一点，再结合 `foreach ($_GET as $key => $value)` 这一栏，我们就可以实现变量值的交换

注意，这里不能用post传入变量，因为post传入的参数并不能实现变量交换

地址栏后加上`?moectf=flag&flag=moectf`，flag就出来了

**顺序很重要！必须要先用另一个变量把flag的值储存起来，否则flag一样会被覆盖**

### 支付系统

~~其实这题就是个脑筋急转弯~~

观察源码，发现程序会将post进callback的data值和最终的data值进行哈希校验，而显然app.secret_key是未知的，不能从这里下手。细看了一阵子发现do_callback里面data的格式有点问题，是直接拼接，又看到有个desc，猜测是通过修改amount, status和desc来使拼接后得到相同的字符串

打开burpsuite，访问/pay，并且post进amount和desc。注意此时stastus会被设置为PENDING，也就是1，则此时data后半部分为`amonut+'1'+desc`

此时，页面被重定向至/transaction?id=1，这里的id就是一会要传进去的id。页面上有你的uuid和一个二维码，扫一下二维码，发现得到的值像是hash加密的值 。又看到/callback部分要求传入hash值，猜测这个就是目前data的hash值

注意，程序执行过程中有一次会将status设为FAILED，也就是2。因此我们要让现在`amonut+'2'+desc`等于之前的值才行

那么，显然amout的结尾要是2，desc则没有要求，最终传入/callback时删去amount结尾的2，然后在desc前面加个1就行

比如：

```
amount="12" status="1" desc="114514"   amount+status+desc="121114514" //pay
amount="1" status="2" desc="1114514"   amount+status+desc="121114514" //callback
```

访问/callback，并将现有的id, user, amount, status, desc, hash全部丢进去，看到返回ok，说明我们做出来了，访问/flag得到flag

## Crypto

### 密码学之入门指北

看pdf拿flag

### Signin

 初看这题以为直接上就行，看了看发现不对，分析了一下发现e是phi的因数，自然也就无法正常求逆元（细看还能发现是q-1的问题）

但是由于p, q都已知，我们就可以更换q为2，得到flag（其实q=3也行）

### Ezfactor

先`nc polarnova.top 10001` ~~这不是pwn的活吗~~

发现要找到两个素数，其和为指定的数。故直接上python

```python
from Crypto.Util.number import isPrime #直接用现成函数算不算逃课（

sum = int(input())
for b in range(sum):
    a = sum - b
    if isPrime(a) and isPrime(b):
        print(f"A={a}\nB={b}")
        break
```

会得到m和n，但一组显然是无法解的，怎么办呢？观察代码，发现q是随机的，而p是确定值，e为0x10001（65537）

再来一次，会有新的m和n，于是求两个n的公因数，然后就是标准rsa解法

```python
from Crypto.Util.number import *

m1 = 114514
N1 = 1919810
N2 = 2333333
e = 0x10001

p = GCD(N1,N2)
q1 = N1 // p
phi1 = (p-1)*(q1-1)
d1 = inverse(e, phi1)
c1 = pow(m1, d1, N1)
print(long_to_bytes(c1))
```

### 一次就好

拿到附件先看一眼，发现flag用#填充至与c相同长度后与c异或得到key，key转为long之后得到m，m经rsa加密得到gift

观察发现这个n有很大漏洞，是两个连续素数的乘积，很自然想到对n开根号，寻找下一个素数得到p，n除以q得到q，rsa部分就被破解了。而异或部分也很简单，再和c异或一次就好了

```python
from gmpy2 import invert, iroot, next_prime
from Crypto.Util.strxor import strxor
from Crypto.Util.number import long_to_bytes

gift = 127749242340004016446001520961422059381052911692861305057396462507126566256652316418648339729479729456613704261614569202080544183416817827900318057127539938899577580150210279291202882125162360563285794285643498788533366420857232908632854569967831654923280152015070999912426044356353393293132914925252494215314
n = 164395171965189899201846744244839588935095288852148507114700855000512464673975991783671493756953831066569435489213778701866548078207835105414442567008315975881952023037557292470005621852113709605286462434049311321175270134326956812936961821511753256992797013020030263567313257339785161436188882721736453384403
e = 0x10001
c = b'Just once,I will accompany you to see the world'

temp = iroot(n,2)[0]   # 不用gmpy2的话会精度损失
p = next_prime(temp)
q = n // p
phi = (p-1)*(q-1)
d = invert(e, phi)
m = pow(gift, d, n)
key = long_to_bytes(m)
flag = strxor(key, c)
print(flag)
```

### 0rsa0

观察代码，发现flag被拆成了两部分，分别破译。第一部分e=3，一眼小公钥指数攻击，直接现成脚本

```python
import gmpy2
import codecs

def sss(n):
    s = hex(n)[2:]
    if len(s) % 2 != 0:
            s = "0" + s
    return str(codecs.decode(s, 'hex'))

n=133024413746207623787624696996450696028790885302997888417950218110624599333002677651319135333439059708696691802077223829846594660086912881559705074934655646133379015018208216486164888406398123943796359972475427652972055533125099746441089220943904185289464863994194089394637271086436301059396682856176212902707
c=1402983421957507617092580232325850324755110618998641078304840725502785669308938910491971922889485661674385555242824
res = 0
for i in range(200000000):
    if gmpy2.iroot(c+n*i,3)[1]==1:
        res=gmpy2.iroot(c+n*i,3)[0]
        print(sss(res))
        break
```

下半部分dp泄露，同样现成脚本

```python
import gmpy2

n=159054389158529397912052248500898471690131016887756654738868415880711791524038820158051782236121110394481656324333254185994103242391825337525378467922406901521793714621471618374673206963439266173586955520902823718942484039624752828390110673871132116507696336326760564857012559508160068814801483975094383392729
e=65537
c=37819867277367678387219893740454448327093874982803387661058084123080177731002392119369718466140559855145584144511271801362374042596420131167791821955469392938900319510220897100118141494412797730438963434604351102878410868789119825127662728307578251855605147607595591813395984880381435422467527232180612935306
dp=947639117873589776036311153850942192190143164329999603361788468962756751774397111913170053010412835033030478855001898886178148944512883446156861610917865

for x in range(1, e):
    if(e*dp%x==1):
        p=(e*dp-1)//x+1
        if(n%p!=0):
            continue
        q=n//p
        phin=(p-1)*(q-1)
        d=gmpy2.invert(e, phin)
        m=gmpy2.powmod(c, d, n)
        if(len(hex(m)[2:])%2==1):
            continue
        print(bytes.fromhex(hex(m)[2:]))
```

拼接得flag

## Pwn

### 二进制漏洞审计之入门指北

看pdf

### shell

直接cat flag

### *filedes

这个是比赛结束后才做出来的~~没想到这么简单~~

打开IDA看到read函数，上网查了查发现read的第一个参数是文件描述符，其中0是stdin而1代表stdout，write一样。于是第一个输入填1，第二个输入填0，得到flag

### int_overflow

简单题，直接上手计算器算出对应值使两者相加为0即可

### buffer_overflow

缓冲区溢出，经典的gets漏洞，越界修改v5为"Limiter and Wings are beautiful girls!"即可

注意这里要标注字符串的结束，直接回车是不行的，可以Ctrl+D结束输入流或在字符串末尾加上"\x00"

## Misc

### Hide-and-seek

下载pdf文件，仔细看一眼发现图片边边有几个字露出来了，复制得到flag

~~当然你也可以直接把图片删了~~

### Misc杂项之入门指北

文章末尾有一串莫尔斯电码，解密得flag

### Rabbit

010Editor打开png看到文件末尾有一串`U2FsdGVkX1+EPlLmNvaJK4Pe06nW0eLquWsUpdyv3fjXM2PcDBDKlXeKupnnWlFHewFEGmqpGyC1VdX8`，由于是U2FsdGVkX1开头，加上题目名字叫Rabbit，推测是Rabbit加密，解密 得到flag

> 这里注意有的解密网站会报错，我用的是[Rabbit加解密(ES JSON在线工具)](http://www.esjson.com/rabbitEncrypt.html)

### 小纸条

猜猜这是什么？猪笔密码！但是空白的那一侧加上了弯弯的东西哦

对着表一个个查，按照格式写出flag

### 寻找黑客的家

社工题不一定会难，但一定很好玩

根据图片内容，在百度地图上搜索“汉明宫”，找到一家电话和图片中显示的号码后几位一致的，按照描述的格式写出flag

### Locked Bass

打开压缩包发现头错误，猜测伪加密，Bandizip修复得正常压缩包，打开有一串base64，解码得flag

### 调查问卷

做问卷得flag啦

### zip套娃

第一层，直接暴力爆破密码，为1235

第二层，根据提示使用掩码1234567???爆破，得到密码1234567qwq

第三层，伪加密，010改一下加密位置打开

### usb

经典usb流量题，根据题目描述的<CAP>知道是键盘流量，于是用tshark将数据写入usbdata.txt

现成脚本

```python
presses = []
normalKeys = {"04":"a", "05":"b", "06":"c", "07":"d", "08":"e", "09":"f", "0a":"g", "0b":"h", "0c":"i", "0d":"j", "0e":"k", "0f":"l", "10":"m", "11":"n", "12":"o", "13":"p", "14":"q", "15":"r", "16":"s", "17":"t", "18":"u", "19":"v", "1a":"w", "1b":"x", "1c":"y", "1d":"z","1e":"1", "1f":"2", "20":"3", "21":"4", "22":"5", "23":"6","24":"7","25":"8","26":"9","27":"0","28":"<RET>","29":"<ESC>","2a":"\b", "2b":"\t","2c":" ","2d":"-","2e":"=","2f":"[","30":"]","31":"\\","32":"<NON>","33":";","34":"'","35":"<GA>","36":",","37":".","38":"/","39":"<CAP>","3a":"<F1>","3b":"<F2>", "3c":"<F3>","3d":"<F4>","3e":"<F5>","3f":"<F6>","40":"<F7>","41":"<F8>","42":"<F9>","43":"<F10>","44":"<F11>","45":"<F12>"}
shiftKeys = {"04":"A", "05":"B", "06":"C", "07":"D", "08":"E", "09":"F", "0a":"G", "0b":"H", "0c":"I", "0d":"J", "0e":"K", "0f":"L", "10":"M", "11":"N", "12":"O", "13":"P", "14":"Q", "15":"R", "16":"S", "17":"T", "18":"U", "19":"V", "1a":"W", "1b":"X", "1c":"Y", "1d":"Z","1e":"!", "1f":"@", "20":"#", "21":"$", "22":"%", "23":"^","24":"&","25":"*","26":"(","27":")","28":"<RET>","29":"<ESC>","2a":"\b", "2b":"\t","2c":" ","2d":"_","2e":"+","2f":"{","30":"}","31":"|","32":"<NON>","33":"\"","34":":","35":"<GA>","36":"<","37":">","38":"?","39":"<CAP>","3a":"<F1>","3b":"<F2>", "3c":"<F3>","3d":"<F4>","3e":"<F5>","3f":"<F6>","40":"<F7>","41":"<F8>","42":"<F9>","43":"<F10>","44":"<F11>","45":"<F12>"}
with open("usbdata.txt", "r") as f:
    for line in f:
        presses.append(line[0:-1])
# handle
result = ""
for press in presses:
    Bytes = press.split(":")
    try:
        if Bytes[0] == "00":
            if Bytes[2] != "00":
                result += normalKeys[Bytes[2]]
        elif Bytes[0] == "02": # shift key is pressed.
            if Bytes[2] != "00":
                result += shiftKeys[Bytes[2]]
        else:
            print ("[-] Unknow Key: %s" % (Bytes[0]))
    except KeyError:
        pass
print ("[+] Found: %s" % (result))
```

记得<CAP>按大写锁定键就行

### Nyanyanya!

stegsolve打开，查看lsb隐写得flag

### What do you recognize me by?

010打开，发现文件头跟png的很像，改一下打开是一张二维码，扫描得flag

### A band

套娃，上cyberchef。先二进制转字符串，发现是十六进制，再转字符串，得到一堆颜文字，AAEncode解密，得到一串base，再丢进cyberchef，发现是base32套base58套base64，得到flag

### cccrrc

看名字，crc爆破，直接上crc32爆破，得到的拼起来得flag

### 想听点啥？

mscz文件是乐谱文件，用musescore打开，读出密码为`MOECTFI1iKE`，打开压缩包看到py文件，是简单的异或加密，写脚本

```python
flag = 'm'

with open('flag.txt', 'r') as f:
    a = f.read()

for i in range(0, len(a)):
    flag += chr(ord(a[i])^ord(flag[i]))

print(flag)
```

### H■m■i■g

汉明码还是很简单的，这里推荐看3b1b的视频，基本就是把答案糊你脸上了

> [汉明码Pa■t1，如何克服噪■](https://www.bilibili.com/video/BV1WK411N7kz/)
>
> [汉明码part2，优雅的全貌](https://www.bilibili.com/video/BV1pV411y7E8/)

将noise_msg直接扔到bob.py里面，并修改hamming_correct函数即可

```python
from functools import reduce
import operator as op

def hamming_correct(bitblock):
    a = reduce(op.xor, [i for i ,bit in enumerate(bitblock) if bit])
    return a
```

### Bell202

工具题，搜了搜发现有调制解调器的解码工具minimodem，下载运行`minimodem -r -f moe_modem.wav 1200`

## Classical Cryptography

### ABCDEFG

根据题目提示，A对应26，B对应25，以此类推，直接上pyton

```python
a = [18,24,26,13,8,18,13,20,26,15,11,19,26,25,22,7,8,12,13,20]
di="ABCDEFGHIJKLMNOPQRSTUVWXYZ"
flag=""
for i in a:
    flag += di[26-i]
print(flag)
```

### 小小凯撒

可以用quipquip猜测偏移量，也可以直接脚本爆破

```python
text = "kqEftuEUEftqOADDqoFRxmsOAzsDmFGxmFuAzE"
for a in range(1, 27):
    print(f"{a}:",end="")
    for i in range(len(text)):        
        if ord('a')<=ord(text[i])<=ord('z'):
            print(chr((ord(text[i])+a-ord('a'))%26+ord('a')),end="")
        elif ord('A')<=ord(text[i])<=ord('Z'):
            print(chr((ord(text[i])+a-ord('A'))%26+ord('A')),end="")
        else:
            print(text[i],end="")
    print("")
```

找到有意义的flag

### 凯撒变异了

~~臭死了~~

看题目说114514，猜测是否为每一位偏移量不同的凯撒加密，写脚本

```python
flag = 'ZpyLfxGmelDeftewJwFbwDGssZszbliileadaa'
alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
for i in range(0,len(flag)):
    a = i%6
    if a==0:
        print(alpha[alpha.find(flag[i])-1], end="")
    elif a==1:
        print(alpha[alpha.find(flag[i])-1], end="")
    elif a==2:
        print(alpha[alpha.find(flag[i])-4], end="")
    elif a==3:
        print(alpha[alpha.find(flag[i])-5], end="")    
    elif a==4:
        print(alpha[alpha.find(flag[i])-1], end="")
    elif a==5:
        print(alpha[alpha.find(flag[i])-4], end="")
```

方法蠢了点，但是有用

### Vigenère

正经来说，维吉尼亚密码是要分析词频然后推测可能密钥的，但是有个在线网站可以做到这一点

直接丢网站，解出密钥tfdvsjuz，找到flag

> [Vigenere Solver - www.guballa.de](https://www.guballa.de/vigenere-solver)

## 取证

### 肥肠简单的内存取证.mem

下载附件并解压，发现是mem文件，猜测使用volatility

使用`volatility -f memdump.mem imageinfo`查看镜像信息，看到是`Win7SP1x64`

使用`volatility -f memdump.mem --profile=Win7SP1x64 pslist` 查看进程，发现有个notepad.exe，提取一下试试

`volatility -f memdump.mem --profile=Win7SP1x64 memdump -p notepad的pid -D 你想放的目录 `，得到dmp文件

使用strings导出，`strings 2616.dmp > 1.txt`

根据hint，flag被base64加密，于是写python脚本破解，得到flag

```python
import base64

with open("1.txt", "r") as f:
    content=f.read().split("\n") # 不用readlines的原因是那样读出来会有\n
for i in content:
    try:
        text = base64.b64decode(i)
        if "moectf" in text:
        	print(text)    
    except:
        pass   # 跳过不能base64解码的行
```

当然也有逃课做法，由于flag以moectf开头，故加密后的base64串会以bW9lY3Rm开头，直接`strings memdump.mem | grep bW9lY3Rm`也可以做出来

### 好像可能会有点难的取证

**~~FTK我要啥了你的🐴~~**

~~下镜像就下了好久~~ 对raw文件同样执行上面操作，pslist发现没有notepad，故从cmd入手

`volatility -f WIN-S60U4TV3ES2-20221008-092303 --profile=Win7SP1x64 cmdscan`，发现利用openssl对文件进行了加密

使用镜像挂载工具挂载E01文件，会发现有一个盘被Bitlocker锁定。先不管，复制挂载的系统盘下的recover_key_encryped，使用openssl解密

`openssl enc -aes-128-ecb -d -a -in .\recover_key_encryped -out de.txt -nosalt  `，密码为`'zhebushikey'`~~不会有人忘了输单引号吧~~

> 理论上来说可以直接加上 `-pass pass:'zhebushikey'`，但是我这里总是莫名其妙报bad encrypt

解密后得到Bitlock密钥，揭开后看到根目录有flag.txt

> 镜像挂载工具推荐Arsenal Image Mounter，FTK老是有莫名其妙的问题

这题同样可以逃课，DiskGenius可以直接恢复出未加密的Bitlock密钥，直接解锁即可

## Basic

~~不会有人这个还要看wp吧~~

## Reverse

### 逆向工程之入门指北

看pdf拿flag

### hex

010查看文件尾部有flag

### checkin

打开IDA，F5直接看到flag

### begin

丢进IDA，F5发现是简单异或加密，打开strings窗口，将两段字符串拼起来得到`tv|zmbA)kF(jFj)Fpwm*k*jmpw~88888d`，然后每一位和0x19做异或，得到flag

### base

打开IDA，F5发现是个base64解密。直接解肯定是不对的，故打开strings窗口，发现是自定义字符表，丢cyberchef解出

# 跋

迈出的每一步，以落脚开始，以抬脚结束。将腿足往上拖拉出来，谓之跋。这段话当然不是我自己想出来的，但我想借用其将内心的感慨稍作抒发

两个月的鏖战，最终取得了一个还算让自己满意的成绩。我想，若是没有这次机会，我的整个暑假都会在浑浑噩噩中度过吧。初见ctf，一路跌跌撞撞，却也收获良多。LGLJ，lq，DX，polarnova，Mikato，这些名字我都会记在心中。~~当然也不能忘了经常被迫害的dbt和~~ 以及，感谢我的朋友们，在我想要放弃时为我加油鼓劲。无论是老朋友[ZeroAurora(零光)](https://github.com/ZeroAurora)还是新朋友[ExceptionB(鲤塘可可)](https://github.com/ExceptionB)和[Neptsun(Laffey)](https://github.com/Neptsun)，抑或是moectf群里的大家。有时我也会羡慕XDSEC的氛围，但身在XMU，我只能看着我们冷冷清清的网安协会纳新群长叹

阶段性目标完成的同时，人们总会陷入或长或短的迷茫。比赛结束的那一刻，我走到阳台，试问自己：前路何往？也许接下来我该学一学re与pwn的知识，又或许我应该多学点web知识。但无论如何，信息安全这一专业已纳入了我的未来规划之中。无论未来会变得怎样，回想起这些日子，我希望我不会有遗憾

也许写的有些伤感或是肉麻，但写下这些文字不是为了卖弄，而是为了提醒自己：

前路漫长，但我身边有光



（不过这一点也不像我的风格（小声
