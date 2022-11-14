#include "Save_Data.h"

void Send_WR_Samples()
{
	WR_Roller = (BUFFERSIZE-1)-(WR_Ring.place + 1);
	for(int Iter=0;Iter<=WR_Roller;Iter++)
	{
		RingReadElement(&WR_Ring,&WR_Ring_Unit);
		itoa(WR_Ring_Unit,WR_Ring_Bulletin,10);
		send(0, (buff_size *)strcat(WR_Ring_Bulletin,","),strlen(WR_Ring_Bulletin));
		//send(0, (buff_size *)",",strlen(","));
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
		send(0, (buff_size *)strcat(FCT_Ring_Bulletin,","),strlen(FCT_Ring_Bulletin));
		//send(0, (buff_size *)",",strlen(","));
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
		send(0, (buff_size *)strcat(WL_Ring_Bulletin,","),strlen(WL_Ring_Bulletin));
		//send(0, (buff_size *)",",strlen(","));
		HAL_Delay(100);
	}
}

void Send_Data()
{
	send(0, (uint8_t *)GRAB_STOP_CMD,strlen(GRAB_STOP_CMD));
	HAL_Delay(500);
	send(0, (uint8_t *)LOG_START_CMD,strlen(LOG_START_CMD));
	HAL_Delay(500);

	send(0, (uint8_t *)LOG_WR_CMD,strlen(LOG_WR_CMD));
	HAL_Delay(500);
	send(0, (uint8_t *)LOG_WRITE_CMD,strlen(LOG_WRITE_CMD));
	HAL_Delay(500);
	Send_WR_Samples();//send WR Samples
	HAL_Delay(500);
	send(0, (uint8_t *)LOG_END_WRITE_CMD,strlen(LOG_END_WRITE_CMD));
	HAL_Delay(500);

	send(0, (uint8_t *)LOG_FCT_CMD,strlen(LOG_FCT_CMD));
	HAL_Delay(500);
	send(0, (uint8_t *)LOG_WRITE_CMD,strlen(LOG_WRITE_CMD));
	HAL_Delay(500);
	Send_FCT_Samples();//send  Samples
	HAL_Delay(500);
	send(0, (uint8_t *)LOG_END_WRITE_CMD,strlen(LOG_END_WRITE_CMD));
	HAL_Delay(500);

	send(0, (uint8_t *)LOG_WL_CMD,strlen(LOG_WL_CMD));
	HAL_Delay(500);
	send(0, (uint8_t *)LOG_WRITE_CMD,strlen(LOG_WRITE_CMD));
	HAL_Delay(500);
	Send_WL_Samples();
	HAL_Delay(500);
	send(0, (uint8_t *)LOG_END_WRITE_CMD,strlen(LOG_END_WRITE_CMD));
	HAL_Delay(500);

	itoa(WR_Counts,WR_Count_Bulletin,10);
	send(0, (buff_size *)strcat(WR_Count_Bulletin,","),strlen(WR_Count_Bulletin));

	HAL_Delay(500);
	itoa(FCT_Counts,FCT_Count_Bulletin,10);
	send(0, (buff_size *)strcat(FCT_Count_Bulletin,","),strlen(FCT_Count_Bulletin));

	HAL_Delay(500);
	itoa(WL_Counts,WL_Count_Bulletin,10);
	send(0, (buff_size *)strcat(WL_Count_Bulletin,","),strlen(WL_Count_Bulletin));

	HAL_Delay(500);
	send(0, (uint8_t *)LOG_STOP_CMD,strlen(LOG_STOP_CMD));
}
