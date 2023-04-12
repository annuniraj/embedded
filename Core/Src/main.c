/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi2;
SPI_HandleTypeDef hspi3;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim16;
TIM_HandleTypeDef htim17;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
#define RtcHandle &hrtc
static uint16_t YearStart = 2000;
char message[50], message1[50];
uint8_t size;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
static void MX_SPI2_Init(void);
static void MX_SPI3_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM6_Init(void);
static void MX_TIM16_Init(void);
static void MX_TIM17_Init(void);
/* USER CODE BEGIN PFP */
extern unsigned long int	WR_Counts,
							FCT_Counts,
							WL_Counts;
extern uint8_t Phy_TCP_IP;

extern uint8_t  server_Add[4];


uint32_t count;
uint32_t tim16_count;
uint32_t tim17_count;
uint32_t PortStatus;
uint8_t remotePort;
uint8_t remote;
uint8_t Ping_ack[2048] = PING_ACK_CMD;
uint8_t Abox_not_ready[2048] = ABOX_NOT_READY_CMD;
uint8_t Recv_Ping[2048];


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t spi_rb(void)
{
	uint8_t rbuf;
	HAL_SPI_Receive(&hspi3, &rbuf, 1, 0xffffffff);
	return rbuf;
}

void spi_wb(uint8_t b)
{
	HAL_SPI_Transmit(&hspi3, &b, 1, 0xffffffff);
}

void Timer2_Stop()
{
	HAL_TIM_Base_Stop(&htim2);
}

void Timer2_DeInitilized()
{
	HAL_TIM_Base_DeInit(&htim2);
	HAL_TIM_Base_DeInit(&htim6);
	HAL_TIM_Base_DeInit(&htim16);
	HAL_TIM_Base_DeInit(&htim17);
}

void Timer2_Initilized()
{
	HAL_TIM_Base_Init(&htim2);
	HAL_TIM_Base_Init(&htim6);
	HAL_TIM_Base_Init(&htim16);
	HAL_TIM_Base_Init(&htim17);
}

void Timer2_Start()
{
	HAL_TIM_Base_Start(&htim2);
}

void Timer6_Start()
{
	HAL_TIM_Base_Start_IT(&htim6);
}

void Timer6_Stop()
{
	HAL_TIM_Base_Stop_IT(&htim6);
}

void Timer16_Start()
{
	HAL_TIM_Base_Init(&htim16);
	HAL_TIM_Base_Start_IT(&htim16);
}

void Timer16_Stop()
{
	HAL_TIM_Base_Stop_IT(&htim16);
	HAL_TIM_Base_DeInit(&htim16);
}

void Timer17_Start()
{
	HAL_TIM_Base_Init(&htim17);
	HAL_TIM_Base_Start_IT(&htim17);
}

void Timer17_Stop()
{
	HAL_TIM_Base_Stop_IT(&htim17);
	HAL_TIM_Base_DeInit(&htim17);
}

int Timer2_GetTimer()
{
	uint32_t Tim_val = __HAL_TIM_GetCounter(&htim2);
	return Tim_val;
}
/* USER CODE END 0 */

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
  MX_RTC_Init();
  MX_SPI2_Init();
  MX_SPI3_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  MX_TIM6_Init();
  MX_TIM16_Init();
  MX_TIM17_Init();
  /* USER CODE BEGIN 2 */
  //unsigned char* Count_Bulletin[10];
  //unsigned char* Count_Bulletin1[10];
  unsigned char Date_RTC[10], Month_RTC[10], Year_RTC[10], Hour_RTC[10], Min_RTC[10], Sec_RTC[10];
  RTC_TimeTypeDef sTime;
  RTC_DateTypeDef sDate;

