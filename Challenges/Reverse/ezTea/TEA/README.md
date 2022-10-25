# TEA 的解题思路 | 测题用

## 目录结构

```
.
├── README.md
├── realease            // 附件原文件和压缩包，记得确认一下不要压缩错了
│   ├── main.c          // 源码题附件
│   └── tutorial.pdf    // 题目描述与指引
├── src                 // 出题代码
│   ├── keygen.c        // 解密脚本
│   └── main.c
└── test                // 一些小测试
    └── test-sum.c
```

## 题目信息

| 题目名 | 类型  | 难度  |
| --- | --- | --- |
| TEA | Rev | 简单  |

## FLAG

moectf{Th3_TEA_!S_s0_t4s7y~~!!!}

## 知识点

- C 基础
- TEA 算法逆向

## 解题步骤

源码逆算法，显然是 TEA，虽然 delta 改变了，不影响我们直接解密，C 语言写 exp 见附件中