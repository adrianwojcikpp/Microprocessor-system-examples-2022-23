/**
  ******************************************************************************
  * @file    L04_example_01.c
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 2.0
  * @date    14-Mar-2022
  * @brief   Instruction #04 bit manipulation playground
  *
  ******************************************************************************
  */

/* Includes -------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* Define --------------------------------------------------------------------*/
#define COLORED_CONSOLE 1

/* Function prototypes -------------------------------------------------------*/
void uint32_to_binstr(uint32_t num, char* binstr);

/* Macro ---------------------------------------------------------------------*/

/// @brief Naming convention: binary string buffer name postfix
#define __binstr(name) name##_binstr

/// @brief Defines buffer of <size> for <name> variable
#define __binstr_buf(name, size)  char __binstr(name)[size] = {0,};\
                                  uint32_to_binstr(name, __binstr(name))
/// @brief Bitwise operations result table header
#define __print_tab_header(op_name) printf("[%4s]              | HEX        | DEC        | BIN\n", op_name);\
                                    puts("----------------------------------------------------------------------------------")

/* Function definitions ------------------------------------------------------*/

/**
 * @brief Unsigned integer (32 bits) to C-string.
 * @param[in]  num    Input unsigned 32 bits integer.
 * @param[out] binstr Output binary string with leading zeros.
 *                    Have to be at least 320 byte buffer. 
 * @retval None.
 */
void uint32_to_binstr(uint32_t num, char* binstr)
{
  for(int i = 0; i < 8*sizeof(num); i++)
  {
    #if COLORED_CONSOLE 
    memcpy(&binstr[i*10], ((1u << i) & num) ? "\033[31m1\033[0m" : "\033[32m0\033[0m", 10);
    #else
    binstr[i] = ((1u << i) & num) ? '1' : '0';
    #endif
  }
}

/**
  * @brief Print binary bitwise operation result.
  * @param[in] arg1 Left-hand side argument.
  * @param[in] arg2 Right-hand side argument.
  * @param[in] rslt Operation result.
  * @param[in] op_name   Operation name (4 character string).
  * @param[in] op_symbol Operation symbol (single character).
  * @retval None.
  */
void print_binary_bitwise_operation(uint32_t arg1, uint32_t arg2, uint32_t rslt, char* op_name, char op_symbol)
{
  __binstr_buf(arg1, 512);
  __binstr_buf(arg2, 512);
  __binstr_buf(rslt, 512);

  __print_tab_header(op_name); 
  printf("ARG #1              : 0x%08x | %10u | 0b%32s\n", arg1, arg1, __binstr(arg1));
  printf("ARG #2              : 0x%08x | %10u | 0b%32s\n", arg2, arg2, __binstr(arg2));
  printf("(ARG #1) %c (ARG #2) : 0x%08x | %10u | 0b%32s\n\n", op_symbol, rslt, rslt, __binstr(rslt)); 
}

/**
  * @brief  Print binary bitwise operation result.
  * @param[in] arg  Right-hand side argument
  * @param[in] rslt Operation result
  * @param[in] op_name   Operation name (4 character string).
  * @param[in] op_symbol Operation symbol (single character).
  * @retval None 
  */
void print_unary_bitwise_operation(uint32_t arg, uint32_t rslt, char* op_name, char op_symbol)
{
  __binstr_buf(arg, 512);
  __binstr_buf(rslt, 512);

  __print_tab_header(op_name); 
  printf("ARG #1              : 0x%08x | %10u | 0b%32s\n", arg, arg, __binstr(arg));
  printf("%c(ARG #1)           : 0x%08x | %10u | 0b%32s\n\n", op_symbol, rslt, rslt, __binstr(rslt)); 
}

/* Main function -------------------------------------------------------------*/

/**
  * @brief  The application entry point.
  * @retval 0 
  */
int main()
{
  { /* Bitwise AND */
    uint32_t arg1 = 0x12345678;
    uint32_t arg2 = 0x91011121 ;  
    print_binary_bitwise_operation(arg1, arg2, arg1 & arg2, "AND", '&');
  }

  { /* Bitwise OR */
    uint32_t arg1 = 0x31415161;
    uint32_t arg2 = 0x71819202;
    print_binary_bitwise_operation(arg1, arg2, arg1 | arg2, "OR", '|');
  }
   
  { /* Bitwise XOR */
    uint32_t arg1 = 0x12223242;
    uint32_t arg2 = 0x52627282; 
    print_binary_bitwise_operation(arg1, arg2, arg1 ^ arg2, "XOR", '^');
  }
   
  { /* Bitwise NOT */
    uint32_t arg1 = 0x93031323;
    print_unary_bitwise_operation(arg1, ~arg1, "NOT", '~');
  }
}
