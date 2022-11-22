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
	if(getSn_IR(0) & (1 << 2))
	{
		recv(0,Receive_Buffer,255);
//		if(Receive_Buffer==PING_ACK_CMD)
//		{
//			//Set State Idle State
//		}

		memset(Receive_Buffer,0,sizeof Receive_Buffer);// clear the receiving buffer
		setSn_IR(0, 0x04);
	}

	else if(getSn_IR(0) & (1 << 1))
	{
		Ethernet_Connect();
		setSn_IR(0, 0x02);
	}

	else
	{
		setSn_IR(0, 0x1F);/// decimal 31 .. for more info check W5500 datasheet, Page 48
	}
}

void WR_Interrupt_Service(void)
{
	WR_Counts++;
	if(Lt_Rt_flag==0)
	{
		switch(WR_Counts)
		{
		case(1):
				send(0, (uint8_t *)INIT_CMD,strlen(INIT_CMD));
		        Timer2_Start();
				WR_Instant=Timer2_GetTimer();
				RingWriteElement(&WR_Ring,&WR_Instant);
				break;
		case(2):
				send(0, (uint8_t *)GRAB_START_CMD,strlen(GRAB_START_CMD));
				Entry_flag=1;
				Rt_Lt_flag=1;
				WR_Instant=Timer2_GetTimer();
				RingWriteElement(&WR_Ring,&WR_Instant);
				break;
		}

	}

	if(Entry_flag==1)
	{
		WR_Instant=Timer2_GetTimer();
		RingWriteElement(&WR_Ring,&WR_Instant);
	}
}


void FCT_Interrupt_Service(void)
{
	FCT_Counts++;
	if(Lt_Rt_flag==1)
	{
		FCT_Instant=Timer2_GetTimer();
		RingWriteElement(&FCT_Ring,&FCT_Instant);
	}
	else if(Rt_Lt_flag==1)
	{
		FCT_Instant=Timer2_GetTimer();
		RingWriteElement(&FCT_Ring,&FCT_Instant);

		//Camera ON
		//Laser ON
		HAL_GPIO_WritePin(GPIOB,CA_OP_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,CA_OP1_Pin,GPIO_PIN_RESET);

		Manual_delay();
		HAL_GPIO_WritePin(GPIOB,CA_OP_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,CA_OP1_Pin,GPIO_PIN_SET);
	}

}

void WL_Interrupt_Service(void)
{
	WL_Counts++;
	if(Rt_Lt_flag==0)
	{
		switch(WL_Counts)
		{
		case(1):
				send(0, (uint8_t *)INIT_CMD,strlen(INIT_CMD));
				Timer2_Start();
				WL_Instant=Timer2_GetTimer();
				RingWriteElement(&WL_Ring,&WL_Instant);
				break;

		case(2):
				send(0, (uint8_t *)GRAB_START_CMD,strlen(GRAB_START_CMD));
				Entry_flag=1;
				Lt_Rt_flag=1;
				WL_Instant=Timer2_GetTimer();
				RingWriteElement(&WL_Ring,&WL_Instant);
				break;
		}

	}

	if(Entry_flag==1)
	{
		WL_Instant=Timer2_GetTimer();
		RingWriteElement(&WL_Ring,&WL_Instant);
	}
}
