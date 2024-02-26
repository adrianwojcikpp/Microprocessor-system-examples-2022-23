/**
  ******************************************************************************
  * @file    L01_example.c
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    01-Mar-2022
  * @brief   Instruction #01 tasks solution template
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/
#define T '1' /**< True symbol (T / H / 1) */
#define F '0' /**< False symbol (F / L / 0) */

/* Typedef -------------------------------------------------------------------*/

/* Global variables ----------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/

/* Function definitions ------------------------------------------------------*/

/**
 * @brief Binary boolean operator truth table printing procedure
 * @param[in] op      Binary boolean operator function 
 * @param[in] op_sign Binary boolean operator symbol or designation
 * @return None
 */
//void print_truth_table(logic_operator op, const char* op_sign)
void print_truth_table(_Bool op(_Bool,_Bool), const char* op_sign)
{
  printf("\n| p | q | p%sq |\n------------------\n", op_sign);
  unsigned char i;
  _Bool p,q;
  for(i = 0; i < 4; i++)
  {
    p = i & 2;
    q = i & 1;
    printf("| %c | %c |    %c   |\n", p ? T : F, 
                                     q ? T : F, 
                               op(p,q) ? T : F);
  }
}

/**
 * @brief Binary operator Material nonimplication
 * @param[in] p First boolean input argument
 * @param[in] q Second boolean input argument
 * @return p -/-> q
 */
_Bool my_material_nonimplication(_Bool p, _Bool q)
{
  // USER CODE BEGIN
  return p && !q;
  // USER CODE END
}

/* Main function -------------------------------------------------------------*/

/**
  * @brief  The application entry point.
  * @retval 0 
  */
int main(void)
{
  // call example
  print_truth_table(my_material_nonimplication, "-/->"); 
  
  return 0;
}

/* Function definitions ------------------------------------------------------*/
