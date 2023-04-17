/**
  ******************************************************************************
  * @file    moore_machine_test.c
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    21-Apr-2021
  * @brief   Moore machine C implementation example
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

/* Typedef -------------------------------------------------------------------*/
typedef enum { a, b, c, d } INPUT;                      //! Input symbols type
typedef enum { alpha = 1, beta = 2, gamma = 4 } OUTPUT; //! Output symbols type
typedef enum { A, B, C} STATE;                          //! State symbol type

/* Function prototypes -------------------------------------------------------*/

/**
 * @brief State machine state transition function: next state truth table
 * @param[in] i - an input symbol
 * @param[in] s - a current state symbol
 * @return Next state symbol
 */
STATE STATE_MACHINE_StateTransition(INPUT i, STATE s);

/**
 * @brief State machine output function: output truth table
 * @param[in] s - a current state symbol
 * @return Current output symbol
 */
OUTPUT STATE_MACHINE_GetOutput(STATE s);

/**
 * @brief Prints table row with names of input, output and state
 * @param[in] i - Input symbol 
 * @param[in] o - Output symbol 
 * @param[in] s - State symbol 
 */
void print_state_machine(INPUT i, OUTPUT o, STATE s);

/* Entry point: main function ------------------------------------------------*/
int main(void)
{
  STATE state = A; // Initial state
  INPUT input[] = { a, d, b, a, c, b, b, c, c, b, d, c, a, d };
  
  // Logging table header
  printf(" # | I |   O   | S | \n");
  printf("-------------------- \n");
  
  int i;
  for(i = 0; i < 14; i++)
  {
    print_state_machine(input[i], STATE_MACHINE_GetOutput(state), state);
    state = STATE_MACHINE_StateTransition(input[i], state);
  }
  print_state_machine(input[i-1], STATE_MACHINE_GetOutput(state), state);
  
  return 0;
}

/* Function implementations ---------------------------------------------------*/

STATE STATE_MACHINE_StateTransition(INPUT i, STATE s)
{
  STATE lookUpTable[][4] = {
    /*         a  b  c  d  */
    /* A: */ { A, B, C, A },
    /* B: */ { B, A, C, A },
    /* B: */ { C, B, A, A }      
  };
  
  return lookUpTable[s][i];
}

OUTPUT STATE_MACHINE_GetOutput(STATE s)
{
  OUTPUT lookUpTable[] = { 
    /* A: */ alpha, 
    /* B: */ beta, 
    /* C: */ gamma 
  };
  
  return lookUpTable[s];
}

void print_state_machine(INPUT i, OUTPUT o, STATE s)
{
                                      
  static const char* _input_names[] = {
  /* 00   01   10   11 */
    "a", "b", "c", "d"
  };
  
  static const char* _output_names[] = {
  /*  000      001      010      011      100   */
    "     ", "alpha", "beta ", "     ", "gamma"
  };
  
  static const char* _state_names[] = {
  /* 00   01   10 */ 
    "A", "B", "C"
  };
  
  static int cnt = 0;
  
  printf("%2d | %s | %s | %s | \n", ++cnt, 
    _input_names[i], _output_names[o], _state_names[s]);
}