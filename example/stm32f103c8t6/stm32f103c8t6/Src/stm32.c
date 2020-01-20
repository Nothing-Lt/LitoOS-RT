
#include "../Inc/stm32.h"

#include "../LitoOS/include/task.h"

I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart1;

extern LT_list_t* ready_queue;
extern LT_list_item_t* tcb_item_running_task;
TCB_t* tcb_save;
TCB_t* tcb_load;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);

void hardware_init()
{
  LT_IRQ_disable();

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_USART1_UART_Init();
}

uint32_t hardware_tick_get()
{
	return HAL_GetTick();
}

void lr_temp()
{
	while(1){

	}
}

void hardware_context_switch()
{
	*((uint32_t*)0xE000ED04) = 0x10000000;
}

void hardware_TCB_init(TCB_t* tcb,function* func,void* parameter,void* stack_pointer,size_t stack_size)
{
	CONTENT_t* tcb_in_stack = NULL;

	if((NULL == tcb) || (NULL == func) || (NULL == stack_pointer)){
		return;
	}

	tcb_in_stack = tcb->stack_pointer = (CONTENT_t*)(((uint32_t)stack_pointer) + stack_size - sizeof(TCB_t) - sizeof(CONTENT_t));

	// in the future, this can be the return address.
	tcb_in_stack->lr = (uint32_t)lr_temp;
	tcb_in_stack->pc = ((uint32_t)func) & 0xfffffffe;

	// in the future, this can be the parameter.
	tcb_in_stack->r0 = (uint32_t)parameter;

	tcb_in_stack->r1  = tcb_in_stack->r2  = tcb_in_stack->r3  = \
	tcb_in_stack->r4  = tcb_in_stack->r5  = tcb_in_stack->r6  = \
	tcb_in_stack->r7  = tcb_in_stack->r8  = tcb_in_stack->r9  = \
	tcb_in_stack->r10 = tcb_in_stack->r11 = tcb_in_stack->r12 = 0;

	tcb_in_stack->xPSR = 0x1000000;
}

void LT_IRQ_enable()
{
	__asm volatile
	(
		"	mov r0, #0		\n" \
		"	msr basepri, r0	\n" \
		"	isb				\n" \
		"	dsb				\n" \
	);

}

void LT_IRQ_disable()
{
	__asm volatile
	(
		"	mov r0, #80		\n" \
		"	msr basepri, r0	\n" \
		"	isb				\n" \
		"	dsb				\n" \
	);
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
 * This is the dummy task in LitoOS-RT,
 * it should be the very first task in this OS.
 */
void LT_dummy_task(const void* arg)
{
	while(1){
		HAL_Delay(500);
	}
}

/*The function to start the first task(dummy task)*/
void LT_first_task_start()
{
	tcb_load = &(((Lito_TCB_t*)(tcb_item_running_task->content))->tcb);

	__asm volatile(
			" ldr r0, =0xE000ED08 	\n" /* Use the NVIC offset register to locate the stack. */
			" ldr r0, [r0] 			\n"
			" ldr r0, [r0] 			\n"
			" msr msp, r0			\n" /* Set the msp back to the start of the stack. */
			" cpsie i				\n" /* Globally enable interrupts. */
			" cpsie f				\n"
			" dsb					\n"
			" isb					\n"
			" svc 0					\n" /* System call to start first task. */
			" nop					\n"
	);
}



/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
