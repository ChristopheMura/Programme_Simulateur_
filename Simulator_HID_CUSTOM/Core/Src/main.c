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
//#include "stm32l0xx_it.h"
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
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
extern USBD_CUSTOM_HID_HandleTypeDef hUsbDeviceFS;
//extern USBD_CUSTOM_HID_ItfTypeDef hUsbDeviceFS;

GPIO_PinState BP_1;
GPIO_PinState BP_3;
GPIO_PinState hat_east;

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
void envoi(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

	uint32_t ADC_VAL[5];
	char msg[80];

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
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
  HAL_ADCEx_Calibration_Start(&hadc, ADC_SINGLE_ENDED);		// Calibration de l'ADC
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  CH = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8);				// Entrée CH pour le débouncer

	  /******************** LECTURE DES BOUTONS POUSSOIRS ********************/

	  /************ BOUTON SUR MANCHE ************/

	  BP_1 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6);			// Lecture bouton 1
	  BP_3 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5);			// Lecture bouton 3
	  hat_east = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4);		// Lecture chapeau est

	  hat_north = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3);		// Lecture chapeau nord
	  hat_west = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15);		// Lecture chapeau ouest

	  BP_2 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9);			// Lecture bouton 2
	  BP_4 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8);			// Lecture bouton 4
	  hat_south = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15);		// Lecture chapeau sud

	  /************ BOUTON SUR CONLLECTIVE ************/

	  BP_5 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13);			// Lecture bouton 5 rouge
	  BP_6 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);			// Lecture bouton 6 rouge

	  BP_7 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11);			// Lecture switch rouge position haut
	  BP_8 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10);			// Lecture switch rouge position bas

	  BP_20 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2);			// Lecture swtich noir config 1 position haut
	  BP_11 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);			// Lecture switch noir config 1 position bas
	  BP_21 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);			// Lecture switch noir config 2 position haut
	  BP_30 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7);			// Lecture switch noir config 2 position bas

	  /******************** CONVERSION DES DONNEES ANALOGIQUE ********************/

	  HAL_ADC_Start(&hadc);								// Scan des entrées ADC
	  ADC_VAL[0] = HAL_ADC_GetValue(&hadc);					// ADC channel 0
	  ADC_VAL[1] = HAL_ADC_GetValue(&hadc);					// ADC channel 1
	  ADC_VAL[2] = HAL_ADC_GetValue(&hadc);					// ADC channel 4
	  ADC_VAL[3] = HAL_ADC_GetValue(&hadc);					// ADC channel 5
	  ADC_VAL[4] = HAL_ADC_GetValue(&hadc);					// ADC channel 6
	  HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);		// Fin de conversion
	  HAL_ADC_Stop(&hadc);									// Stop la conversion

	  if (hat_north == 0) pumahid.hat0 = 0x00;				// Appuie sur chapeau nord
	  else if (hat_west == 0) pumahid.hat0 = 0x06;			// Appuie sur chapeau ouest
	  else if (hat_east == 0) pumahid.hat0 = 0x02;			// Appuie sur chapeau est
	  else if (hat_south == 0) pumahid.hat0 = 0x04;			// Appuie sur chapeau sud
	  else pumahid.hat0 = 0x07;

	  if (BP_1 == 0) pumahid.but0 = 0x01;					// Appuie sur bouton 1
	  else if (BP_3 == 0) pumahid.but0 = 0x02;				// Appuie sur bouton 3
	  else if (BP_2 == 0) pumahid.but0 = 0x04;				// Appuie sur bouton 2
	  else if (BP_4 == 0) pumahid.but0 = 0X08;				// Appuie sur bouton 4
	  else pumahid.but0 = 0x10;

	  if (BP_5 == 0) pumahid.but1 = 0x01;					// Appuie sur bouton 5
	  else if (BP_6 == 0) pumahid.but1 = 0x02;				// Appuie sur bouton 6
	  else pumahid.but1 = 0x04;

	  /******************** Gestion des communitateurs ********************/
	  if (BP_7 == 0)
	  {
		  if (BP_11 == 0) pumahid.but2 = 0x01;
		  if (BP_20 == 0) pumahid.but2 = 0x02;
	  }


	  ADC_VAL[0] -= 1725;											// AXE X
	  if (ADC_VAL[0] < 0 | ADC_VAL[0] > 60000) ADC_VAL[0] = 0;
	  ADC_VAL[0] = (ADC_VAL[0]*255)/511;
	  if (ADC_VAL[0] > 255 & ADC_VAL[0] < 50000) ADC_VAL[0] = 255;

	  ADC_VAL[1] -= 1766;											// AXE Y
	  if (ADC_VAL[1] < 0 | ADC_VAL[1] > 60000) ADC_VAL[1] = 0;
	  ADC_VAL[1] = (ADC_VAL[1]*255)/490;
	  if (ADC_VAL[1] > 255 & ADC_VAL[1] < 50000) ADC_VAL[1] = 255;

	  ADC_VAL[2] -= 1850;											// COLLECTIVE AXE Z
	  if (ADC_VAL[2] < 0 | ADC_VAL[2] > 60000) ADC_VAL[2] = 0;
	  ADC_VAL[2] = (ADC_VAL[2]*255)/700;
	  if (ADC_VAL[2] > 255 & ADC_VAL[2] < 50000) ADC_VAL[2] = 255;

	  ADC_VAL[3] -= 3912;											// PEDAL X ROTATION
	  if (ADC_VAL[3] < 0 | ADC_VAL[3] > 60000) ADC_VAL[3] = 0;
	  ADC_VAL[3] = (ADC_VAL[3]*255)/38;
	  if (ADC_VAL[3] > 255 & ADC_VAL[3] < 50000) ADC_VAL[3] = 255;

	  ADC_VAL[4] -= 2264;											// COLLECTIVE Y ROTATION
	  if (ADC_VAL[4] < 0 | ADC_VAL[4] > 60000) ADC_VAL[4] = 0;
	  ADC_VAL[4] = (ADC_VAL[4]*255)/104;
	  if (ADC_VAL[4] > 255 & ADC_VAL[4] < 50000) ADC_VAL[4] = 255;

	  /*********** Attribution des valeurs analogiques aux différents axes ***********/

	  pumahid.x = ADC_VAL[0];
	  pumahid.y = ADC_VAL[1];
	  pumahid.z = ADC_VAL[2];
	  pumahid.rx = ADC_VAL[3];
	  pumahid.ry = ADC_VAL[4];

	  /*********** Envoie des valeurs par USB ***********/
	  USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, &pumahid, sizeof(pumahid));

	  HAL_Delay(10);

	  /*********** Envoie des valeurs en UART ***********/
	  //sprintf(msg, " PEDAL X = %hu | COLLECTIVE = %hu\n", /*ADC_VAL[0], ADC_VAL[1], ADC_VAL[2], */ADC_VAL[3], ADC_VAL[4]);
	  //HAL_UART_Transmit(&huart2, &msg, strlen(msg), HAL_MAX_DELAY);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_USB;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
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
  hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ContinuousConvMode = ENABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerFrequencyMode = DISABLE;
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
  HAL_GPIO_WritePin(LED_V_GPIO_Port, LED_V_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : BP30_Pin BP4_Pin HAT_WEST_Pin */
  GPIO_InitStruct.Pin = BP30_Pin|BP4_Pin|HAT_WEST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : BP21_Pin BP11_Pin BP8_Pin BP7_Pin
                           HAT_SOUTH_Pin HAT_NORTH_Pin HAT_EAST_Pin BP3_Pin
                           BP1_Pin */
  GPIO_InitStruct.Pin = BP21_Pin|BP11_Pin|BP8_Pin|BP7_Pin
                          |HAT_SOUTH_Pin|HAT_NORTH_Pin|HAT_EAST_Pin|BP3_Pin
                          |BP1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : BP20_Pin BP5_Pin BP6_Pin CH_Pin */
  GPIO_InitStruct.Pin = BP20_Pin|BP5_Pin|BP6_Pin|CH_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : BP2_Pin */
  GPIO_InitStruct.Pin = BP2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BP2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_V_Pin */
  GPIO_InitStruct.Pin = LED_V_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_V_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : EN_Pin */
  GPIO_InitStruct.Pin = EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(EN_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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

