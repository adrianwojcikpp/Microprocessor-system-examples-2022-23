/**
  ******************************************************************************
  * @file    input_validation.c
  * @author  AW		adrian.wojcik@put.poznan.pl
  * @version 3.0
  * @date    22-May-2022
  * @brief   User input validation example
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

/* Private function ----------------------------------------------------------*/
/**
 * @brief Checks whether message contains only given characters
 * 
 * @param[in] msg : User input
 * @param[in] key : String with allowed characters
 * @retval 1 if user input contains only characters in given key
 *         0 otherwise
 */
_Bool MESSAGE_ContainsOnly(const char* msg, const char* key)
{
    while(*msg != '\0')
    {
        if(msg != strpbrk(msg,key))
            return 0;
        msg++;
    }
    return 1;
}

/**
 * @brief Checks whether message is terminated with given sequence
 * 
 * @param[in] msg : User input
 * @param[in] terminator : Expected sequence at the and of user input
 * @retval 1 if user input is terminated as expected
 *         0 otherwise
 */
_Bool MESSAGE_TerminateWith(const char* msg, const char* terminator)
{
    int p = strlen(msg) - strlen(terminator);
    return (&msg[p] == strstr(msg,terminator));
}

/**
 * @brief Checks whether message is valid: contains only '0', '1',
 *        '\r' and '\n' and is terminated with "\r\n" sequence
 * 
 * @param[in] msg : User input
 * @retval 1 if user input is valid
 *         0 otherwise
 */
_Bool MESSAGE_IsValid(const char* msg)
{
    return MESSAGE_ContainsOnly(msg, "01\r\n") && MESSAGE_TerminateWith(msg, "\r\n");
}

/* Main function -------------------------------------------------------------*/

/**
  * @brief  The application entry point.
  * @retval 0 
  */
int main()
{
    // User input
    //char msg[] = "101010101\r\n"; // valid input 
    char msg[] = "101010101\n\r"; // invalid input 

    // Print validation results
    printf("User input content: %s\nUser input is %svalid\n", msg, MESSAGE_IsValid(msg) ? "" : "in");

    return 0;
}
