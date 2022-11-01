// gcc syscall.c -fno-stack-protector -o pwn
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char binsh[] = "/bin/sh";

void gadget() {
    asm volatile(
        "pop %rdi;"
        "ret;"
        "pop %rsi;"
        "pop %rdx;"
        "ret;"
        "syscall");
}

void vuln() {
    char buf[60];
    read(0, buf, 0x80);
    read(0, buf, 60);
    return;
}

int main() {
    printf("I'll give you a gift first!\n");
    printf("%p\n", gadget);
    printf("Go Go Go!!!\n");
    vuln();
    return 0;
}

__attribute__((constructor)) void unbuffer() {
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
}
