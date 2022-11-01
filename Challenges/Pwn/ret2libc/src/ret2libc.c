// gcc ret2libc.c -fno-stack-protector -no-pie -o pwn
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void gadget() {
    asm volatile(
        "pop %rdi;"
        "ret;");
}

void vuln() {
    char buf[60];
    read(0, buf, 0x70);
    return;
}

int main() {
    puts("Go Go Go!!!");
    vuln();
    return 0;
}

__attribute__((constructor)) void unbuffer() {
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
}
