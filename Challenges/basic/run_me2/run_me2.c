#include <stdio.h>
#include <string.h>
//moectf{run_m3_t0_g3t_th3_f1ag}
unsigned char flag[]={146,144,154,156,139,153,132,141,138,145,160,146,204,160,139,207,160,152,204,139,160,139,151,204,160,153,206,158,152,130,0};

int main()
{   
    int i;

    for(i = 0; i < strlen(flag); i++)
        printf("%c", flag[i]^0xff);

    return 0;
}

