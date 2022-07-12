/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
#pragma once
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "state.h"
#include "event.h"
#include "state_Handler.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
void spi_wb(uint8_t b);
uint8_t spi_rb(void);
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
#define WR_IP_Pin GPIO_PIN_0
#define WR_IP_GPIO_Port GPIOA
#define WR_IP_EXTI_IRQn EXTI0_IRQn
#define WL_IP_Pin GPIO_PIN_1
#define WL_IP_GPIO_Port GPIOA
#define WL_IP_EXTI_IRQn EXTI1_IRQn
#define F_IP_Pin GPIO_PIN_5
#define F_IP_GPIO_Port GPIOA
#define F_IP_EXTI_IRQn EXTI9_5_IRQn
#define LAN_CS_Pin GPIO_PIN_0
#define LAN_CS_GPIO_Port GPIOB
#define LAN_INT_Pin GPIO_PIN_2
#define LAN_INT_GPIO_Port GPIOB
#define CA_OP1_Pin GPIO_PIN_8
#define CA_OP1_GPIO_Port GPIOA
#define LA_OP1_Pin GPIO_PIN_9
#define LA_OP1_GPIO_Port GPIOA
#define LAN_RESET_Pin GPIO_PIN_15
#define LAN_RESET_GPIO_Port GPIOA
#define CA_OP_Pin GPIO_PIN_8
#define CA_OP_GPIO_Port GPIOB
#define LA_OP_Pin GPIO_PIN_9
#define LA_OP_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
