/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_customhid.h"
#include "stm32l0xx_it.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

typedef struct{
	uint8_t hat0;
	uint8_t hat1;
	uint8_t hat2;
	uint8_t key3;
	uint8_t but0;
	uint8_t but1;
	uint8_t but2;
	uint8_t but3;
	uint16_t x;
	uint16_t y;
	uint16_t z;
	uint16_t rx;
	uint16_t ry;
}pumaHID;

pumaHID pumahid;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define VREFINT_CAL_ADDR ((uint16_t*)(uint32_t)0x1FFFF7BA)
#define ADC_IRQ ADC1_IRQn
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
extern USBD_CUSTOM_HID_HandleTypeDef hUsbDeviceFS;

unsigned int uiAnalogData[5];

unsigned char i = 0;
char adcUpdated;

unsigned char msg[10];

float Vdd;

GPIO_PinState BP_1;
GPIO_PinState BP_3;
GPIO_PinState hat_switch;

GPIO_PinState hat_north;
GPIO_PinState hat_west;

GPIO_PinState BP_2;
GPIO_PinState BP_4;
GPIO_PinState hat_south;

GPIO_PinState BP_5;
GPIO_PinState BP_6;

GPIO_PinState BP_7;
GPIO_PinState BP_8;

GPIO_PinState BP_11;
GPIO_PinState BP_20;

GPIO_PinState BP_21;
GPIO_PinState BP_30;

GPIO_PinState CH;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void ADC_Select_CH(char choix);


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/*void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* cat){

	 if((ADC1->ISR & ADC_ISR_OVR)== 1)
	    printf("OVR ERR");

	 uiAnalogData[i]= HAL_ADC_GetValue(&hadc);
	i++;

	if (i == 5){//when #conversion > 1000 reset count. This will cause overwrite of SRAM storage locations
		HAL_ADC_Stop_IT (&hadc);
		i=0;
	}

	if( i%2==0 )  //every two conversion restart ADC w/interrupts
		HAL_ADC_Start_IT(&hadc);   //start adc conversion and use interrupts when EOC occurs

}*/

/*
void ADC_IRQHandler()
{
    HAL_ADC_IRQHandler(&hadc);
}*/
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */



	pumahid.hat0 = 0x00;
	pumahid.hat1 = 0x00;
	pumahid.hat2 = 0x00;
	pumahid.key3 = 0x00;
	pumahid.but0 = 0x00;
	pumahid.but1 = 0x00;
	pumahid.but2 = 0x00;
	pumahid.but3 = 0x00;
	pumahid.x = 0x0000;
	pumahid.y = 0x0000;
	pumahid.z = 0x0000;
	pumahid.rx = 0x0000;
	pumahid.ry = 0x0000;

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
  MX_ADC_Init();
  MX_USART2_UART_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */

  //HAL_ADC_Start_IT(&hadc);
  //HAL_NVIC_EnableIRQ(ADC_IRQ);
  //HAL_NVIC_SetPriority(ADC_IRQ, 0, 0);
  //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, PinState)
  //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  CH = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8);
	  BP_5 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13);
	  BP_6 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);

	  HAL_ADC_Start(&hadc);
	  HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);
	  uiAnalogData[0] = HAL_ADC_GetValue(&hadc);
	  HAL_ADC_Stop(&hadc);

	  /*if (uiAnalogData[0] <= 30)
		  uiAnalogData[0] = 0;

	  uiAnalogData[0] = (uiAnalogData[0]*256)/4096;*/

	  if (BP_5 == 0 /*&& CH == 1*/) pumahid.hat0 = 0x01;
	  else pumahid.hat0 = 0x00;
	  if (BP_6 == 0) pumahid.hat1 = 0x02;
	  else pumahid.hat1 = 0x00;

	  pumahid.x = 255;

	  USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &pumahid, sizeof(pumahid));



	  /*if (adcUpdated)
	  {
		  adcUpdated = 0;
	  }*/



	  //HAL_Delay(100);
	  //USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &pumahid, sizeof(pumahid));
	  //HAL_Delay(10);//

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  //HAL_Delay(100);
	  //HAL_ADC_ConvCpltCallBack(&hadc);
	  //sprintf(msg, "resultat_0 %hu \n", uiAnalogData[0]);

	  //HAL_UART_Transmit(&huart2, &msg, strlen(msg), HAL_MAX_DELAY);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_3;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_USB;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC_Init(void)
{

  /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc.Instance = ADC1;
  hadc.Init.OversamplingMode = DISABLE;
  hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerFrequencyMode = ENABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_1;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_4;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_6;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA7 PA8 PA9 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB10
                           PB11 PB13 PB14 PB15
                           PB3 PB4 PB5 PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : CH_Pin */
  GPIO_InitStruct.Pin = CH_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(CH_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : EN_Pin */
  GPIO_InitStruct.Pin = EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(EN_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void ADC_Select_CH(char choix)
{
	ADC_ChannelConfTypeDef sConfig = {0};

	switch(choix)
	{
	case(0):
			sConfig.Channel = ADC_CHANNEL_0;
			sConfig.Rank = 1;
			break;

	case(1):
			sConfig.Channel = ADC_CHANNEL_1;
			sConfig.Rank = 1;
			break;

	case(4):
			sConfig.Channel = ADC_CHANNEL_4;
			sConfig.Rank = 1;
			break;

	case(5):
			sConfig.Channel = ADC_CHANNEL_5;
			sConfig.Rank = 1;
			break;

	case(6):
			sConfig.Channel = ADC_CHANNEL_6;
			sConfig.Rank = 1;
			break;
	}


	if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

