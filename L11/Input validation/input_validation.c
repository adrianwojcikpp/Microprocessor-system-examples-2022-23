/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <string.h>

_Bool MESSAGE_ContainsOnly(char* msg, char* key)
{
    while(*msg != '\0')
    {
        if(msg != strpbrk(msg,key))
            return 0;
        msg++;
    }
    return 1;
}

_Bool MESSAGE_TerminateWith(char* msg, char* terminator)
{
    int p = strlen(msg) - strlen(terminator);
    return (&msg[p] == strstr(msg,terminator));
}

_Bool MESSAGE_IsValid(char* msg)
{
    return MESSAGE_ContainsOnly(msg, "01\r\n") && MESSAGE_TerminateWith(msg, "\r\n");
}

int main()
{
    char msg[] = "101010101\r\n";
    
    printf("%s: %u\n", msg, MESSAGE_IsValid(msg));

    return 0;
}
