/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define AXE_X_Pin GPIO_PIN_0
#define AXE_X_GPIO_Port GPIOA
#define AXE_Y_Pin GPIO_PIN_1
#define AXE_Y_GPIO_Port GPIOA
#define AXE_Z_Pin GPIO_PIN_4
#define AXE_Z_GPIO_Port GPIOA
#define COLLECTIVE_Y_Pin GPIO_PIN_5
#define COLLECTIVE_Y_GPIO_Port GPIOA
#define PEDALE_Pin GPIO_PIN_6
#define PEDALE_GPIO_Port GPIOA
#define BP30_Pin GPIO_PIN_7
#define BP30_GPIO_Port GPIOA
#define BP21_Pin GPIO_PIN_0
#define BP21_GPIO_Port GPIOB
#define BP11_Pin GPIO_PIN_1
#define BP11_GPIO_Port GPIOB
#define BP20_Pin GPIO_PIN_2
#define BP20_GPIO_Port GPIOB
#define BP8_Pin GPIO_PIN_10
#define BP8_GPIO_Port GPIOB
#define BP7_Pin GPIO_PIN_11
#define BP7_GPIO_Port GPIOB
#define BP5_Pin GPIO_PIN_13
#define BP5_GPIO_Port GPIOB
#define BP6_Pin GPIO_PIN_14
#define BP6_GPIO_Port GPIOB
#define HAT_SOUTH_Pin GPIO_PIN_15
#define HAT_SOUTH_GPIO_Port GPIOB
#define BP4_Pin GPIO_PIN_8
#define BP4_GPIO_Port GPIOA
#define BP2_Pin GPIO_PIN_9
#define BP2_GPIO_Port GPIOA
#define LED_V_Pin GPIO_PIN_10
#define LED_V_GPIO_Port GPIOA
#define HAT_WEST_Pin GPIO_PIN_15
#define HAT_WEST_GPIO_Port GPIOA
#define HAT_NORTH_Pin GPIO_PIN_3
#define HAT_NORTH_GPIO_Port GPIOB
#define HAT_EAST_Pin GPIO_PIN_4
#define HAT_EAST_GPIO_Port GPIOB
#define BP3_Pin GPIO_PIN_5
#define BP3_GPIO_Port GPIOB
#define BP1_Pin GPIO_PIN_6
#define BP1_GPIO_Port GPIOB
#define CH_Pin GPIO_PIN_8
#define CH_GPIO_Port GPIOB
#define EN_Pin GPIO_PIN_9
#define EN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
