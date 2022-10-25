#include <stdio.h>
#include <stdint.h>

uint32_t k[4] = {1, 2, 3, 4};
uint8_t sec[] = { 0x17, 0x65, 0x54, 0x89, 0xed, 0x65, 0x46, 0x32,
                  0x3d, 0x58, 0xa9, 0xfd, 0xe2, 0x5e, 0x61, 0x97,
                  0xe4, 0x60, 0xf1, 0x91, 0x73, 0xe9, 0xe9, 0xa2,
                  0x59, 0xcb, 0x9a, 0x99, 0xec, 0xb1, 0xe1, 0x7d };

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
    for (int i = 0; i < 32; i += 8) {
        uint32_t v[2] = {*(uint32_t *)&sec[i], *(uint32_t *)&sec[i+4]};
        decrypt(v, k);
        printf("%s", (char *)v);
    }
    return 0;
}