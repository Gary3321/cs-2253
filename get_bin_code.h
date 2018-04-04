#ifndef _GET_BIN_CODE_H
#define _GET_BIN_CODE_H
char* get_operand_bin(char *operand);
char* read_symbol_table(char* symbol);
void get_code_bin(char* operation, char* operand1, char* operand2, char* operand3, FILE *fp_w, int pc);
#endif