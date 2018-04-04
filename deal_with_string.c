#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "deal_with_string.h"

char* replacestring(char* src, char* dst)
{
	char* p=dst;
	
	while(*src==' ') //remove first spaces
	{
		src++;
	}
	while(*src) //copy the operation which seperates by space
	{
		*p=*src;
		p++;
		src++;
		if(*src==' ' && *(src+1)!=' ')
		{
			//src++;
			break;
		}
	}
	while(*src)
	{
		
		while(*src==' ' && *(src+1)==' ') //replace many spaces with one space
			src++;
		*p=*src;
		p++;
		src++;		
		if(*src==' ') //replace space with comma
		{
			*p=',';
			p++;
			src++;
		}
		if(*src==';') //don't copy comments
			break;
	}
	*p='\0';
	if(*(p-1)==',')
	{
		*(p-1)=' ';
		//*(++p)='\0';
	}
	return dst;
}

char *upper(char *src)
{
	char *des =src;
	while(*src != '\0')
	{
		if (*src >= 'a' && *src <='z') //convert to upper
			*src -= 'a'-'A';
		src++;
	}
	return des;
}

void trim_string(char *str)  
{  
    char *start, *end;  
    int len = strlen(str);  
  
    //去掉最后的换行符  
    if(str[len-1] == '\n')  
    {  
        len--;      //字符串长度减一  
        str[len] = 0;   //给字符串最后一个字符赋0，即结束符  
    }  
  
    //去掉两端的空格  
    start = str;        //指向首字符  
    end = str + len -1; //指向最后一个字符  
    while(*start && isspace(*start))  
        start++;    //如果是空格，首地址往前移一位，如果不是，则跳过该循环  
    while(*end && isspace(*end))  
        *end-- = 0; //如果是空格，末地址往前移一位，并赋结束符  
    strcpy(str, start); //把首地址还给str  
}  
/*int main()
{
	char* a=" and r1,R1 0";
	char out[100];
	replacestring(a,out);
	printf("%s\n",upper(out));
	return 0;
}
*/