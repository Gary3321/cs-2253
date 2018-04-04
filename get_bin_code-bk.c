#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char operation[17], operand1[17], operand2[27], operand3[17];
char* get_operation_bin(char *operation);
char* get_operand_bin(char *operand);

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

char* get_operation_bin(char *operation)
{
	//char* bin_operation;
	
		if (strcmp(operation,"ADD")==0) return "0001";
		if (strcmp(operation,"AND")==0) return "0101";
		if (strcmp(operation,"BR")==0) return "0000";
		if (strcmp(operation,"JMP")==0) return "1100";
		if (strcmp(operation, "JSR")==0) return "0100";
		if (strcmp(operation, "JSRR")==0) return "0100";
		if (strcmp(operation, "LD")==0) return "0010";
		if (strcmp(operation, "LDI")==0) return "1010";
		if (strcmp(operation, "LDR")==0) return "0110";
		if (strcmp(operation, "LEA")==0) return "1110";
		if (strcmp(operation, "NOT")==0) return "1001";
		if (strcmp(operation, "RET")==0) return "1100";
		if (strcmp(operation, "RTI")==0) return "1000";
		if (strcmp(operation, "ST")==0) return "0011";
		if (strcmp(operation, "STI")==0) return "1011";
		if (strcmp(operation, "STR")==0) return "0111";
		if (strcmp(operation, "TRAP")==0) return "1111";
		else return '\0';
	
	
}

