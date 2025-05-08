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
#include <math.h>  

/// @brief Naming convention: binary string buffer name postfix
#define __binstr(name) name##_binstr

/// @brief Defines buffer of <size> for <name> variable
#define __binstr_buf(name, size) \
  char __binstr(name)[size] = {0,};\
  uint32_to_binstr(name, __binstr(name))

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
 * @param mem : Input memory address
 */
void print_mem(mem_t* mem)
{
  mem_t variable = *mem;
  printf("Memory content [dec]: %10u \n", variable);
  printf("Memory content [hex]: 0x%08X \n", variable);
  __binstr_buf(variable, 512);
  printf("Memory content [bin]: 0b%s", variable_binstr);
}
/* END RAW MEMORY ---------------------------------------------- */

/* BEGIN INTEGER ----------------------------------------------- */
/**
 * @brief Printing integer variable or literal 
 *        as a numeric value and memory content.
 * @param number_text : Input integer number as text
 * @param number : Input integer number as 'int32_t'
 */
void print_int32(const char* number_text, int32_t number)
{
  printf("Integer variable / literal: %s \n", number_text);
  printf("Value [dec]: %d \n", number);
  print_mem( (mem_t*)&number ); /* Casting 'number' address to  
                                   'mem_t' pointer             */
}
/* END INTEGER ------------------------------------------------- */

/* BEGIN FIXED-POINT ------------------------------------------- */
/**
 * @brief Printing fixed-point variable or literal 
 *        from <-1.0, 1.0) range as a numeric value and memory content.
 * @param number_text : Input fixed-point fractional number as text
 * @param number : Input fixed-point fractional number as 'q31_t'
 */
void print_q31(const char* number_text, q31_t number)
{
  printf("Fixed-point variable / literal: %s \n", number_text);
  printf("Value [dec]: %0.15f \n", Q31_TO_DOUBLE(number));
  print_mem( (mem_t*)&number ); /* Casting 'number' address to  
                                   'mem_t' pointer             */
}
/* END FIXED-POINT --------------------------------------------- */

/* BEGIN FLOATING-POINT -----------------------------------------*/


/**
 * @brief Estimate the number of decimal digits needed to represent a float 
 *        with reasonable precision based on its magnitude.
 *
 * This function approximates how many digits after the decimal point are 
 * needed to preserve the significant digits of a 32-bit IEEE 754 float.
 * It assumes approximately 7 significant decimal digits of precision.
 *
 * @param value The float value to analyze.
 * @return The estimated number of decimal digits needed after the
 *         decimal point to preserve precision in formatted output.
 */
unsigned int float32_digits(float value) 
{
    const unsigned int min_digits = 15;
    
    if (value == 0.0f) 
        return min_digits; 
        
    float abs_val = fabsf(value);
    int magnitude = (int)floorf(log10f(abs_val));
    int digits_after_decimal = 7 - magnitude - 1;
    
    if (digits_after_decimal < min_digits) 
        digits_after_decimal = min_digits;
        
    return digits_after_decimal;
}

/**
 * @brief Printing single-precision floating point variable or literal 
 *        as a numeric value and memory content.
 * @param number_text : Input floating-point fractional number as text
 * @param number : Input floating-point fractional number as 'float'
 */
void print_float(const char* number_text, float number)
{
  printf("Floating-point variable / literal: %s \n", number_text);
  printf("Value [dec]: %0.*f \n", float32_digits(number), number);
  print_mem( (mem_t*)&number ); /* Casting 'number' address to  
                                   'mem_t' pointer             */
}
/* END FLOATING-POINT -------------------------------------------*/