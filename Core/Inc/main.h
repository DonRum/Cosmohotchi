/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f4xx_hal.h"

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
#define BUT8_Pin GPIO_PIN_12
#define BUT8_GPIO_Port GPIOF
#define BUT7_Pin GPIO_PIN_13
#define BUT7_GPIO_Port GPIOF
#define BUT4_Pin GPIO_PIN_14
#define BUT4_GPIO_Port GPIOF
#define BUT2_Pin GPIO_PIN_15
#define BUT2_GPIO_Port GPIOF
#define LED7_Pin GPIO_PIN_7
#define LED7_GPIO_Port GPIOE
#define LED8_Pin GPIO_PIN_8
#define LED8_GPIO_Port GPIOE
#define BUT6_Pin GPIO_PIN_9
#define BUT6_GPIO_Port GPIOE
#define LED6_Pin GPIO_PIN_10
#define LED6_GPIO_Port GPIOE
#define BUT5_Pin GPIO_PIN_11
#define BUT5_GPIO_Port GPIOE
#define LED5_Pin GPIO_PIN_12
#define LED5_GPIO_Port GPIOE
#define BUT3_Pin GPIO_PIN_13
#define BUT3_GPIO_Port GPIOE
#define LED4_Pin GPIO_PIN_14
#define LED4_GPIO_Port GPIOE
#define LED3_Pin GPIO_PIN_15
#define LED3_GPIO_Port GPIOE
#define LED2_Pin GPIO_PIN_10
#define LED2_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_11
#define LED1_GPIO_Port GPIOB
#define BUT9_Pin GPIO_PIN_15
#define BUT9_GPIO_Port GPIOD
#define LED9_Pin GPIO_PIN_9
#define LED9_GPIO_Port GPIOG
#define BUT1_Pin GPIO_PIN_14
#define BUT1_GPIO_Port GPIOG
#define LED10_Pin GPIO_PIN_0
#define LED10_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
