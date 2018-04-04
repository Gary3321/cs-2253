#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "deal_with_string.h"
#include "get_bin_code.h"
//#include "write_symbol_table.h"


//void trim_string(char *str) ;
bool write_symbol_table(char* filePath)
{
	// lines with labels must have them in the first column.
    // lines without labels must have a blank in the first column.
    char data[1000], start_address[100]="0";
	char operations[100]="ADD,AND,BR,JMP,JSR,JSRR,LD,LDI,LDR,LEA,NOT,RET,RTI,ST,STI,STR,TRAP,HALT";
	char *ptr; //store lable
	char *start, *begin; //store start address
	int pc_counter;
    FILE *fp=fopen(filePath,"r");
	FILE *fp_w = fopen("symbol_table.sym","a");
    if(!fp)
    {
        printf("can't open file\n");
        return false;
    }

    while ((fgets(data,1000,fp))!=NULL)
	{
		if(strlen(data)!=1) //don't read empty line,empty line also read "\n". 
		{	printf("%s",data);
		
		//if (data[0]!=' ')
       // {
			//printf("str2=%c",data[0]);
			ptr=strtok(data," ");
			trim_string(ptr);//remove space and enter
		if (strstr(operations,ptr)||((*ptr=='B')&&(*(ptr+1)=='R')))
		  {
			  if(strcmp(ptr,"HALT")==0) //pc counter does not increase for "HALT" instruction
				pc_counter--;
		  }
		  else 
		  {
			if(strcmp(ptr,".ORIG")==0)
			{
				start = strtok(NULL," ");
				//begin=strstr(start,"X")+1;
				//printf("start=%s,begin=%s,first=%c",strcat(start_address,start),begin,*start);
				strcat(start_address,start);
				pc_counter = strtol(start_address,NULL,16);
				pc_counter--; //first instruction is 3000
				printf("pc=%d\n",pc_counter);
				printf("pc=%04x\n",pc_counter+1);
			}
			//if(*(start)=='X')
			//printf("str2=%s%s\n",ptr,  start  );
			//printf("begin=%s\n",strcpy("0",start)  );
			else
			{
				if(strcmp(ptr,".END")!=0)
				//printf("str2=%s",ptr);
				{					
					fprintf(fp_w,"%s",strcat(ptr," "));
					fprintf(fp_w,"%04x\n",pc_counter);
				}
			}
		}
		if(strcmp(ptr,".STRINGZ")==0)
		{
			ptr=strtok(data," ");
			pc_counter=pc_counter+strlen(ptr)-2+1; //account for surrounding quotes
		}
		else 
			pc_counter++;
		}
	}
	fclose(fp_w);
    fclose(fp);
    return true;
}

bool ReadFile(char* filePath)
{
	// lines with labels must have them in the first column.
    // lines without labels must have a blank in the first column.
    char data[1000],line[1000], start_address[100]="0";
	char operations[100]="ADD,AND,BR,JMP,JSR,JSRR,LD,LDI,LDR,LEA,NOT,RET,RTI,ST,STI,STR,TRAP,HALT";
	char *ptr; //store lable
	char *operand1, *operand2, *operand3;
	char *start, *begin; //store start address
	int pc_counter;
    FILE *fp=fopen(filePath,"r");
	FILE *fp_w = fopen("bin.sym","a");
    if(!fp)
    {
        printf("can't open file\n");
        return false;
    }
	if(!fp_w)
    {
        printf("can't open file\n");
        return false;
    }

    while ((fgets(data,1000,fp))!=NULL)
	{
		if(strlen(data)!=1) //don't read empty line,empty line also read "\n". 
		{	printf("%s\n",data);
		
		//if (data[0]!=' ')
       // {
			//printf("str2=%c",data[0]);
			replacestring(data,line);
			ptr=strtok(line," ");
			trim_string(line);
			trim_string(ptr);//remove space and enter
		if (strstr(operations,ptr)||((*ptr=='B')&&(*(ptr+1)=='R')))
		  {
			  if(strcmp(ptr,"HALT")==0) //pc counter does not increase for "HALT" instruction
				pc_counter--;
			  operand1=strtok(NULL,",");
			  operand2=strtok(NULL,",");
			  operand3=strtok(NULL,",");
			  operand3='\0';
			  trim_string(operand2);
			  printf("p=%s,o1=%s,o2=%s,o3=%s,pc=%d",ptr, operand1, operand2, operand3,pc_counter);
			  get_code_bin(ptr, operand1, operand2, operand3, fp_w, pc_counter);
		  }
		  else 
		  {
			if(strcmp(ptr,".ORIG")==0)
			{
				start = strtok(NULL," ");
				//begin=strstr(start,"X")+1;
				//printf("start=%s,begin=%s,first=%c",strcat(start_address,start),begin,*start);
				strcat(start_address,start);
				pc_counter = strtol(start_address,NULL,16);
				pc_counter--; //first instruction is 3000
				//printf("pc=%d\n",pc_counter);
				//printf("pc=%04x\n",pc_counter+1);
			}
			//if(*(start)=='X')
			//printf("str2=%s%s\n",ptr,  start  );
			//printf("begin=%s\n",strcpy("0",start)  );
			/*else
			{
				if(strcmp(ptr,".END")!=0)
				//printf("str2=%s",ptr);
				{					
					fprintf(fp_w,"%s",strcat(ptr," "));
					fprintf(fp_w,"%04x\n",pc_counter);
				}
			}*/
		}
		if(strcmp(ptr,".STRINGZ")==0)
		{
			ptr=strtok(data," ");
			pc_counter=pc_counter+strlen(ptr)-2+1; //account for surrounding quotes
		}
		else 
			pc_counter++;
		}
	}
	fclose(fp_w);
    fclose(fp);
    return true;
}

int main()
{
	write_symbol_table("1.asm");
    ReadFile("1.asm");
    return 0;
}
/*
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
*/
