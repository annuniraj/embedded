#include "state_Handler.h"

void Initilisation_State_Handler()
{
	//Set state to Initilisation State
	Set_state(Initilisation_State);
	//Reset the event
	Reset_event();
	//Initilise the TCPIP Connection
	//
	//set event to reset
	Set_event(Reset_Event);
}

void Reset_State_Handler()
{
	//Set state to reset state
	Set_state(Reset_State);
	//Reset the event
	Reset_event();
	//reset the buffers,count variables, and other defined variables
	//set the event to idle
	Set_event(Idle_Event);
}

void Idle_State_Handler()
{
	//Set state to idle state
	Set_state(Idle_State);
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
		//reset the event
		Reset_event();
	}
	//tasks that need to be done on each WL trigger
}

void Train_Exit_State_Handler()
{
	//Set state to Train Exit state
	Set_state(Train_Exit_State);
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
	//reset the event
	Reset_event();
	//send the data over TCPIP
	//set the event to reset event
	Set_event(Reset_Event);
}
