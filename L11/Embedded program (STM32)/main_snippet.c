

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "serial_port_lib.h"
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART3_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  SERIAL_PORT_Handle handle;
  int status;

  status = SERIAL_PORT_Init(&handle);

  printf("Initialization status: %s \r\n", (status == 0) ? "OK" : "ERROR");

  status = SERIAL_PORT_WriteString(handle, "Hello, World!\r\n");

  printf("Writing status: %s \r\n", (status == 0) ? "OK" : "ERROR");

  char msg[20] = { 0 }; // MAX MESSAGE SIZE: 17 CHARACTERS!

  while (1)
  {
    status = SERIAL_PORT_ReadLine(handle, msg);

    printf("Reading status: %s \r\n", (status == 0) ? "OK" : "ERROR");
    printf("Message: %s", msg);
    printf("Message length: %d\r\n", (int)strlen(msg));

    //if(strcmp(msg, "CLOSE\r\n") == 0)
    //   break;

    status = SERIAL_PORT_WriteString(handle, msg);

    printf("Writing status: %s \r\n", (status == 0) ? "OK" : "ERROR");

    memset(msg, 0, sizeof(msg));
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}
