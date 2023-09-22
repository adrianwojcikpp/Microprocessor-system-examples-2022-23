/**
  ******************************************************************************
  * @file    L02_example.c
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 2.0
  * @date    08-Mar-2022
  * @brief   Intruction #02 tasks solution template
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Define --------------------------------------------------------------------*/
#define T '1' /**< True symbol (T / H / 1) */
#define F '0' /**< False symbol (F / L / 0) */

#define NOT   '~' /**< Logisim negation symbol */
#define BLANK ' '

#define PROD '*' /**< Logisim Evolution product symbol */
//#define PROD ' ' /**< Logisim product symbol */

/* Macro ---------------------------------------------------------------------*/

/* Typedef -------------------------------------------------------------------*/

/* Global variables ----------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/

/* Function definitions ------------------------------------------------------*/

/**
 * @brief Logic function truth table printing procedure
 * @param[in] fcn  : Logic function 
 * @param[in] bits : Input size (number of bits)
 * @param[in] n    : Number of integer inputs 
 * @return None
 */ 
void print_truth_table(_Bool fcn(unsigned int), unsigned int bits, unsigned int n)
{
  // print table header
  for(int s = 1; s < n; s++)
    printf("   ");
  printf("     |");
  for(int j = 0; j < bits; j++)
    printf(" %c |", (char)j + 'a');
  printf(" %s |\n", "fcn");
    
  unsigned int bits_per_number = bits / n;
  unsigned int upper_limit = pow(2, bits_per_number);
  
  // print table body
  for(unsigned int i = 0; i < (1 << bits); i++)
  {
    printf("[");
    // print row number(s)
    for(int k = n-1; k > 0; k--)
      printf("%2d,", (i >> k*bits_per_number) % upper_limit);
    printf("%2d] |", i % upper_limit);
    // print logic function values
    for(int j = bits-1; j >= 0; j--)
      printf(" %c |", (i & (1 << j)) ? T : F);
    printf("  %c  |\n", fcn(i) ? T : F);
  }
}

/**
 * @brief Saves C-string to text file.
 * @param[in] filename : File name 
 * @param[in] buffer   : Input C-string to be saved in text file
 * @return None
 */
void save_buffer_to_file(char* filename, char* buffer)
{
  FILE *hFile;
  hFile = fopen(filename,"w");
  if(hFile == NULL)
  {
    printf("Cannot open '%s' file for writing.", filename);
    return;
  }
  fprintf(hFile,"%s", buffer);
  fclose(hFile);
}

/**
 * @brief Sum Of Product (SOP) formula printing procedure
 * @param[in] fcn      : Logic function 
 * @param[in] bits     : Input size (number of bits)
 * @param[in] filename : Result file name
 * @return None
 */
void print_and_save_sop(_Bool fcn(unsigned int), unsigned int bits, char* filename)
{
  char buffer[4096] = { '\0', };
  int len = 0;
  _Bool is_firt = 1;
  for(unsigned int  i = 0; i < (1 << bits); i++)
  {
    if(fcn(i) == 1)
    {
      len += sprintf(buffer+len, "%c(", is_firt ? ' ' : '+');
      is_firt = 0;
      int j;
      for(j = bits-1; j > 0; j--)
        len += sprintf(buffer+len, "%c%c%c", (i & (1 << j)) ? BLANK : NOT, (char)(bits - (j+1)) + 'a', PROD);
      len += sprintf(buffer+len, "%c%c)\n",  (i & (1 << j)) ? BLANK : NOT, (char)(bits - (j+1)) + 'a');
    }
  }
  printf("%s", buffer);
  save_buffer_to_file(filename, buffer);
}

/**
 * @brief Product Of Sum (POS) formula printing procedure
 * @param[in] fcn      : Logic function 
 * @param[in] bits     : Input size (number of bits)
 * @param[in] filename : Result file name
 * @return None
 */
