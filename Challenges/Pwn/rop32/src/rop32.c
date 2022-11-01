// gcc -m32 rop32.c -fno-stack-protector -no-pie -o pwn
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char binsh[] = "/bin/sh";

void vuln() {
    char buf[20];
    read(0, buf, 0x28);
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
