#include <stdio.h>

int myAtoi(char *str)
{
    int result = 0;   
    int sign = 1;   
    int i = 0;   
      
    // negative number
    if (str[0] == '-')
    {
        sign = -1;  
        i++;   
    }
      
     
    for (; str[i] != '\0'; ++i)
        result = result*10 + str[i] - '0';
 
    return sign*result;
}
  
// Driver program to test above function
int main()
{
    char str[] = "3123";
    int val = myAtoi(str);
    printf ("%d ", val);
    return 0;
}
