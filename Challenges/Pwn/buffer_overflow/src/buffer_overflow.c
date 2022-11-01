// gcc buffer_overflow.c -o pwn
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char ans[] = "Limiter and Wings are beautiful girls!";

int main() {
    struct noteBook {
        char str1[70];
        char str2[70];
    } data;
    memset(&data, 0, sizeof(data));
    strcpy(data.str2, "Limiter and Wings are handsome boys!");

    printf("Write down your note:\n");
    read(0, data.str1, 0x70);
    sleep(1);

    printf("This is my note:\n");
    sleep(1);
    printf("%s\n", data.str2);
    sleep(1);
    sleep(1);

    if (!strcmp(data.str2, ans)) {
        printf("Wow they are really cute...\n");
        sleep(1);
        printf("And this is a gift for you^_^!\n");
        sleep(1);
        system("cat ./flag");
    } else {
        printf("No, They are beautiful girls!\n");
        sleep(1);
    }
    return 0;
}

__attribute__((constructor)) void unbuffer() {
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
}
