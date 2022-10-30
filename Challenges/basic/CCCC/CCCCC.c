#include <stdio.h>
#include <string.h>

unsigned char flag[]={146,144,154,156,139,153,132,207,151,160,134,207,138,160,156,158,145,160,141,138,145,160,158,160,188,160,143,141,207,152,141,158,146,222,130,0};

int main()
{   
    int i;

    for(i = 0; i < strlen(flag); i++)
        printf("%c", flag[i] ^ 0xff);

    return 0;
}