char* get_operand_bin(char *operand)
{
		if (strstr(operand,"R"))
		{ printf("test...");
			if (strcmp(operand, "R0")==0) return "000";
		if (strcmp(operand, "R1")==0) return "001";
		if (strcmp(operand, "R2")==0) return "010";
		if (strcmp(operand, "R3")==0) return "011";
		if (strcmp(operand, "R4")==0) return "100";
		if (strcmp(operand, "R5")==0) return "101";
		if (strcmp(operand, "R6")==0) return "110";
		if (strcmp(operand, "R7")==0) return "111";
		else return ""; //return null
		}
		else return ""; //return null
}
char* read_symbol_table(char* symbol)
{
	FILE *fp=fopen("symbol_table.sym","r");
	char data[1000];
	char* ptr;
	if(!fp)
    {
        printf("can't open file\n");
        return false;
    }
	while ((fgets(data,1000,fp))!=NULL)
	{
	if(strlen(data)!=1) 
	{
		ptr=strtok(data," ");
		trim_string(ptr);//remove space and enter
		if(strcmp(ptr,symbol)==0)
		{
			ptr = strtok(NULL," ");
			trim_string(ptr);
			return ptr;
		}
	}
	}
	return "0000";//error
}
void get_code_bin(char* operation, char* operand1, char* operand2, char* operand3, FILE *fp_w, int pc)
{
	char* op3=get_operand_bin(operand3);
	char* op2=get_operand_bin(operand2);
	char* op1=get_operand_bin(operand1);
	char* sysbol_address;
	char code[16]; //bin code
	char binary[16]; //binary
	char binary_full[16]; //binary with length of 5
	int op3_int,offset;
	//char *code_bin;
	if (strcmp(operation,"ADD")==0)
	{
		strcat(code,"0001"); 
		strcat(code,op1);
		strcat(code,op2);
		if (strlen(op3)>1) //op3 is a register
		{
			
			strcat(code,"000");
			strcat(code,op3);
			
		}
		else
		{
			if (strstr(operand3,"#")) //operand3 includs "#"
				itoa(atoi(strstr(operand3,"#")+1),binary,2); //convert to binary
			else
				itoa(atoi(operand3),binary,2); //convert to binary
			//printf("binary=%05s",binary);	
			sprintf(binary_full,"%05s",binary);//add 0 to left
			strcat(code,"1");
			strcat(code,binary_full);
			
			
		}
		
			printf("code=%s ",code);
	}
	else if (strcmp(operation,"AND")==0)
	{
		strcat(code,"0101"); 
		strcat(code,op1);
		strcat(code,op2);
		if (strlen(op3)>1) //op3 is a register
		{
			
			strcat(code,"000");
			strcat(code,op3);
			
		}
		else
		{
			if (*operand3=='#')//(strstr(operand3,"#")) //operand3 includs "#"
				itoa(atoi(strstr(operand3,"#")+1),binary,2); //convert to binary
			else
				itoa(atoi(operand3),binary,2); //convert to binary
			//printf("binary=%05s",binary);	
			sprintf(binary_full,"%05s",binary);//add 0 to left
			strcat(code,"1");
			strcat(code,binary_full);
			
			
		}
		
			printf("code=%s ",code);
	}
	else if (strcmp(operation,"JMP")==0)
	{
		strcat(code,"1100"); 
		strcat(code,"000");
		strcat(code,op1);
		strcat(code,"000000");
		printf("code=%s ",code);
		//get_code_bin("JMP","R1","R1","0");
	}
	else if (strcmp(operation,"NOT")==0)
	{
		strcat(code,"1001"); 
		strcat(code,op1);
		strcat(code,op2);
		strcat(code,"111111"); 
	}
	else if (strcmp(operation,"LD")==0 || strcmp(operation,"ST")==0 || strcmp(operation,"LDI")==0 || strcmp(operation,"STI")==0)
	{
		if (strcmp(operation,"LD")==0 )
		    strcat(code,"0010"); 
		else if (strcmp(operation,"ST")==0 )
			strcat(code,"0011");
		else if (strcmp(operation,"LDI")==0 )
			strcat(code,"1010");
		else
			strcat(code,"1011");
		strcat(code,op1);
		if (*operand2=='X')
		{
			sscanf(strstr(operand2,"X")+1,"%x",&offset);
			itoa(offset-pc-1,binary,2); //convert to binary
		}
		else
		{
			//	itoa(atoi(operand3),binary,2); //convert to binary
			sysbol_address=read_symbol_table(operand2); //get address from symbol table
			sscanf(sysbol_address,"%x",&offset); //conver to decimal
			//printf("sysbol_address=%s,offset=%d,pc=%d",sysbol_address,offset,pc);
			itoa(offset-pc-1,binary,2);
		}
		sprintf(binary_full,"%09s",binary);//add 0 to left
		//printf("binary=%s",binary_full);
		strcat(code,binary_full);
	}
	else if (strcmp(operation,"LDR")==0 || strcmp(operation,"STR")==0)
	{
		if (strcmp(operation,"LDR")==0 )
		    strcat(code,"0110"); 
		else
			strcat(code,"0111"); 
		strcat(code,op1);
		if (*operand3=='X')
		{
			sscanf(strstr(operand3,"X")+1,"%x",&offset);
			itoa(offset-pc-1,binary,2); //convert to binary
		}
		else
		{
			//	itoa(atoi(operand3),binary,2); //convert to binary
			sysbol_address=read_symbol_table(operand3); //get address from symbol table
			sscanf(sysbol_address,"%x",&offset); //conver to decimal
			//printf("sysbol_address=%s,offset=%d,pc=%d",sysbol_address,offset,pc);
			itoa(offset-pc-1,binary,2);
		}
		sprintf(binary_full,"%09s",binary);//add 0 to left
		//printf("binary=%s",binary_full);
		strcat(code,binary_full);
	}
	else if (strcmp(operation,"LEA")==0)
	{
		strcat(code,"1110"); 
		strcat(code,op1);
		if (*operand2=='#')
		{
			offset=atoi(strstr(operand2,"#")+1); //convert to integer
			itoa(offset,binary,2); //convert to binary
		}
		else
		{
			//	itoa(atoi(operand3),binary,2); //convert to binary
			sysbol_address=read_symbol_table(operand2); //get address from symbol table
			sscanf(sysbol_address,"%x",&offset); //conver to decimal
			//printf("sysbol_address=%s,offset=%d,pc=%d",sysbol_address,offset,pc);
			itoa(offset,binary,2);
		}
		sprintf(binary_full,"%09s",binary);//add 0 to left
		//printf("binary=%s",binary_full);
		strcat(code,binary_full);
	}
	else if (*(operation)=='B' && *(operation+1)=='R')
	{
		strcat(code,"0000"); 
		if(strstr(operation,"N")) //include "N"
			strcat(code,"1"); 
		else 
			strcat(code,"0"); 
		if(strstr(operation,"Z")) //include "Z"
			strcat(code,"1"); 
		else 
			strcat(code,"0");
		if(strstr(operation,"P")) //include "P"
			strcat(code,"1"); 
		else 
			strcat(code,"0");
		if (*operand1=='X')
		{
			sscanf(strstr(operand1,"X")+1,"%x",&offset); //conver to integer
			itoa(offset,binary,2); //convert to binary
		}
		else
		{
			//	itoa(atoi(operand3),binary,2); //convert to binary
			sysbol_address=read_symbol_table(operand2); //get address from symbol table
			sscanf(sysbol_address,"%x",&offset); //conver to decimal
			//printf("sysbol_address=%s,offset=%d,pc=%d",sysbol_address,offset,pc);
			itoa(offset-pc-1,binary,2);
		}
		sprintf(binary_full,"%09s",binary);//add 0 to left
		//printf("binary=%s",binary_full);
		strcat(code,binary_full);
		
	}
	else if (strcmp(operation,"JSR")==0)
	{
		strcat(code,"01001"); 
		if (*operand1=='X')
		{
			sscanf(strstr(operand1,"X")+1,"%x",&offset);
			itoa(offset-pc-1,binary,2); //convert to binary
		}
		else
		{
			//	itoa(atoi(operand3),binary,2); //convert to binary
			sysbol_address=read_symbol_table(operand1); //get address from symbol table
			sscanf(sysbol_address,"%x",&offset); //conver to decimal
			//printf("sysbol_address=%s,offset=%d,pc=%d",sysbol_address,offset,pc);
			itoa(offset-pc-1,binary,2);
		}
		sprintf(binary_full,"%011s",binary);//add 0 to left
		//printf("binary=%s",binary_full);
		strcat(code,binary_full);
	}
	else if (strcmp(operation,"TRAP")==0)
	{
		strcat(code,"00000000"); 
		
		sscanf(strstr(operand1,"X")+1,"%x",&offset); //start with "X"
			itoa(offset,binary,2); //convert to binary
			sprintf(binary_full,"%08s",binary);//add 0 to left
			//printf("binary=%s",binary_full);
			strcat(code,binary_full);
		
		
		
	}
	else if (strcmp(operation,"RET")==0)
	{
		strcat(code,"1100000111000000"); 		
			
	}
	else if (strcmp(operation,"RTI")==0)
	{
		strcat(code,"1000000000000000"); 		
			
	}
	fprintf(fp_w,"%s",strcat(code," "));
}

int main()
{
	char* operation ="ADD";
	char* operand = "R0";
	char* bin_operation=get_operation_bin(operation);
	char code[16];
	char *a='\0';
	FILE *fp_w=fopen("bin.sym","a");
	//char* code1;
	//if (strcmp(operand, "R0")==0) bin_operand="0000";
	printf("b1=%s",bin_operation);
	get_operand_bin(a);
	printf("b2=%s",get_operand_bin(a));
	printf("operantion=%s",operation);
	printf("operand=%s",operand);
	//printf("get_code_in=%s",get_code_bin("ADD","R0","R1","R2",code));
	get_code_bin("LD","R1","R2","",fp_w,0);
	//get_operand_bin(a);
	//printf("code=%s",code);
	
}

