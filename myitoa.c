#include <stdio.h>


char* itoa(int num, char* str, int base)
{
typedef int bool;
#define true 1
#define false 0
    int i = 0;
    bool isNegative = false;
 
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with 
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
}
    return 0;
}

int main()
{
    char str[100];
printf ("Base:10%s ", itoa(1567, str, 10));
printf ("Base:2%s ", itoa(1567, str, 2));
printf ("Base:8%s ", itoa(1567, str, 8));
printf ("Base:16%s ", itoa(1567, str, 16));
    return 0;
}
