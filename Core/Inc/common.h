
#pragma once
#ifndef INC_COMMON_H_
#define INC_COMMON_H_



#endif /* INC_COMMON_H_ */

typedef enum {
	NULL_Event,
	Reset_Event,
	Idle_Event,
	WRSide_Train_Detect_Event,
	WLSide_Train_Detect_Event,
	Train_Exit_Event,
	Log_Data_Event,
}myEvents;

typedef enum {
	NULL_State,
	Initilisation_State,
	Reset_State,
	Idle_State,
	WRSide_Train_Presence_State,
	WLSide_Train_Presence_State,
	Train_Exit_State,
	Log_Data_State,
}myStates;

