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
  
    //ȥ�����Ļ��з�  
    if(str[len-1] == '\n')  
    {  
        len--;      //�ַ������ȼ�һ  
        str[len] = 0;   //���ַ������һ���ַ���0����������  
    }  
  
    //ȥ�����˵Ŀո�  
    start = str;        //ָ�����ַ�  
    end = str + len -1; //ָ�����һ���ַ�  
    while(*start && isspace(*start))  
        start++;    //����ǿո��׵�ַ��ǰ��һλ��������ǣ���������ѭ��  
    while(*end && isspace(*end))  
        *end-- = 0; //����ǿո�ĩ��ַ��ǰ��һλ������������  
    strcpy(str, start); //���׵�ַ����str  
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