//  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
//  sDate.Date = 30;
//  sDate.Month = 3;
//  sDate.Year = 23;
//  HAL_RTC_SetDate(RtcHandle, &sDate, RTC_FORMAT_BIN);
//  sTime.Hours = 14;
//  sTime.Minutes = 14;
//  HAL_RTC_SetTime(RtcHandle, &sTime, RTC_FORMAT_BIN);
//  uint16_t mseconds;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */



  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  HAL_RTC_GetTime(RtcHandle, &sTime, RTC_FORMAT_BIN);
	  HAL_RTC_GetDate(RtcHandle, &sDate, RTC_FORMAT_BIN);
	  //mseconds = (sTime.SubSeconds * 1000) / (sTime.SecondFraction + 1);

	  switch(Get_state())
	  	  {
	  	  case Initilisation_State:
	  		  Initilisation_State_Handler();

	  		  if(Get_event()==Health_Event)
	  		  {
		  		  ctlwizchip(CW_GET_PHYLINK, (void*) &Phy_TCP_IP);
		  		  //if((Phy_TCP_IP==PHY_LINK_OFF) || (PortStatus==SOCKERR_SOCKSTATUS))
		  		  if(Phy_TCP_IP==PHY_LINK_OFF)
		  		  {
		  			  Set_state(Initilisation_State);
		  		  }
		  		  else
		  		  {
		  			Set_state (Health_State);//Health_State_Handler();
		  		  }
	  		  }
	  		  break;

	  	  case Health_State:
	  		  Health_State_Handler();
	  		  if(Get_event()==Reset_Event)
	  		  {
	  			  Reset_State_Handler();
	  		  }
	  		  break;

	  	  case Reset_State:
	  		  if(Get_event()==Idle_Event)
	  		  {
	  			  Idle_State_Handler();
	  			  Timer16_Stop();
	  			  tim16_count=0;
	  			  Timer16_Start();
	  		  }
	  		  break;

	  	  case Idle_State:
	  		  if(Get_event()==WRSide_Train_Detect_Event)
	  		  {
	  			  WRSide_Train_Presence_State_Handler();
	  		  }
	  		  else if (Get_event()==WLSide_Train_Detect_Event)
	  		  {
	  			  WLSide_Train_Presence_State_Handler();
	  		  }

//	  		  uint8_t  server_Address[4] = {192,168,1,111};
//	  		  Refresh_Watchdog();
//	  		  connect(0,server_Address,PORT_ADDR);
//	  		  remote = getsockopt(0,SO_STATUS, &remotePort);
//	  		  if(remotePort==28)
//	  		  {
//	  			  Set_state(Initilisation_State);
//	  		  }

	  		   //Check for physical connection.
	  		  ctlwizchip(CW_GET_PHYLINK, (void*) &Phy_TCP_IP);
	  		  if(Phy_TCP_IP==PHY_LINK_OFF)
	  		  {
	  			  Set_state(Initilisation_State);
	  		  }

	  		  else if(Phy_TCP_IP==PHY_LINK_ON)
	  		  {
	  			  //sprintf(message1, "Time: %2.2u:%2.2u:%2.2u\n\r", sTime.Hours, sTime.Minutes, sTime.Seconds);
	  			  //send(0, (uint32_t *)message1,strlen(message1));
	  			  //sprintf(message, "Date: %2.2u-%2.2u-%4.4u\n\r", sDate.Date, sDate.Month, sDate.Year + YearStart,sTime.);
	  			  //send(0, (uint32_t *)message,strlen(message));
	  			  //HAL_Delay(1000);
	  			  if (tim16_count>TIM16TIMEOOUTPERIOD)
	  			  {
	  				  memset(Recv_Ping,0,sizeof Recv_Ping);
	  				  recv(0, Recv_Ping,2048);
	  				  if(strcmp(Abox_not_ready,Recv_Ping)!=0)
	  				  {
	  					send(0, (uint8_t *)PING_CMD,strlen(PING_CMD));
	  				  }
	  				Timer16_Stop();
	  				tim16_count=0;
	  				Timer16_Start();
	  				Timer17_Start();

	  				while(tim17_count<TIM17TIMEOOUTPERIOD)
	  				{
	  					recv(0, Recv_Ping,2048);
	  					if(Get_event()==WRSide_Train_Detect_Event)
	  					{
	  						WRSide_Train_Presence_State_Handler();
	  						break;
	  					}
	  					else if (Get_event()==WLSide_Train_Detect_Event)
	  					{
	  						WLSide_Train_Presence_State_Handler();
	  						break;
	  					}

	  					if(strcmp(Abox_not_ready,Recv_Ping)==0)
	  					{
	  						Timer17_Stop();
	  						tim17_count=0;
	  						Set_state(Health_State);
	  						Set_event(Reset_Event);
	  						break;
	  					}
	  				}
  					if(strcmp(Ping_ack,Recv_Ping)!=0 && (Get_state()!=Health_State))
  					{
  						Timer17_Stop();
  						tim17_count=0;
  						Set_state(Initilisation_State);
  						break;
  					}
	  				Timer17_Stop();
	  				tim17_count=0;
	  			  }
	  		  }
	  		  break;

	  	  case WRSide_Train_Presence_State:

//			  itoa(count,Count_Bulletin,10);
//			  send(0, (uint32_t *)strcat(Count_Bulletin,","), strlen(Count_Bulletin));
//			  HAL_Delay(1000);

			  if (count>TIMEOOUTPERIOD)
			  {
				  Set_event(Train_Exit_Event);
			  }

	  		  if(Get_event()==Train_Exit_Event)
	  		  {
	  			  Train_Exit_State_Handler();
	  		  }
	  		  break;

	  	  case WLSide_Train_Presence_State:

//			  itoa(count,Count_Bulletin1,10);
//			  send(0, (uint32_t *)strcat(Count_Bulletin1,","), strlen(Count_Bulletin1));
//			  HAL_Delay(1000);

			  if (count>TIMEOOUTPERIOD)
			  {
				  Set_event(Train_Exit_Event);
			  }

	  		  if(Get_event()==Train_Exit_Event)
	  		  {
	  			  Train_Exit_State_Handler();
	  		  }
	  		  break;

	  	  case Train_Exit_State:
	  		  if(Get_event()==Log_Data_Event)
	  		  {
	  			  Log_Data_State_Handler();
	  		  }
	  		  break;

	  	  case Log_Data_State:
	  		  if(Get_event()==Reset_Event)
	  		  {
	  			  Reset_State_Handler();
	  		  }
	  		  break;
	  	  }
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

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV5;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL14;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_TIM16
                              |RCC_PERIPHCLK_TIM17;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  PeriphClkInit.Tim16ClockSelection = RCC_TIM16CLK_HCLK;
  PeriphClkInit.Tim17ClockSelection = RCC_TIM17CLK_HCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */
  if (HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1) != 0xBEBE)
     {
     // Write Back Up Register 1 Data
     HAL_PWR_EnableBkUpAccess();
     // Writes a data in a RTC Backup data Register 1
     HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0xBEBE);
     HAL_PWR_DisableBkUpAccess();
     }
     else
     {
        // data register already written so turn LED3
        return;
     }

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 15;
  sTime.Minutes = 16;
  sTime.Seconds = 0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_WEDNESDAY;
  sDate.Month = RTC_MONTH_MARCH;
  sDate.Date = 30;
  sDate.Year = 23;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable the WakeUp
  */
  if (HAL_RTCEx_SetWakeUpTimer(&hrtc, 0, RTC_WAKEUPCLOCK_RTCCLK_DIV16) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 7;
  hspi3.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi3.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 70-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 0xFFFFFFFF-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 6999;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 9999;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief TIM16 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM16_Init(void)
{

  /* USER CODE BEGIN TIM16_Init 0 */

  /* USER CODE END TIM16_Init 0 */

  /* USER CODE BEGIN TIM16_Init 1 */

  /* USER CODE END TIM16_Init 1 */
  htim16.Instance = TIM16;
  htim16.Init.Prescaler = 6999;
  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim16.Init.Period = 9999;
  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim16.Init.RepetitionCounter = 0;
  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM16_Init 2 */

  /* USER CODE END TIM16_Init 2 */

}

/**
  * @brief TIM17 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM17_Init(void)
{

  /* USER CODE BEGIN TIM17_Init 0 */

  /* USER CODE END TIM17_Init 0 */

  /* USER CODE BEGIN TIM17_Init 1 */

  /* USER CODE END TIM17_Init 1 */
  htim17.Instance = TIM17;
  htim17.Init.Prescaler = 6999;
  htim17.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim17.Init.Period = 9999;
  htim17.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim17.Init.RepetitionCounter = 0;
  htim17.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim17) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM17_Init 2 */

  /* USER CODE END TIM17_Init 2 */

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
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_RXOVERRUNDISABLE_INIT;
  huart2.AdvancedInit.OverrunDisable = UART_ADVFEATURE_OVERRUN_DISABLE;
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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(FCT_TRIG_LED_GPIO_Port, FCT_TRIG_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LA_TRIG_LED_Pin|CA_TRIG_LED_Pin|WR_TRIG_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LAN_CS_Pin|CA_OP_Pin|LA_OP_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|WL_TRIG_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, CA_OP1_Pin|LA_OP1_Pin|LAN_RESET_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : FCT_TRIG_LED_Pin */
  GPIO_InitStruct.Pin = FCT_TRIG_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(FCT_TRIG_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : WR_IP_Pin WL_IP_Pin F_IP_Pin */
  GPIO_InitStruct.Pin = WR_IP_Pin|WL_IP_Pin|F_IP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LA_TRIG_LED_Pin CA_TRIG_LED_Pin CA_OP1_Pin LA_OP1_Pin
                           LAN_RESET_Pin */
  GPIO_InitStruct.Pin = LA_TRIG_LED_Pin|CA_TRIG_LED_Pin|CA_OP1_Pin|LA_OP1_Pin
                          |LAN_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LAN_CS_Pin */
  GPIO_InitStruct.Pin = LAN_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LAN_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LAN_INT_Pin */
  GPIO_InitStruct.Pin = LAN_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(LAN_INT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 CA_OP_Pin LA_OP_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_12|CA_OP_Pin|LA_OP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : WL_TRIG_LED_Pin */
  GPIO_InitStruct.Pin = WL_TRIG_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(WL_TRIG_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : WR_TRIG_LED_Pin */
  GPIO_InitStruct.Pin = WR_TRIG_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(WR_TRIG_LED_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

  /* Prevent unused argument(s) compilation warning */
  UNUSED(GPIO_Pin);

  /* NOTE: This function should not be modified, when the callback is needed
   */

  switch(GPIO_Pin)
  {
  case WR_IP_Pin:
	  switch(Get_state()){
	  case Idle_State:
		  Set_event(WRSide_Train_Detect_Event);
	  case WRSide_Train_Presence_State:
		  WR_Interrupt_Service();
		  break;
	  case WLSide_Train_Presence_State:
		  WR_Interrupt_Service();
		  break;
	  }

	  if (WR_Counts==WL_Counts)//(Counts of WL_Counts==WR_Counts)
	  {
		  Set_event(Train_Exit_Event);
	  }
	  break;

  case WL_IP_Pin:

	  switch(Get_state()){
	  case Idle_State:
		  Set_event(WLSide_Train_Detect_Event);
	  case WRSide_Train_Presence_State:
		  WL_Interrupt_Service();
		  break;
	  case WLSide_Train_Presence_State:
		  WL_Interrupt_Service();
		  break;
	  }

	  if (WR_Counts==WL_Counts)
	  {
		  Set_event(Train_Exit_Event);
	  }

	  break;


  case F_IP_Pin:


	  switch(Get_state())
	  {
	  case WRSide_Train_Presence_State:
		  FCT_Interrupt_Service();
		  break;
	  case WLSide_Train_Presence_State:
		  FCT_Interrupt_Service();
		  break;
	  }
	  break;

  case LAN_INT_Pin:

	  Lan_Interrupt_Service();
	  break;
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
