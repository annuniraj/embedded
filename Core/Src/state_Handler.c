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

 uint8_t Recv_Cmd[2048];
 uint8_t Abox_Ready[2048] = "ACK_PING1";
 extern uint8_t remotePort;
 extern uint32_t PortStatus;
 extern uint8_t remote;

void Initilisation_State_Handler()
{
	Set_state(Initilisation_State);
	Reset_event();
	//Initialize the TCPIP Connection
	Init_Ethernet();
	//Check the physical Connection of TCP IP
	ctlwizchip(CW_GET_PHYLINK, (void*) &Phy_TCP_IP); // gets physical status of the TCPIP

	if(Phy_TCP_IP==PHY_LINK_OFF)
	{
		//Save the status in the flash memory with date and time stamp+++++++++++++++++++++
		Set_state(Initilisation_State);
	}
	else if(Phy_TCP_IP==PHY_LINK_ON)
	{
		HAL_Delay(100);
		//Connect the TCP iP Connection
		Refresh_Watchdog();
		Ethernet_Connect();
		HAL_Delay(100);

		send(0, (uint8_t *)SYS_INIT_CMD,strlen(SYS_INIT_CMD));

		while(strcmp(Recv_Cmd,Abox_Ready)!=0)
		{
			uint32_t remoteee;
			memset(Recv_Cmd,0,sizeof Recv_Cmd);
			PortStatus=recv(0, Recv_Cmd,2048);
			HAL_Delay(100);
	  		ctlwizchip(CW_GET_PHYLINK, (void*) &Phy_TCP_IP);
	  		if(PortStatus==SOCKERR_SOCKSTATUS)
	  		{
	  			break;
	  		}
	  		if(Phy_TCP_IP==PHY_LINK_OFF)
	  		{
	  			break;
	  		}
		}
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
	memset(Recv_Cmd,0,sizeof Recv_Cmd);
	send(0, (uint8_t *)"RESET",strlen("RESET"));
	//set the event to idle
	Set_event(Idle_Event);
}

void Idle_State_Handler()
{
	//Set state to idle state
	Set_state(Idle_State);


	send(0, (buff_size *)" Idle,",strlen(" Idle,"));
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
		//set state to WLSide Train Presence state
		Set_state(WLSide_Train_Presence_State);

		//send(0, (buff_size *)" WLSide,",strlen(" WLSide,"));
		//reset the event
		Reset_event();
	}
	//tasks that need to be done on each WL trigger
}

void Train_Exit_State_Handler()
{
	//Set state to Train Exit state
	Set_state(Train_Exit_State);

	//send(0, (buff_size *)" Exit,",strlen(" Exit,"));
	//reset the event
	Reset_event();
	//shut down the purge and close the shutters
	//set the event to Log Data event
	Set_event(Log_Data_Event);
}

void Log_Data_State_Handler()
{
	//Set state to Log Data state
	Set_state(Log_Data_State);

	//send(0, (buff_size *)" Log,",strlen(" Log,"));
	//reset the event
	Reset_event();
	//send the data over TCPIP
	Send_Data();
	//set the event to reset event
	Set_event(Reset_Event);
}


