#include <stdio.h>
#include <string.h>
//moectf{run_me_to_get_the_flag}
unsigned char flag[]={146,144,154,156,139,153,132,141,138,145,160,146,154,160,139,144,160,152,154,139,160,139,151,154,160,153,147,158,152,130,0};

int main()
{   
    int i;

    for(i = 0; i < strlen(flag); i++)
        printf("%c", flag[i]^0xff);

    return 0;
}

