/**
  ******************************************************************************
  * @file    serial_port_demo.c.c
  * @author  AW		adrian.wojcik@put.poznan.pl
  * @version 3.0
  * @date    22-May-2022
  * @brief   Serial port demo app in C
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

#include "serial_port_lib.h"

/* Main function -------------------------------------------------------------*/

/**
  * @brief  The application entry point.
  * @retval 0 
  */
int main(void)
{
  SERIAL_PORT_Handle handle;
  int status;
  
  status = SERIAL_PORT_Init(&handle);
  
  printf("Initialization status: %s \n", (status == 0) ? "OK" : "ERROR");
  
  status = SERIAL_PORT_WriteString(handle, "Hello, World!\r\n");
  
  printf("Writing status: %s \n\n", (status == 0) ? "OK" : "ERROR");
  
  char msg[20] = { 0 }; // MAX MESSAGE SIZE: 17 CHARACTERS!
  
  while(1) // ECHO LOOP
  {
  
    status = SERIAL_PORT_ReadLine(handle, msg);
  
    printf("Reading status: %s \n", (status == 0) ? "OK" : "ERROR");
    printf("Message: %s", msg);
    printf("Message length: %d\n", (int)strlen(msg));
    
    if(strcmp(msg, "CLOSE\r\n") == 0)
      break;
    
    status = SERIAL_PORT_WriteString(handle, msg);
  
    printf("Writing status: %s \n\n", (status == 0) ? "OK" : "ERROR");
    
    memset(msg, 0, sizeof(msg));
  }
  
  status = SERIAL_PORT_DeInit(handle);
  
  printf("Deinitialization status: %s \n", (status == 0) ? "OK" : "ERROR");
  
  return 0;
}
