// gcc rop64.c -no-pie -o pwn
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char binsh[] = "/bin/sh";

void gadget() {
    asm volatile(
        "pop %rdi;"
        "ret;");
}

void vuln() {
    char buf[40];
    memset(buf, 0, 40);

    read(0, buf, 0x30);
    printf("%s", buf);
    read(0, buf, 0x50);
    return;
}

int main() {
    system("echo Go Go Go!!!\n");
    vuln();
    return 0;
}

__attribute__((constructor)) void unbuffer() {
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
}
