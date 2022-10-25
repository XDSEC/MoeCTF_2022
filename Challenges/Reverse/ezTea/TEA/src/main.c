#include <stdio.h>
#include <stdint.h>
 
#define DEBUG
#define SHOW(str, x) printf("\033[0;31m%s: \033[0m%#x %#x\n", str, x[0], x[1]);

void encrypt (uint32_t* v, uint32_t* k) {
    uint32_t v0 = v[0], v1 = v[1], sum = 0;
    uint32_t delta = 0xd33b470;
    for (int i = 0; i < 32; i++) {
        sum += delta;
        // printf("EN_SUM_%d: %#x\n", i, sum);
        v0 += ((v1<<4) + k[0]) ^ (v1 + sum) ^ ((v1>>5) + k[1]);
        v1 += ((v0<<4) + k[2]) ^ (v0 + sum) ^ ((v0>>5) + k[3]);
    }
    v[0] = v0;
    v[1] = v1;
}

void decrypt (uint32_t* v, uint32_t* k) {
    uint32_t v0 = v[0], v1 = v[1], sum = 0xa6768e00;
    uint32_t delta = 0xd33b470;
    for (int i = 0; i < 32; i++) {
        // printf("DE_SUM_%d: %#x\n", i, sum);
        v1 -= ((v0<<4) + k[2]) ^ (v0 + sum) ^ ((v0>>5) + k[3]);
        v0 -= ((v1<<4) + k[0]) ^ (v1 + sum) ^ ((v1>>5) + k[1]);
        sum -= delta;
    }
    v[0] = v0;
    v[1] = v1;
}

int main() {
    uint32_t k[4] = {1, 2, 3, 4};
    int8_t input[32] = {0};
    
    scanf("%32s", input);
    #ifdef DEBUG
    for (int i = 0; i < 32; i+=8) {
    #endif
        uint32_t v[2] = {*(uint32_t *)&input[i], *(uint32_t *)&input[i+4]};
        SHOW("BEFORE", v);
        encrypt(v, k);
        SHOW("ENCRYPT", v);
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 4; k++) {
                printf("%#x, ", v[j] & 0xff);
                v[j] >>= 8;
            }
        }
        printf("%s", "\n");
        decrypt(v, k);
        SHOW("DECRYPT", v);
    #ifdef DEBUG
    }
    #endif
    return 0;
}