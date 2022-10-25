#include <stdio.h>
#include <stdint.h>

int main() {
    uint32_t sum = 0xa6768e00;
    uint32_t delta = 0xd33b470;
    for (int i = 0; i < 32; i++) {
        sum -= delta;
        printf("SUM_%d: %#x\n", i, sum);
    }
    return 0;
}