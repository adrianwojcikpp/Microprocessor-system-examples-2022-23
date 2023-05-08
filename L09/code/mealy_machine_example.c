/**
  ******************************************************************************
  * @file    mealy_machine_example.c
  * @author  AW		adrian.wojcik@put.poznan.pl
  * @version 3.0
  * @date    09-May-2022
  * @brief   Mealy machine C implementation example (with structure)
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

/* Typedef -------------------------------------------------------------------*/

typedef enum { a, b, c, d } INPUT;                      //! Input symbols type
typedef enum { alpha = 1, beta = 2, gamma = 4, delta = 8 } OUTPUT;           //! Output symbols type
typedef enum { A, B, C} STATE;                          //! State symbol type

typedef struct __STATE_MACHINE__ STATE_MACHINE;

typedef void (*STATE_TRANSITION)(STATE_MACHINE*);
typedef OUTPUT (*GET_OUTPUT)(STATE_MACHINE*);

struct __STATE_MACHINE__ {
  INPUT input;
  OUTPUT output;
  STATE state;
  STATE_TRANSITION state_transition;
  GET_OUTPUT get_output;
};

/* Function prototypes -------------------------------------------------------*/

/**
 * @brief State machine state transition function: next state truth table
 * @param[in] sm - pointer to state machine structure
 */
void STATE_MACHINE_StateTransition(STATE_MACHINE* sm);

/**
 * @brief State machine output function: output truth table
 * @param[in] sm - pointer to state machine structure
 * @return Current output symbol
 */
OUTPUT STATE_MACHINE_GetOutput(STATE_MACHINE* sm);

/**
 * @brief Prints table row with names of input, output and state
 * @param[in] sm - pointer to state machine structure
 */
void print_state_machine(STATE_MACHINE* sm);

/* Main function -------------------------------------------------------------*/

/**
  * @brief  The application entry point.
  * @retval 0 
  */
int main(void)
{
  INPUT input[] = { a, d, b, a, c, b, b, c, c, b, d, c, a, d };
  
  STATE_MACHINE sm = { 
    .state = A,
    .input = input[0],
    .state_transition = STATE_MACHINE_StateTransition,
    .get_output =  STATE_MACHINE_GetOutput
  };
  
  // Logging table header
  printf(" # | I |   O   | S | \n");
  printf("-------------------- \n");
  
  int i;
  for(i = 0; i < (sizeof(input)/sizeof(INPUT)); i++)
  {
    sm.input = input[i];
    print_state_machine(&sm);
    sm.state_transition(&sm);
  }
  print_state_machine(&sm);
  
  return 0;
}

/* Function implementations ---------------------------------------------------*/

void STATE_MACHINE_StateTransition(STATE_MACHINE* sm)
{
  INPUT i = sm->input;
  STATE s = sm->state;	
  
  static const STATE lookUpTable[][4] = {
    /*         a  b  c  d  */
    /* A: */ { A, B, C, A },
    /* B: */ { B, A, C, A },
    /* C: */ { C, B, A, A }      
  };
  
  sm->state = lookUpTable[s][i];
}

OUTPUT STATE_MACHINE_GetOutput(STATE_MACHINE* sm)
{
  INPUT i = sm->input;
  STATE s = sm->state;	
	
  static const OUTPUT lookUpTable[][4] = {
    /*           a      b      c      d  */
    /* A: */ { alpha,  beta, gamma, delta },
    /* B: */ {  beta,  beta, gamma, delta },
    /* C: */ { gamma,  beta, gamma, delta }      
  };
  
  return lookUpTable[s][i];
}

void print_state_machine(STATE_MACHINE* sm)
{
                                      
  static const char* _input_names[] = {
  /* 00   01   10   11 */
    "a", "b", "c", "d"
  };
  
  static const char* _output_names[] = {
  /* 0000     0001     0010     0011     0100     0101     0110     0111     1000  */
    "     ", "alpha", "beta ", "     ", "gamma", "     ", "     ", "     ", "delta"
  };
  
  static const char* _state_names[] = {
  /* 00   01   10 */ 
    "A", "B", "C"
  };
  
  static int cnt = 0;
  
  INPUT i = sm->input;
  OUTPUT o = sm->get_output(sm);
  STATE s = sm->state;
  
  printf("%2d | %s | %s | %s | \n", ++cnt, 
    _input_names[i], _output_names[o], _state_names[s]);
}