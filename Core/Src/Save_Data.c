#include "Save_Data.h"

 extern RingBuffer_t		WR_Ring,
 					FCT_Ring,
 					WL_Ring;

 extern unsigned long int	WR_Counts,
 					FCT_Counts,
 					WL_Counts;

 unsigned char*	WR_Ring_Bulletin[10],
 				WL_Ring_Bulletin[10],
 				FCT_Ring_Bulletin[10],
 				WR_Count_Bulletin[10],
 				WL_Count_Bulletin[10],
 				FCT_Count_Bulletin[10];

 uint8_t WR_Roller,
 		WL_Roller,
 		FCT_Roller;

 buff_size	WR_Ring_Unit,
 			WL_Ring_Unit,
 			FCT_Ring_Unit;

void Send_WR_Samples()
{
	WR_Roller = (BUFFERSIZE-1)-(WR_Ring.place + 1);
	for(int Iter=0;Iter<=WR_Roller;Iter++)
	{
		RingReadElement(&WR_Ring,&WR_Ring_Unit);
		itoa(WR_Ring_Unit,WR_Ring_Bulletin,10);
		unsigned char* WR_Packet;
		WR_Packet = malloc(strlen(LOG_WRITE_CMD)+strlen(WR_Ring_Bulletin));
		strcpy(WR_Packet,LOG_WRITE_CMD);
		strcat(WR_Packet,WR_Ring_Bulletin);

		send(0, (buff_size *)WR_Packet,strlen(WR_Packet));
		free(WR_Packet);
		WR_Packet=NULL;

		HAL_Delay(100);
	}
}

void Send_FCT_Samples()
{
	FCT_Roller = (BUFFERSIZE-1)-(FCT_Ring.place + 1);
	for(int Iter=0;Iter<=FCT_Roller;Iter++)
	{
		RingReadElement(&FCT_Ring,&FCT_Ring_Unit);
		itoa(FCT_Ring_Unit,FCT_Ring_Bulletin,10);
		unsigned char* FCT_Packet;
		FCT_Packet = malloc(strlen(LOG_WRITE_CMD)+strlen(FCT_Ring_Bulletin));
		strcpy(FCT_Packet,LOG_WRITE_CMD);
		strcat(FCT_Packet,FCT_Ring_Bulletin);

		send(0, (buff_size *)FCT_Packet,strlen(FCT_Packet));
		free(FCT_Packet);
		FCT_Packet=NULL;
		HAL_Delay(100);
	}
}


void Send_WL_Samples()
{
	WL_Roller = (BUFFERSIZE-1)-(WL_Ring.place + 1);
	for(int Iter=0;Iter<=WL_Roller;Iter++)
	{
		RingReadElement(&WL_Ring,&WL_Ring_Unit);
		itoa(WL_Ring_Unit,WL_Ring_Bulletin,10);
		unsigned char* WL_Packet;
		WL_Packet = malloc(strlen(LOG_WRITE_CMD)+strlen(WL_Ring_Bulletin));
		strcpy(WL_Packet,LOG_WRITE_CMD);
		strcat(WL_Packet,WL_Ring_Bulletin);

		send(0, (buff_size *)WL_Packet,strlen(WL_Packet));
		free(WL_Packet);
		WL_Packet=NULL;
		HAL_Delay(100);
	}
}

void Send_Data()
{
	send(0, (uint8_t *)GRAB_STOP_CMD,strlen(GRAB_STOP_CMD));
	HAL_Delay(100);
	send(0, (uint8_t *)LOG_START_CMD,strlen(LOG_START_CMD));
	HAL_Delay(100);

	send(0, (uint8_t *)LOG_WR_CMD,strlen(LOG_WR_CMD));
	HAL_Delay(100);

	Send_WR_Samples();//send WR Samples
	HAL_Delay(100);
	send(0, (uint8_t *)LOG_END_WRITE_CMD,strlen(LOG_END_WRITE_CMD));
	HAL_Delay(100);

	send(0, (uint8_t *)LOG_FCT_CMD,strlen(LOG_FCT_CMD));
	HAL_Delay(100);

	//Send_FCT_Samples();//send  Samples
	HAL_Delay(100);
	send(0, (uint8_t *)LOG_END_WRITE_CMD,strlen(LOG_END_WRITE_CMD));
	HAL_Delay(100);

	send(0, (uint8_t *)LOG_WL_CMD,strlen(LOG_WL_CMD));
	HAL_Delay(100);

	Send_WL_Samples();
	HAL_Delay(100);
	send(0, (uint8_t *)LOG_END_WRITE_CMD,strlen(LOG_END_WRITE_CMD));
	HAL_Delay(100);

	itoa(WR_Counts,WR_Count_Bulletin,10);
	send(0, (buff_size *)strcat(WR_Count_Bulletin,","),strlen(WR_Count_Bulletin));

	HAL_Delay(100);
	itoa(FCT_Counts,FCT_Count_Bulletin,10);
	send(0, (buff_size *)strcat(FCT_Count_Bulletin,","),strlen(FCT_Count_Bulletin));

	HAL_Delay(100);
	itoa(WL_Counts,WL_Count_Bulletin,10);
	send(0, (buff_size *)strcat(WL_Count_Bulletin,","),strlen(WL_Count_Bulletin));

	HAL_Delay(100);
	send(0, (uint8_t *)LOG_STOP_CMD,strlen(LOG_STOP_CMD));
}
