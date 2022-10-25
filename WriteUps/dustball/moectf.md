# moectf

## reverse

### Fake_code

```c
  puts("Give me your flag:");
  printf("%s", input);//输入,但是printf?
  index = -1i64;
  do
    ++index;
  while ( input[index] );
  if ( index == 51 )//输入51个字符
  {
    for ( i = 0; i < 51; ++i )
    {
      v5 = (127 * v5 + 102) % 255;//这v5是个寂寞吧
      input[i] ^= box[critical];//每个输入的字符都和box[critical]做异或运算
    }
    if ( (unsigned int)strcmp(&ans, input) )//比较input和ans是否相同
      puts("\nTTTTTTTTTTQQQQQQQQQQQQQLLLLLLLLL!!!!");
    else
      puts("\nQwQ, please try again.");
    result = 0;
  }
  else
  {
    puts("\nQwQ, please try again.");
    result = 0;
  }
```

ans是已知的,只需要分析input是怎么得到的,input[51]首先被输入,然后和box[critical]做异或运算,这里critical看似是一个常数,实际上异常处理机制是会修改他的值的,box也是已知的,

那么问题转化为,critical是怎么变化的了

在critical上观察交叉引用

![image-20220929204958145](https://raw.githubusercontent.com/DeutschBall/DeutschBall/main/image-20220929204958145.png)

loc_1400011E9引用过他,过去看看

是在except块中,except用于处理异常,确实会对critical有写入动作,在分析except干了什么之前,首先看看是什么触发的异常

```asm
loc_1400011E9:
;   __except(loc_1400020D0) // owned by 1400011B8
imul    eax, cs:critical, 61h ; 'a'
add     eax, 65h ; 'e'
cdq
mov     ecx, 0E9h
idiv    ecx
mov     eax, edx
mov     cs:critical, eax
mov     eax, cs:critical
xor     eax, 29h
mov     cs:critical, eax
...
```



在try块中,try块用于捕获异常

```asm
loc_1400011B8:
;   __try { // __except at loc_1400011E9
imul    eax, [rsp+0D8h+var_B4], 7Fh
add     eax, 66h ; 'f'
cdq
mov     ecx, 0FFh
idiv    ecx
mov     eax, edx
mov     [rsp+0D8h+var_B4], eax
mov     eax, [rsp+0D8h+var_B4]
sar     eax, 7
mov     [rsp+0D8h+var_B0], eax
mov     eax, 1
cdq
idiv    [rsp+0D8h+var_B0]
mov     [rsp+0D8h+var_B0], eax
jmp     short loc_140001212
;   } // starts at 1400011B8
```

var_B4在main一开始被初始化为0

每次try块都会干这么一个事情

```
var_B4=(var_B4*0x7F+0x66)%0xFF
var_B0=var_B4>>7
```

然后var_B0作为除数,如果var_B0=0,则触发除0异常,那么var_B0啥时候为0呢?



写一个程序打个表

```c
#include <iostream>
#include <iomanip>
using namespace std;
int main(){
    int a=0;//var_B4
    int b;//var_B0
    for(int i=0;i<=10;++i){
        a=(a*0x7F+0x66)%0xFF;
        b=a>>7;
        cout<<setw(5)<<a<<setw(5)<<b<<endl;
    }
    return 0;
}
```

```sh
PS C:\Users\86135\Desktop\moectf\fake_code> g++ main.cpp -O0 -o main
PS C:\Users\86135\Desktop\moectf\fake_code> ./main
  102    0
   51    0
  204    1
    0    0
  102    0
   51    0
  204    1
    0    0
  102    0
   51    0
  204    1
```

这确实是有规律的

| 周期相位 | 0    | 1    | 2    | 3    |
| -------- | ---- | ---- | ---- | ---- |
| var_B4   | 102  | 51   | 204  | 0    |
| var_B0   | 0    | 0    | 1    | 0    |

对于输入的51个字节来说,每4个字节一组,每组的第三个字节时var_B0会等于1,其他情况都是0

下面的问题是,当除零异常发生时,critical会经过怎样的变化呢?

```asm
loc_1400011E9:
;   __except(loc_1400020D0) // owned by 1400011B8
imul    eax, cs:critical, 61h ; 'a'
add     eax, 65h ; 'e'
cdq
mov     ecx, 0E9h
idiv    ecx
mov     eax, edx
mov     cs:critical, eax
mov     eax, cs:critical
xor     eax, 29h
mov     cs:critical, eax
```

$$
critical=[(critical\times 61h+65h)\mod E9h]\oplus 29h
$$

critical的初始值是0x19h

下面打表critical的值

```c
#include <iostream>
#include <iomanip>
using namespace std;
int main(){
    int a=0;//var_B4
    int b;//var_B0
    int c=0x19;//critical
    for(int i=0;i<51;++i){
        a=(a*0x7F+0x66)%0xFF;
        b=a>>7;
        if(b==0){
            c=((c*0x61+0x65)%0xe9)^0x29;
        }
        cout<<c<<",";
    }
    return 0;
}
```

```
237,62,62,16,63,179,179,247,20,152,152,143,200,139,139,111,191,244,244,42,255,163,163,109,148,34,34,160,35,40,40,61,232,45,45,14,20,152,152,143,200,139,139,111,191,244,244,42,255,163,163
```

然后box也是已知的

```c
unsigned char box[256] = {
    0xAC, 0x04, 0x58, 0xB0, 0x45, 0x96, 0x9F, 0x2E, 0x41, 0x15, 0x18, 0x29, 0xB1, 0x33, 0xAA, 0x12, 
    0x0D, 0x89, 0xE6, 0xFA, 0xF3, 0xC4, 0xBD, 0xE7, 0x70, 0x8A, 0x94, 0xC1, 0x85, 0x9D, 0xA3, 0xF2, 
    0x3F, 0x82, 0x8E, 0xD7, 0x03, 0x93, 0x3D, 0x13, 0x05, 0x6B, 0x41, 0x03, 0x96, 0x76, 0xE3, 0xB1, 
    0x8A, 0x4A, 0x22, 0x55, 0xC4, 0x19, 0xF5, 0x55, 0xA6, 0x1F, 0x0E, 0x61, 0x27, 0xCB, 0x1F, 0x9E, 
    0x5A, 0x7A, 0xE3, 0x15, 0x40, 0x94, 0x47, 0xDE, 0x00, 0x01, 0x91, 0x66, 0xB7, 0xCD, 0x22, 0x64, 
    0xF5, 0xA5, 0x9C, 0x68, 0xA5, 0x52, 0x86, 0xBD, 0xB0, 0xDD, 0x76, 0x28, 0xAB, 0x16, 0x95, 0xC5, 
    0x26, 0x2C, 0xF6, 0x39, 0xBE, 0x00, 0xA5, 0xAD, 0xE3, 0x93, 0x9E, 0xE3, 0x05, 0xA0, 0xB0, 0x1D, 
    0xB0, 0x16, 0x0B, 0x5B, 0x33, 0x95, 0xA4, 0x09, 0x16, 0x87, 0x56, 0x1F, 0x83, 0x4E, 0x4A, 0x3C, 
    0x55, 0x36, 0x6F, 0xBB, 0x4C, 0x4B, 0x9D, 0xB1, 0xAE, 0xE5, 0x8E, 0xC8, 0xFB, 0x0E, 0x29, 0x8A, 
    0xBB, 0xFC, 0x20, 0x62, 0x04, 0x2D, 0x80, 0x61, 0xD6, 0xC1, 0xCC, 0x3B, 0x89, 0xC5, 0x8B, 0xD5, 
    0x26, 0x58, 0xD6, 0xB6, 0xA0, 0x50, 0x75, 0xAB, 0x17, 0x83, 0x7F, 0x37, 0x2B, 0xA0, 0x1D, 0x2C, 
    0xCF, 0xC7, 0xE0, 0xE5, 0x49, 0xC9, 0xFA, 0x6B, 0xC0, 0x98, 0x66, 0x99, 0x92, 0x00, 0x02, 0xD4, 
    0x75, 0x46, 0x22, 0x05, 0x35, 0xD1, 0x4B, 0xC5, 0xAD, 0xE0, 0x8E, 0x45, 0x3B, 0x50, 0x15, 0xB5, 
    0x2E, 0x85, 0x30, 0x89, 0x54, 0x12, 0xDE, 0xF1, 0x5A, 0xF0, 0x2B, 0xA7, 0x1B, 0x4A, 0x26, 0x5D, 
    0x98, 0xD4, 0xA1, 0xBE, 0xD1, 0x4D, 0x7E, 0x38, 0xDE, 0x0B, 0x0A, 0x54, 0xB8, 0x73, 0x6D, 0xAD, 
    0x8C, 0x1E, 0xD9, 0x31, 0x5F, 0x56, 0x7E, 0xBD, 0x48, 0x32, 0x98, 0x2E, 0x3E, 0xEB, 0xA2, 0x1D
};
```



下面就可以解密了



```c
#include <iostream>
#include <iomanip>
using namespace std;
int idx[51]={237,62,62,16,63,179,179,247,20,152,152,143,200,139,139,111,191,244,244,42,255,163,163,109,148,34,34,160,35,40,40,61,232,45,45,14,20,152,152,143,200,139,139,111,191,244,244,42,255,163,163};
unsigned char box[256] = {
    0xAC, 0x04, 0x58, 0xB0, 0x45, 0x96, 0x9F, 0x2E, 0x41, 0x15, 0x18, 0x29, 0xB1, 0x33, 0xAA, 0x12, 
    0x0D, 0x89, 0xE6, 0xFA, 0xF3, 0xC4, 0xBD, 0xE7, 0x70, 0x8A, 0x94, 0xC1, 0x85, 0x9D, 0xA3, 0xF2, 
    0x3F, 0x82, 0x8E, 0xD7, 0x03, 0x93, 0x3D, 0x13, 0x05, 0x6B, 0x41, 0x03, 0x96, 0x76, 0xE3, 0xB1, 
    0x8A, 0x4A, 0x22, 0x55, 0xC4, 0x19, 0xF5, 0x55, 0xA6, 0x1F, 0x0E, 0x61, 0x27, 0xCB, 0x1F, 0x9E, 
    0x5A, 0x7A, 0xE3, 0x15, 0x40, 0x94, 0x47, 0xDE, 0x00, 0x01, 0x91, 0x66, 0xB7, 0xCD, 0x22, 0x64, 
    0xF5, 0xA5, 0x9C, 0x68, 0xA5, 0x52, 0x86, 0xBD, 0xB0, 0xDD, 0x76, 0x28, 0xAB, 0x16, 0x95, 0xC5, 
    0x26, 0x2C, 0xF6, 0x39, 0xBE, 0x00, 0xA5, 0xAD, 0xE3, 0x93, 0x9E, 0xE3, 0x05, 0xA0, 0xB0, 0x1D, 
    0xB0, 0x16, 0x0B, 0x5B, 0x33, 0x95, 0xA4, 0x09, 0x16, 0x87, 0x56, 0x1F, 0x83, 0x4E, 0x4A, 0x3C, 
    0x55, 0x36, 0x6F, 0xBB, 0x4C, 0x4B, 0x9D, 0xB1, 0xAE, 0xE5, 0x8E, 0xC8, 0xFB, 0x0E, 0x29, 0x8A, 
    0xBB, 0xFC, 0x20, 0x62, 0x04, 0x2D, 0x80, 0x61, 0xD6, 0xC1, 0xCC, 0x3B, 0x89, 0xC5, 0x8B, 0xD5, 
    0x26, 0x58, 0xD6, 0xB6, 0xA0, 0x50, 0x75, 0xAB, 0x17, 0x83, 0x7F, 0x37, 0x2B, 0xA0, 0x1D, 0x2C, 
    0xCF, 0xC7, 0xE0, 0xE5, 0x49, 0xC9, 0xFA, 0x6B, 0xC0, 0x98, 0x66, 0x99, 0x92, 0x00, 0x02, 0xD4, 
    0x75, 0x46, 0x22, 0x05, 0x35, 0xD1, 0x4B, 0xC5, 0xAD, 0xE0, 0x8E, 0x45, 0x3B, 0x50, 0x15, 0xB5, 
    0x2E, 0x85, 0x30, 0x89, 0x54, 0x12, 0xDE, 0xF1, 0x5A, 0xF0, 0x2B, 0xA7, 0x1B, 0x4A, 0x26, 0x5D, 
    0x98, 0xD4, 0xA1, 0xBE, 0xD1, 0x4D, 0x7E, 0x38, 0xDE, 0x0B, 0x0A, 0x54, 0xB8, 0x73, 0x6D, 0xAD, 
    0x8C, 0x1E, 0xD9, 0x31, 0x5F, 0x56, 0x7E, 0xBD, 0x48, 0x32, 0x98, 0x2E, 0x3E, 0xEB, 0xA2, 0x1D
};
unsigned char ans[51] = {
    0x1E, 0x70, 0x7A, 0x6E, 0xEA, 0x83, 0x9E, 0xEF, 0x96, 0xE2, 0xB2, 0xD5, 0x99, 0xBB, 0xBB, 0x78, 
    0xB9, 0x3D, 0x6E, 0x38, 0x42, 0xC2, 0x86, 0xFF, 0x63, 0xBD, 0xFA, 0x79, 0xA3, 0x6D, 0x60, 0x94, 
    0xB3, 0x42, 0x11, 0xC3, 0x90, 0x89, 0xBD, 0xEF, 0xD4, 0x97, 0xF8, 0x7B, 0x8B, 0x0B, 0x2D, 0x75, 
    0x7E, 0xDD, 0xCB
};
int main(){
    for(int i=0;i<51;++i){
        cout<<(char)(ans[i]^box[idx[i]]);
    }
    return 0;
}
```



```
moectf{Re4d_4ssemb1y8t0_g3t_the_m4gic_key_0f_Tr4ck}
```



### Art

#### UPX壳

本来直接ida64上看到UPX字样后,想手工脱壳,但实际上高估自己的脱壳能力了

看看有没有先成的脱壳的家伙

![image-20220929221502391](https://raw.githubusercontent.com/DeutschBall/DeutschBall/main/image-20220929221502391.png)



upx3.96可以脱壳,真是解铃还须系铃人.

脱了之后就肃静了

#### 哈希算法

```c
  scanf("%s", input);
  for ( i = 0; i <= 27; ++i )
    input_copy[i] = input[i];
  for ( i = 1; i <= 27; ++i )
    input[i - 1] ^= (input[i - 1] % 17 + input[i]) ^ 0x19;
  if ( !strcmp(input, &Str2) && (unsigned int)sub_401550(input_copy) )
    puts("\nGood job!!! You know UPX and hash!!!");
```

这里有两个校验

对于input数组来说

```c
input[i - 1] ^= (input[i - 1] % 17 + input[i]) ^ 0x19;
```

计算完成之后要和Str2进行字符串比较,Str2是给定的,只需要求解哈希之前的input

有个规律是,input[27]是没有经过哈希的,通过input[27]可以逆推input[26]

```
哈希之后的input[26]^=(哈希之前的input[26]%17+input[27])^0x19
```

哈希之后的input[26]就是Str2[26],是个常数,不妨设方程为
$$
a=((x\%17+b)\oplus 19h)\oplus x
$$
这个玩意怎么解呢?
$$
a=((x\%17+b)\oplus 19h)\oplus x\\
a=(x\%17+b)\oplus x\oplus 19h\\
a\oplus 19h=(x\%17+b)\oplus x
$$


再往下不会解了,但是a,b,x都是字节大小的,也就是说,其范围在0到255之间,显然可以枚举x值暴力破解

并且满足这个等式的x可能不止一个,input[26]的值会影响input[25]的计算,因此input[26]必须唯一确定才可以继续进行下去,

怎么唯一确定?一开始我寄希望于第二个校验sub_401550(input_copy),然而查了函数用到的常数发现是一个SHA-256加密,显然不能寄希望于他了

那么只能暴力破解了,以input[27]为根,可以得到一个解的树,又前7个字符一定是"moectf{",因此暴力枚举数为$x^{20}$

当x=2,结果为1'048'576,1e6量级可以在1s内跑完

当x=3,结果为3'486'784'401,可以在10s内跑完,还是可以容忍的

因此可以写出DFS算法了

```c
#include <iostream>
using namespace std;
unsigned char Str2[28] = {
    0x02, 0x18, 0x0F, 0xF8, 0x19, 0x04, 0x27, 0xD8, 0xEB, 0x00, 0x35, 0x48, 0x4D, 0x2A, 0x45, 0x6B, 
    0x59, 0x2E, 0x43, 0x01, 0x18, 0x5C, 0x09, 0x09, 0x09, 0x09, 0xB5, 0x7D
};
bool check(unsigned char a,unsigned char b,unsigned char x){
    return (a^0x19)==((x%17+b)^x);
}
unsigned char  moectf[]="moectf{";//最开始7个字符是固定的
unsigned char  input[28];
void printInput(){
    for(int i=0;i<28;++i){
        cout<<(char)input[i];
    }
    cout<<endl;
}
unsigned char temp[28];
void DFS(int depth){
    printInput();
    // cout<<depth<<endl;
    if(depth==0){
        
    }
    if(depth<=6){
        if(input[depth]!=moectf[depth])return;
    }
    for(unsigned char j=20;j<128;++j){
        // cout<<j<<" ";
        if(check(Str2[depth-1],Str2[depth],j)){
            input[depth-1]=j;
            temp[depth-1]=Str2[depth-1];
            Str2[depth-1]=j;
            DFS(depth-1);
            Str2[depth-1]=temp[depth-1];//还原Str2原值
            input[depth-1]=' ';
        }
    }
}


int main(){
    input[27]=Str2[27];//结尾字符是固定的
    DFS(27);


    return 0;
}
```



运行

```c
PS C:\Users\86135\Desktop\moectf\Art> ./main
}
 }
!}
 !}
...
mectf{Art_i5_b14s7ing!!!!!}
oectf{Art_i5_b14s7ing!!!!!}
ioectf{Art_i5_b14s7ing!!!!!}
moectf{Art_i5_b14s7ing!!!!!}
moectf{Art_i5_b14s7ing!!!!!}
...
```

这就出来了







### chicken_soup

```c
  puts("Come on! Give me your flag:");
  scanf("%s", (char)input);
  if ( strlen(input) == 38 )
  {
    ((void (__cdecl *)(char *))encrypt1)(input);
    ((void (__cdecl *)(char *))encrypt2)(input);
    if ( !strcmp((int)input, (int)&target) )
      puts("\nQwQ, please try again.");
    else
      puts("\nTTTTTTTTTTQQQQQQQQQQQQQLLLLLLLLL!!!!");
```

输入38个字符给input

encrypt1和encrypt2两个函数对input进行了一些加密,然后和target比较,如果完全相同则成功

target已知,问题就是求两个加密函数的逆

这俩加密函数就是毒鸡汤了

```asm
.text:00801000 encrypt1:                               ; CODE XREF: _main+85↓p
.text:00801000                 push    ebp
.text:00801001                 mov     ebp, esp
.text:00801003                 sub     esp, 14h
.text:00801006                 push    ebx
.text:00801007                 push    esi
.text:00801008                 push    edi
.text:00801009                 jz      short loc_80100E
.text:0080100B                 jnz     short loc_80100E
.text:0080100B ; ---------------------------------------------------------------------------
.text:0080100D                 db 0E9h
.text:0080100E ; ---------------------------------------------------------------------------
.text:0080100E
.text:0080100E loc_80100E:                             ; CODE XREF: .text:00801009↑j
.text:0080100E                                         ; .text:0080100B↑j
.text:0080100E                 mov     dword ptr [ebp-8], 0
.text:00801015                 jmp     short loc_801020
```

在`.text:00801009 `和`.text:0080100B`两个位置都有跳转,真是蜜汁操作

然后0x80100D白空出一个字节来,这样一捣鼓,ida可算是不知道该干啥了,怎么text节会有data啊?为啥0x80100D这里的一个字节没人要啊?

好了,F5反编译和空格图视图都寄了,只能嗯分析汇编指令了

首先要知道调用两个函数时,如何传参

```asm
.text:00CD1241 loc_CD1241:                             ; CODE XREF: _main+6D↑j
.text:00CD1241 lea     eax, [ebp+input]
.text:00CD1244 push    eax
.text:00CD1245 call    encrypt1
.text:00CD124A add     esp, 4
.text:00CD124D lea     ecx, [ebp+input]
.text:00CD1250 push    ecx
.text:00CD1251 call    encrypt2
```

都是把input的地址压到栈顶作为唯一的参数,然后call又会将返回地址压到栈顶





倒着看

#### encrypt2

##### 开端@00CD1080

```asm
.text:00CD1080 encrypt2:                               ; CODE XREF: _main+91↓p
.text:00CD1080 push    ebp
.text:00CD1081 mov     ebp, esp
.text:00CD1083 sub     esp, 14h
.text:00CD1086 push    ebx
.text:00CD1087 push    esi
.text:00CD1088 push    edi
.text:00CD1089 jz      short loc_CD108E
.text:00CD108B jnz     short loc_CD108E
.text:00CD108D nop                                     ; [Keypatch] modified this from:
.text:00CD108D                                         ;   db 0E9h
.text:00CD108E
```

首先将调用者ebp压栈保存,然后ebp指向此时的栈顶,那么[ebp+0x8]就是input的地址,[ebp+0x4]就是返回地址

其他寄存器压栈以及抬栈都无关紧要

下面就执行到0xCD108E位置了

##### 外圈循环初始化循环@00CD108E

```asm
.text:00CD108E loc_CD108E:                             ; CODE XREF: .text:00CD1089↑j
.text:00CD108E                                         ; .text:00CD108B↑j
.text:00CD108E mov     dword ptr [ebp-8], 0	;外圈循环变量
.text:00CD1095 jmp     short loc_CD10A0
```

这里有个"跳转到中间"循环结构

上一条指令的[ebp-8]置0,很可能是在初始化循环变量,i=0

0xCD1097处三条指令将[ebp-8]自增1,更加证明了这一点

##### 外圈循环变量自增@loc_CD1097

由于跳转到中间,第一次不会执行该自增,后来循环时才会

```asm
.text:00CD1097 ; ---------------------------------------------------------------------------
.text:00CD1097
.text:00CD1097 loc_CD1097:                             ; CODE XREF: .text:00CD10FA↓j
.text:00CD1097 mov     eax, [ebp-8]
.text:00CD109A add     eax, 1
.text:00CD109D mov     [ebp-8], eax
```



##### 外圈循环体上@loc_CD10A0

跟随控制流,直接跳入循环体

```asm
.text:00CD10A0 loc_CD10A0:                             ; CODE XREF: .text:00CD1095↑j
.text:00CD10A0 mov     ecx, [ebp+8];&input->ecx
.text:00CD10A3 mov     [ebp-0Ch], ecx;&input->ecx->ebp-0xC
.text:00CD10A6 mov     edx, [ebp-0Ch];&input->ecx->ebp-0xC->edx
.text:00CD10A9 add     edx, 1;input指针后移一个字节
.text:00CD10AC mov     [ebp-10h], edx;pinput=input+1->ebp-0x10
```

##### 内圈循环体@loc_CD10AF



```asm
.text:00CD10AF loc_CD10AF:                             ; CODE XREF: .text:00CD10BF↓j
.text:00CD10AF mov     eax, [ebp-0Ch];input->eax
.text:00CD10B2 mov     cl, [eax];取出一个字符->cl
.text:00CD10B4 mov     [ebp-1], cl;该字符->ebp-1
.text:00CD10B7 add     dword ptr [ebp-0Ch], 1;pinput++
.text:00CD10BB cmp     byte ptr [ebp-1], 0;判断pinput是否到了\0结束符
.text:00CD10BF jnz     short loc_CD10AF;如果还没有结束则循环
```

##### 外圈跳出循环@00CD10C1

```asm
.text:00CD10C1 mov     edx, [ebp-0Ch];pinput->edx
.text:00CD10C4 sub     edx, [ebp-10h];计算input的长度,放到edx中
.text:00CD10C7 mov     [ebp-14h], edx;
.text:00CD10CA mov     eax, [ebp-8]
.text:00CD10CD cmp     eax, [ebp-14h]
.text:00CD10D0 jnb     short loc_CD10FC
```



##### 外圈循环体下@00CD10C1

```asm
.text:00CD10D2 mov     ecx, [ebp+8];&input
.text:00CD10D5 add     ecx, [ebp-8];&input+i=&input[i]
.text:00CD10D8 movzx   edx, byte ptr [ecx];input[i]->edx
.text:00CD10DB sar     edx, 4;input[i]>>4->edx
.text:00CD10DE mov     eax, [ebp+8];&input
.text:00CD10E1 add     eax, [ebp-8];&input+i=&input[i]
.text:00CD10E4 movzx   ecx, byte ptr [eax];input[i]->ecx
.text:00CD10E7 shl     ecx, 4;input[i]<<4->ecx
.text:00CD10EA or      edx, ecx;(input[i]<<4)|(input[i]>>4)->edx
.text:00CD10EC and     edx, 0FFh;edx&0xFF->edx
.text:00CD10F2 mov     eax, [ebp+8]
.text:00CD10F5 add     eax, [ebp-8]
.text:00CD10F8 mov     [eax], dl;input[i]=((input[i]<<4)|(input[i]>>4))%128
```

##### 外圈重新循环@00CD10FA

```asm
.text:00CD10FA jmp     short loc_CD1097;
```



##### 尾声@loc_CD10FC

```asm
.text:00CD10FC loc_CD10FC:                             ; CODE XREF: .text:00CD10D0↑j
.text:00CD10FC pop     edi
.text:00CD10FD pop     esi
.text:00CD10FE pop     ebx
.text:00CD10FF mov     esp, ebp
.text:00CD1101 pop     ebp
.text:00CD1102 retn
```

#### 总结encrypt2

encrypt2干了个啥事呢?

```c
void encrypt2(char *input){
	for(int i=0;i<strlen(input);++i){
		input[i]=((input[i]<<4)|(input[i]>>4))%128
	}
}
```

出题人直接禁用了编译优化,这导致每次循环都要strlen计算input的长度.strlen并没有调用函数,其逻辑直接放到循环中了

解密就好说了

encrypt2(input)之后,input要和target相等,即加密后的input[i]=target[i]
$$
target[i]=(x[i]<<4\ or\ x[i]>>4)\%128
$$


只需要解这个方程

不好解直接枚举x[i]从0到128即可



#### encrypt1@0xD41000



##### 开端@00D41000

```asm
.text:00D41000 loc_D41000:                             ; CODE XREF: _main+85↓p
.text:00D41000 push    ebp
.text:00D41001 mov     ebp, esp
.text:00D41003 sub     esp, 14h
.text:00D41006 push    ebx
.text:00D41007 push    esi
.text:00D41008 push    edi
.text:00D41009 jz      short loc_D4100E
.text:00D4100B jnz     short loc_D4100E
```



##### 跳入循环中间

```asm
.text:00D4100E loc_D4100E:                             ; CODE XREF: .text:00D41009↑j
.text:00D4100E                                         ; .text:00D4100B↑j
.text:00D4100E mov     dword ptr [ebp-8], 0
.text:00D41015 jmp     short loc_D41020
```

##### 自增循环变量

```asm
.text:00D41017 loc_D41017:                             ; CODE XREF: .text:00D41072↓j
.text:00D41017 mov     eax, [ebp-8]
.text:00D4101A add     eax, 1
.text:00D4101D mov     [ebp-8], eax
```

##### 循环体上

```asm
.text:00D41020 loc_D41020:                             ; CODE XREF: .text:00D41015↑j
.text:00D41020 mov     ecx, [ebp+8]
.text:00D41023 mov     [ebp-0Ch], ecx
.text:00D41026 mov     edx, [ebp-0Ch]
.text:00D41029 add     edx, 1
.text:00D4102C mov     [ebp-10h], edx
```

##### 计算input长度

```asm
.text:00D4102F loc_D4102F:                             ; CODE XREF: .text:00D4103F↓j
.text:00D4102F mov     eax, [ebp-0Ch]
.text:00D41032 mov     cl, [eax]
.text:00D41034 mov     [ebp-1], cl
.text:00D41037 add     dword ptr [ebp-0Ch], 1
.text:00D4103B cmp     byte ptr [ebp-1], 0
.text:00D4103F jnz     short loc_D4102F;input遍历到头了,应该尾声了
```

##### 是否跳出循环

```asm
.text:00D41041 mov     edx, [ebp-0Ch]
.text:00D41044 sub     edx, [ebp-10h]
.text:00D41047 mov     [ebp-14h], edx
.text:00D4104A mov     eax, [ebp-14h]
.text:00D4104D sub     eax, 1
.text:00D41050 cmp     [ebp-8], eax
.text:00D41053 jnb     short loc_D41074
```

##### 循环体下

```asm
.text:00D41055 mov     ecx, [ebp+8]
.text:00D41058 add     ecx, [ebp-8]
.text:00D4105B movzx   edx, byte ptr [ecx+1]
.text:00D4105F mov     eax, [ebp+8]
.text:00D41062 add     eax, [ebp-8]
.text:00D41065 movzx   ecx, byte ptr [eax]
.text:00D41068 add     ecx, edx
.text:00D4106A mov     edx, [ebp+8]
.text:00D4106D add     edx, [ebp-8]
.text:00D41070 mov     [edx], cl
.text:00D41072 jmp     short loc_D41017
```

**input[i+1]+input[i]->input[i]**



##### 尾声

```asm
.text:00D41074 loc_D41074:                             ; CODE XREF: .text:00D41053↑j
.text:00D41074 pop     edi
.text:00D41075 pop     esi
.text:00D41076 pop     ebx
.text:00D41077 mov     esp, ebp
.text:00D41079 pop     ebp
.text:00D4107A retn
```



#### encrypt1总结

就干了一个事情

**input[i+1]+input[i]->input[i]**





综上可以写解密了





### fake_key

```c
  target_length = strlen(aYunzh1jun);
  puts("Now give me your flag:");
  scanf("%s", input);
  input_length = strlen(input);
  for ( i = 0; i < input_length; ++i )
    input[i] ^= aYunzh1jun[i % target_length];
  for ( j = 0; j < input_length; ++j )
    input[j] += rand() % 10;
  if ( (unsigned int)strcmp(input, &ans) )
    puts("\nRight! TTTTTQQQQQLLLLL!!!");
```

这个ans长这个样子

```c
unsigned char ans[30] = {
    0x15, 0x21, 0x0F, 0x19, 0x25, 0x5B, 0x19, 0x39, 0x5F, 0x3A, 0x3B, 0x30, 0x74, 0x07, 0x43, 0x3F, 
    0x09, 0x5A, 0x34, 0x0C, 0x74, 0x3F, 0x1E, 0x2D, 0x27, 0x21, 0x12, 0x16, 0x1F, 0x00
};
```

aYunzhijun这个字符串首先作为密钥和input进行异或加密,如果aYunzhijun不够长则循环使用

加密之后的input再与rand()%10异或加密,显然中途没有更换种子,rand()产生的随机数序列应该是相同的,这个可以动态调试观察

最后strcmp(input,ans)要求input长度为29并且和ans得相同

下面输入29个A动态调试观察随机数序列

![image-20221001162104469](https://raw.githubusercontent.com/DeutschBall/DeutschBall/main/image-20221001162104469.png)

在call rand上下断点,用F9就可以执行下一个rand,每次的结果都会放在eax中,从寄存器视图可以直接观察,

前三个随机数是0x29,0x4823,0x18BE,写一个程序暴力找一下种子是多少

当rand(1)的时候恰好前三个就是,并且第四个是0x6784和fake_key中的第四个随机数相同,因此可以确定种子就是1

后面倒回去就可以了

