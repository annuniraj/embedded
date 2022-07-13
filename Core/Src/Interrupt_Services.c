/*
 * Inturrpt_Service.c
 *
 *  Created on: 27-May-2022
 *      Author: Anil
 */

#include "Interrupt_Services.h"
#include "main.h"

void Manual_delay(void)
{
	for(int i=0;i<=120;i++)
	{

	}
}

void Lan_Interrupt_Service(void)
{
	if(getSn_IR(0) & (1 << 2))   // RECV Interrupt
		{
		Sock_Rx_Flag = 1;
		recv(0,Ethernet_Rx_DataBuff,2048);

		//HAL_UART_Transmit(&huart2, (uint8_t*)Ethernet_Rx_DataBuff, strlen((const char*)Ethernet_Rx_DataBuff), 100)
		//send(0, Ethernet_Rx_DataBuff,strlen((const char*)Ethernet_Rx_DataBuff));

		for(uint16_t i= 0; i < 2048; i++)
		{
			Ethernet_Rx_DataBuff[i] = '\0';
		}

		//HAL_UART_Transmit(&huart2, (uint8_t*)"\r\n", 2, 100);
		setSn_IR(0, 0x04);
		}
	else if(getSn_IR(0) & (1 << 1))  //DISCONNECT Interrupt
		{
		IntStatus = 0;
		disconnect(0);
		close(0);
		Sock_Disconnect_Flag = 1;
		//HAL_UART_Transmit(&huart2, (uint8_t*)"Server Disconnected\r\n", 21, 100);
		Ethernet_Connect();
		setSn_IR(0, 0x02);
		}
	else
	{
		setSn_IR(0, 0x1F);
	}
}

void WR_Interrupt_Service(void)
{
	send(0, (uint8_t *)"WR ",strlen("WR "));
	WR_Counts++;
	if(Lt_Rt_flag==0)
	{
		switch(WR_Counts)
		{
		case(1):
				HAL_TIM_Base_Start(&htim2);
				WR_Instant=__HAL_TIM_GetCounter(&htim2);
				RingWriteElement(&WR_Ring,&WR_Instant);
				break;
		case(2):
				send(0, (uint8_t *)GRAB_START_CMD,strlen(GRAB_START_CMD));
				Entry_flag=1;
				Rt_Lt_flag=1;
				//WR_Instant=__HAL_TIM_GetCounter(&htim2);
				//RingWriteElement(&WR_Ring,&WR_Instant);
				break;
		}

	}

	if(Entry_flag==1)
	{
		WR_Instant=__HAL_TIM_GetCounter(&htim2);
		RingWriteElement(&WR_Ring,&WR_Instant);
	}
}

void TR_Interrupt_Service(void)
{
	send(0, (uint8_t *)"TR ",strlen("TR "));
	TR_Counts++;
	if(Rt_Lt_flag==1)
	{
		TR_Instant=__HAL_TIM_GetCounter(&htim2);
		RingWriteElement(&TR_Ring,&TR_Instant);
	}
	else if(Lt_Rt_flag==1)
	{
		TR_Instant=__HAL_TIM_GetCounter(&htim2);
		RingWriteElement(&TR_Ring,&TR_Instant);
		//Camera ON
		//Laser ON
		HAL_GPIO_WritePin(GPIOB,CA_OP_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,CA_OP1_Pin,GPIO_PIN_RESET);
		//HAL_Delay(1);
		//
		HAL_GPIO_WritePin(GPIOB,CA_OP_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,CA_OP1_Pin,GPIO_PIN_SET);
	}
}

void TL_Interrupt_Service(void)
{
	send(0, (uint8_t *)"TLin ",strlen("TLin "));
	TL_Counts++;
	if(Lt_Rt_flag==1)
	{
		TL_Instant=__HAL_TIM_GetCounter(&htim2);
		RingWriteElement(&TL_Ring,&TL_Instant);
	}
	else if(Rt_Lt_flag==1)
	{
		TL_Instant=__HAL_TIM_GetCounter(&htim2);
		RingWriteElement(&TL_Ring,&TL_Instant);
		//send(0, (uint8_t *)"TL1 ",strlen("TL1 "));
		//Camera ON
		//Laser ON
		HAL_GPIO_WritePin(GPIOB,CA_OP_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,CA_OP1_Pin,GPIO_PIN_RESET);

		Manual_delay();
		HAL_GPIO_WritePin(GPIOB,CA_OP_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,CA_OP1_Pin,GPIO_PIN_SET);
		//send(0, (uint8_t *)"TL2 ",strlen("TL2 "));
	}
	//send(0, (uint8_t *)"TLout ",strlen("TLout "));
}

void WL_Interrupt_Service(void)
{
	//send(0, (uint8_t *)"WL ",strlen("WL "));
	WL_Counts++;
	if(Rt_Lt_flag==0)
	{
		switch(WL_Counts)
		{
		case(1):
				HAL_TIM_Base_Start(&htim2);
				WL_Instant=__HAL_TIM_GetCounter(&htim2);
				RingWriteElement(&WL_Ring,&WL_Instant);
				break;

		case(2):
				send(0, (uint8_t *)GRAB_START_CMD,strlen(GRAB_START_CMD));
				Entry_flag=1;
				Lt_Rt_flag=1;
				//WL_Instant=__HAL_TIM_GetCounter(&htim2);
				//RingWriteElement(&WL_Ring,&WL_Instant);
				break;
		}

	}

	if(Entry_flag==1)
	{
		WL_Instant=__HAL_TIM_GetCounter(&htim2);
		RingWriteElement(&WL_Ring,&WL_Instant);
	}
}
