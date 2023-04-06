 #include "state_Handler.h"

 buff_size			WR_Samples[BUFFERSIZE],
					FCT_Samples[BUFFERSIZE],
					WL_Samples[BUFFERSIZE];

 RingBuffer_t		WR_Ring,
 					FCT_Ring,
 					WL_Ring;

 extern unsigned long int	WR_Counts,
 					FCT_Counts,
 					WL_Counts;

void Initilisation_State_Handler()
{
	Set_state(Initilisation_State);
	Reset_event();
	Init_Ethernet();
	ctlwizchip(CW_GET_PHYLINK, (void*) &Phy_TCP_IP); // gets physical status of the TCPIP

	if(Phy_TCP_IP==PHY_LINK_OFF)
	{
		Set_state(Initilisation_State);
	}
	else if(Phy_TCP_IP==PHY_LINK_ON)
	{
		Refresh_Watchdog();
		Ethernet_Connect();
		send(0, (uint8_t *)SYS_INIT_CMD,strlen(SYS_INIT_CMD));
		Set_event(Reset_Event);
	}
}

void Reset_State_Handler()
{
	Set_state(Reset_State);
	Reset_event();
	//Reset the RingBuffers
	RingInit(&WR_Ring,&WR_Samples[0],BUFFERSIZE,sizeof(buff_size));
	RingInit(&WL_Ring,&WL_Samples[0],BUFFERSIZE,sizeof(buff_size));
	RingInit(&FCT_Ring,&FCT_Samples[0],BUFFERSIZE,sizeof(buff_size));
	//Reset the Counts
	WR_Counts=0;
	WL_Counts=0;
	FCT_Counts=0;
	//Reset the 32 bit timer 2
	Timer2_Stop(); //Timer Stopped
	Timer6_Stop();

	Timer2_DeInitilized();//Timer DeInitilized

	Timer2_Initilized(); //Timer Initialized
	Entry_flag=0;
	Lt_Rt_flag=0;
	Rt_Lt_flag=0;
	Set_event(Idle_Event);
}

void Idle_State_Handler()
{
	//Set state to idle state
	Set_state(Idle_State);


	//send(0, (buff_size *)" Idle,",strlen(" Idle,"));
	//reset the event
	Reset_event();
	//
}

void WRSide_Train_Presence_State_Handler()
{
	if(Get_state!=WRSide_Train_Presence_State)
	{
		//set state to WRSide Train Presence state
		Set_state(WRSide_Train_Presence_State);

		//send(0, (buff_size *)" WRSide,",strlen(" WRSide,"));
		//reset the event
		Reset_event();
	}
	//tasks that need to be done on each WR trigger
}

void WLSide_Train_Presence_State_Handler()
{
	if(Get_state!=WLSide_Train_Presence_State)
	{
		Set_state(WLSide_Train_Presence_State);

		//send(0, (buff_size *)" WLSide,",strlen(" WLSide,"));
		Reset_event();
	}
	//tasks that need to be done on each WL trigger
}

void Train_Exit_State_Handler()
{
	Set_state(Train_Exit_State);

	//send(0, (buff_size *)" Exit,",strlen(" Exit,"));
	Reset_event();
	//shut down the purge and close the shutters
	//set the event to Log Data event
	Set_event(Log_Data_Event);
}

void Log_Data_State_Handler()
{
	Set_state(Log_Data_State);

	//send(0, (buff_size *)" Log,",strlen(" Log,"));
	Reset_event();
	Send_Data();
	Set_event(Reset_Event);
}


