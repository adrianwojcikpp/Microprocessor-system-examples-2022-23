/**
  ******************************************************************************
  * @file    print_mem.c
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 2.0
  * @date    14-Mar-2022
  * @brief   Printing memory content
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "print_mem.h"
#include <string.h>

/// @brief Naming convention: binary string buffer name postfix
#define __binstr(name) name##_binstr

/// @brief Defines buffer of <size> for <name> variable
#define __binstr_buf(name, size) \
  char __binstr(name)[size] = {0,};\
  uint32_to_binstr(name, __binstr(name))

/// @brief Common numbers printing routine
#define __PRINT_NUMBER(L, F) \
    printf(L " variable / literal: %s \n", number_text); \
    printf("Value [dec]: " F "\n", number); \
    print_mem( (mem_t*)&number, sizeof(number) )

/**
 * @brief Unsigned integer (8 bits) to C-string.
 * @param[in]  num    Input unsigned 32 bits integer.
 * @param[out] binstr Output binary string with leading zeros.
 *                    Have to be at least 320 byte buffer. 
 * @retval None.
 */
void uint32_to_binstr(mem_t num, char* binstr)
{
  for(int i = 0; i < 8*sizeof(num); i++)
  {
    #if COLORED_CONSOLE 
    memcpy(&binstr[i*10], ((1u << (8*sizeof(num) - 1 - i)) & num) ? "\033[31m1\033[0m" : "\033[32m0\033[0m", 10);
    #else
    binstr[i] = ((1u << (8*sizeof(num) - 1 - i)) & num)  ? '1' : '0';
    #endif
  }
}

/* BEGIN RAW MEMORY -------------------------------------------- */
/**
 * @brief Printing content of 32-bit memory location
 *        as unsigned integer in decimal, hexadecimal and binary.
 * @param[in] mem     : Input memory address
 * @param[in] mem_len : Input memory sector length
 */
void print_mem(mem_t* mem, size_t mem_len)
{
  printf("Memory content [hex]: 0x");
  for(size_t i = 0; i < mem_len; i++)
    printf("%02X", mem[mem_len - 1 - i]);
  printf("\nMemory content [bin]: 0b");
  for(size_t i = 0; i < mem_len; i++)
  {
    mem_t var = mem[mem_len - 1 - i];
    __binstr_buf(var, 512);
    printf("%s", var_binstr);
  }
}
/* END RAW MEMORY ---------------------------------------------- */

/* BEGIN INTEGER ----------------------------------------------- */
/**
 * @brief Printing integer variable or literal 
 *        as a numeric value and memory content.
 * @param number_text : Input integer variable name or literal as text
 * @param number : Input integer number
 */
void print_int64(const char* number_text, int64_t number) 
{ 
  __PRINT_NUMBER("Integer (64-bit)", "%lli");
}
void print_int32(const char* number_text, int32_t number) 
{ 
  __PRINT_NUMBER("Integer (32-bit)", "%i");
}
void print_int16(const char* number_text, int16_t number) 
{ 
  __PRINT_NUMBER("Integer (16-bit)", "%hi");
}
void print_int8(const char* number_text, int8_t number) 
{ 
  __PRINT_NUMBER("Integer (8-bit)", "%hhi");
}
/* END INTEGER ------------------------------------------------- */

/* BEGIN FLOATING-POINT -----------------------------------------*/
/**
 * @brief Printing single-precision floating point variable or literal 
 *        as a numeric value and memory content.
 * @param number_text : Input floating-point variable name or literal as text
 * @param number : Input floating-point number 
 */
void print_float(const char* number_text, float number)
{ 
  __PRINT_NUMBER("Single precision floating-point", "%.15f");
}
void print_double(const char* number_text, double number)
{
  __PRINT_NUMBER("Double precision floating-point", "%.15ff"); 
}
void print_long_double(const char* number_text, long double number)
{
  __PRINT_NUMBER("Extended double precision floating-point", "%.15Lf"); 
}
/* END FLOATING-POINT -------------------------------------------*/