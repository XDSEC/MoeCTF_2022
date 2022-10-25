#include<stdio.h>
#include<string.h>
#include<time.h>
//const char * base64char  = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const char * base64char  = "abcdefghijklmnopqrstuvwxyz0123456789+/ABCDEFGHIJKLMNOPQRSTUVWXYZ";
 int base64_decode( char * base64, char * originChar )//base64½âÂë
 {
     int i, j;
     unsigned char k;
     unsigned char temp[4];
     for ( i = 0, j = 0; base64[i] != '\0' ; i += 4 )
     {
         memset( temp, 0xFF, sizeof(temp) );
         for ( k = 0 ; k < 64 ; k ++ )
         {
             if ( base64char[k] == base64[i] )
                 temp[0]= k;
         }
         for ( k = 0 ; k < 64 ; k ++ )
         {
             if ( base64char[k] == base64[i+1] )
                 temp[1]= k;
         }
         for ( k = 0 ; k < 64 ; k ++ )
         {
             if ( base64char[k] == base64[i+2] )
                 temp[2]= k;
         }
         for ( k = 0 ; k < 64 ; k ++ )
         {
             if ( base64char[k] == base64[i+3] )
                 temp[3]= k;
         }
  
         originChar[j++] = ((unsigned char)(((unsigned char)(temp[0] << 2))&0xFC)) |
                 ((unsigned char)((unsigned char)(temp[1]>>4)&0x03));
         if ( base64[i+2] == '=' )
             break;
  
         originChar[j++] = ((unsigned char)(((unsigned char)(temp[1] << 4))&0xF0)) |
                 ((unsigned char)((unsigned char)(temp[2]>>2)&0x0F));
         if ( base64[i+3] == '=' )
             break;
  
         originChar[j++] = ((unsigned char)(((unsigned char)(temp[2] << 6))&0xF0)) |
                 ((unsigned char)(temp[3]&0x3F));
     }
     return j;
 }
 
 int main(){
 	
     char base64[]="1wX/yRrA4RfR2wj72Qv52x3L5qa=";
     char de64[20];
     char inp[20];
     printf("Welcome to moectf,plz input your flag!\n");
     gets(inp);
     base64_decode(base64,de64);
     if(!strcmp(de64,inp)){
	 	printf("great!");
     }else{
	 	printf("wrong!");
	 }
	 char a [50];
		gets(a);
     return 0;
 }
 
 
 