void print_and_save_pos(_Bool fcn(unsigned int), unsigned int bits, char* filename)
{
  char buffer[4096] = { '\0', };
  int len = 0;
  _Bool is_firt = 1;
  for(unsigned int i = 0; i < (1 << bits); i++)
  {
    if(fcn(i) == 0)
    {
      len += sprintf(buffer+len, "%c(", is_firt ? ' ' : PROD);
      is_firt = 0;
      int j;
      for(j = bits-1; j > 0; j--)
        len += sprintf(buffer+len, "%c%c + ", (i & (1 << j)) ? NOT : BLANK, (char)(bits - (j+1)) + 'a');
      len += sprintf(buffer+len, "%c%c)\n",   (i & (1 << j)) ? NOT : BLANK, (char)(bits - (j+1)) + 'a');
    }
  }
  printf("%s", buffer);
  save_buffer_to_file(filename, buffer);
}

/**
 * @brief 2-bit number comparator
 * @param[in] x two 2-bit integer input (bits AB and CD)
 * @return 1 if ...; 0 otherwise
 */
_Bool two_bit_comparator(unsigned int x) 
{
  unsigned int AB = (x / 4) % 4;
  unsigned int CD = (x / 1) % 4;
  // USER CODE BEGIN
  return 0;
  // USER CODE END
}

/**
 * @brief Logic function checking whether 
 *        LED line input is valid
 * @details LED line structure:
 * 
 *          [    ] A (MSB)
 *          [    ] B 
 *          [    ] C 
 *          [    ] D
 *          [    ] E (LSB)
 *
 *          Valid inputs:
 * 
 *          [    ] A    [    ] A    [    ] A 
 *          [    ] B    [    ] B    [    ] B
 *          [    ] C    [    ] C    [    ] C
 *          [    ] D    [    ] D    [####] D
 *          [    ] E    [####] E    [####] E 
 *
 *          [    ] A    [    ] A    [####] A 
 *          [    ] B    [####] B    [####] B
 *          [####] C    [####] C    [####] C
 *          [####] D    [####] D    [####] D
 *          [####] E    [####] E    [####] E 
 *
 * @param[in] x 5-bit integer input (bits ABDCE)
 * @return 1 if input is valid; 0 otherwise
 */
_Bool is_led_line_input_valid(unsigned int x) 
{
  unsigned int A = (x / 16) % 2;
  unsigned int B = (x / 8) % 2;
  unsigned int C = (x / 4) % 2;
  unsigned int D = (x / 2) % 2;
  unsigned int E = (x / 1) % 2;
  // USER CODE BEGIN
  return 0;
  // USER CODE END
}

/**
 * @brief Logic function checking whether 
          number is divisible by 3
 * @param[in] x Integer input 
 * @return 1 if is divisible by 3; 0 otherwise
 */
_Bool is_divisible_by_3(unsigned int x) 
{
  // USER CODE BEGIN
  return 0;
  // USER CODE END
}

/* Main function -------------------------------------------------------------*/

/**
  * @brief  The application entry point.
  * @retval 0 
  */
int main(void)
{
  int number_of_bits[] = { 5 /* TASK 1*/, 5 /* TASK 2*/, 4 /* TASK 3*/ };
  int number_of_inputs[] = { 1/* TASK 1*/, 1 /* TASK 2*/, 2 /* TASK 3*/ };
  _Bool (*fcn[])(unsigned int) = { 
    &is_divisible_by_3,       /* TASK 1*/
    &is_led_line_input_valid, /* TASK 2*/
    &two_bit_comparator       /* TASK 3*/
  };
  
  for(int i = 0; i < sizeof(fcn)/sizeof(fcn[0]); i++)
  {
    printf("\n\nTASK #%i ------------------------------------------------------------\n", (i+1));
    
    puts("Truth table: ");
    print_truth_table(fcn[i], number_of_bits[i], number_of_inputs[i]); 
    
    puts("\nSum of product:");
	char filename[128];
	snprintf(filename, sizeof(filename), "sop_task_%d.txt", i+1);
    print_and_save_sop(fcn[i], number_of_bits[i], filename);
    
    puts("\nProduct of sum:");
	snprintf(filename, sizeof(filename), "pos_task_%d.txt", i+1);
    print_and_save_pos(fcn[i], number_of_bits[i], filename);
  }

  return 0;
}

/* Function definitions ------------------------------------------------------*/
