/*
 * Inturrpt_Service.c
 *
 *  Created on: 27-May-2022
 *      Author: Anil
 */

#include "Interrupt_Services.h"
#include "main.h"

 extern RingBuffer_t		WR_Ring,
 					FCT_Ring,
 					WL_Ring;

 unsigned long int	WR_Counts,
 					FCT_Counts,
 					WL_Counts;

 buff_size			WR_Instant,
 					WL_Instant,
 					FCT_Instant;

 uint16_t			Lt_Rt_flag,
 					Rt_Lt_flag,
 					Entry_flag;

 uint8_t Receive_Buffer[255];

 void Save_delay(void)
 {
 	for(int i=0;i<=500000;i++)
 	{

 	}
 }

void Manual_delay(void)
{
	for(int i=0;i<=50000;i++)
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
		if (Get_state() == Direct_Control_State)
		{
			if (Receive_Buffer == DCTR_EXIT)
				Set_event(DCTR_EXIT_Event);
			if (Receive_Buffer == DCTR_TRIGGER_CAMERA)
				Set_event(DCTR_TRIGGER_CAMERA_Event);
			if (Receive_Buffer == DCTR_TRIGGER_CAMERA_LASER);
				Set_event(DCTR_TRIGGER_CAMERA_LASER_Event);
			if (Receive_Buffer == DCTR_PULSE_LASER);
				Set_event(DCTR_PULSE_LASER_Event);
		}

		else if (Get_state() == Idle_State)
		{
			if (Receive_Buffer == DCTR_INIT)
			{
				Set_event(DCTR_INIT_Event);
			}
		}
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
	HAL_GPIO_WritePin(GPIOA,WR_TRIG_LED_Pin,GPIO_PIN_SET);
	Manual_delay();
	HAL_GPIO_WritePin(GPIOA,WR_TRIG_LED_Pin,GPIO_PIN_RESET);
	WR_Counts++;
	if(Lt_Rt_flag==0)
	{
		switch(WR_Counts)
		{
		case(1):
				//send(0, (uint8_t *)INIT_CMD,strlen(INIT_CMD));
		        Timer2_Start();
				WR_Instant=Timer2_GetTimer();
				RingWriteElement(&WR_Ring,&WR_Instant);
				break;
		case(2):
				send(0, (uint8_t *)GRAB_START_CMD,strlen(GRAB_START_CMD));
				Entry_flag=1;
				Rt_Lt_flag=1;
				Timer6_Start();
				break;
		}
	}

	if(Entry_flag==1)
	{
		WR_Instant=Timer2_GetTimer();
		RingWriteElement(&WR_Ring,&WR_Instant);
	}

	if(count<=TIMEOOUTPERIOD  || WR_Counts>=2 )
	{
		Timer6_Stop();
		count=0;
		Timer6_Start();
	}
}


void FCT_Interrupt_Service(void)
{
	HAL_GPIO_WritePin(GPIOC,FCT_TRIG_LED_Pin,GPIO_PIN_SET);
	Manual_delay();
	HAL_GPIO_WritePin(GPIOC,FCT_TRIG_LED_Pin,GPIO_PIN_RESET);
	FCT_Counts++;
	if(Lt_Rt_flag==1)
	{
		FCT_Instant=Timer2_GetTimer();
		RingWriteElement(&FCT_Ring,&FCT_Instant);

		//HAL_GPIO_WritePin(GPIOA,CA_TRIG_LED_Pin,GPIO_PIN_RESET);//test
		//Laser ON
		HAL_GPIO_WritePin(GPIOA,LA_TRIG_LED_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,LA_OP_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,LA_OP1_Pin,GPIO_PIN_RESET);
		Manual_delay();

		//Camera ON
		HAL_GPIO_WritePin(GPIOA,CA_TRIG_LED_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,CA_OP_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,CA_OP1_Pin,GPIO_PIN_SET);
		//HAL_Delay(200);

		//Camera OFF
		//Manual_delay();
		Manual_delay();
		HAL_GPIO_WritePin(GPIOA,CA_TRIG_LED_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB,CA_OP_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,CA_OP1_Pin,GPIO_PIN_RESET);
		Manual_delay();

		//Laser OFF
		HAL_GPIO_WritePin(GPIOA,LA_TRIG_LED_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB,LA_OP_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,LA_OP1_Pin,GPIO_PIN_SET);

	}
	else if(Rt_Lt_flag==1)
	{
		FCT_Instant=Timer2_GetTimer();
		RingWriteElement(&FCT_Ring,&FCT_Instant);

		//HAL_GPIO_WritePin(GPIOA,CA_TRIG_LED_Pin,GPIO_PIN_RESET);//test
		//Laser ON
		HAL_GPIO_WritePin(GPIOA,LA_TRIG_LED_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,LA_OP_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,LA_OP1_Pin,GPIO_PIN_RESET);
		Manual_delay();

		//Camera ON
		HAL_GPIO_WritePin(GPIOA,CA_TRIG_LED_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,CA_OP_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,CA_OP1_Pin,GPIO_PIN_SET);
		//HAL_Delay(200);

		//Camera OFF
		//Manual_delay();
		Manual_delay();
		HAL_GPIO_WritePin(GPIOA,CA_TRIG_LED_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB,CA_OP_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,CA_OP1_Pin,GPIO_PIN_RESET);
		Manual_delay();

		//Laser OFF
		HAL_GPIO_WritePin(GPIOA,LA_TRIG_LED_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB,LA_OP_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,LA_OP1_Pin,GPIO_PIN_SET);
	}

	if(count<=TIMEOOUTPERIOD  || FCT_Counts>=2 )
	{
		Timer6_Stop();
		count=0;
		Timer6_Start();
	}

}

void WL_Interrupt_Service(void)
{
	HAL_GPIO_WritePin(GPIOB,WL_TRIG_LED_Pin,GPIO_PIN_SET);
	Manual_delay();
	HAL_GPIO_WritePin(GPIOB,WL_TRIG_LED_Pin,GPIO_PIN_RESET);
	WL_Counts++;
	if(Rt_Lt_flag==0)
	{
		switch(WL_Counts)
		{
		case(1):
				//send(0, (uint8_t *)INIT_CMD,strlen(INIT_CMD));
				Timer2_Start();
				WL_Instant=Timer2_GetTimer();
				RingWriteElement(&WL_Ring,&WL_Instant);
				break;

		case(2):
				send(0, (uint8_t *)GRAB_START_CMD,strlen(GRAB_START_CMD));
				Entry_flag=1;
				Lt_Rt_flag=1;
				Timer6_Start();
				break;
		}
	}

	if(Entry_flag==1)
	{
		WL_Instant=Timer2_GetTimer();
		RingWriteElement(&WL_Ring,&WL_Instant);
	}

	if(count<=TIMEOOUTPERIOD  || WL_Counts>=2 )
	{
		Timer6_Stop();
		count=0;
		Timer6_Start();
	}
}
