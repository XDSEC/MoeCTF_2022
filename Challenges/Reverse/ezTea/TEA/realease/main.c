#include <stdio.h>
#include <stdint.h>

void encrypt (uint32_t* v, uint32_t* k) {                       // 主要加密函数，试着搞定它
    uint32_t v0 = v[0], v1 = v[1], sum = 0;
    uint32_t delta = 0xd33b470;
    for (int i = 0; i < 32; i++) {
        sum += delta;
        v0 += ((v1<<4) + k[0]) ^ (v1 + sum) ^ ((v1>>5) + k[1]);
        v1 += ((v0<<4) + k[2]) ^ (v0 + sum) ^ ((v0>>5) + k[3]);
    }
    v[0] = v0;
    v[1] = v1;
}

int main() {
    uint32_t k[4] = {1, 2, 3, 4};
    int8_t input[33] = {0};
    
    scanf("%32s", input);
    for (int i = 0; i < 32; i+=8) {
        uint32_t v[2] = {*(uint32_t *)&input[i], *(uint32_t *)&input[i+4]};
        encrypt(v, k);
        for (int j = 0; j < 2; j++) {                           // 这一段主要是把 v 按单字节输出，另外可以了解一下 “大小端序” 在这题是如何体现的
            for (int k = 0; k < 4; k++) {
                printf("%#x, ", v[j] & 0xff);
                v[j] >>= 8;
            }
        }
    }
    return 0;
}