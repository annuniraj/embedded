
#pragma once
#ifndef INC_COMMON_H_
#define INC_COMMON_H_



#endif /* INC_COMMON_H_ */

typedef enum {
	NULL_Event,
	Health_Event,
	Reset_Event,
	Idle_Event,
	WRSide_Train_Detect_Event,
	WLSide_Train_Detect_Event,
	Train_Exit_Event,
	Log_Data_Event,
	DCTR_INIT_Event,
	DCTR_EXIT_Event,
	DCTR_OPEN_SHUTTER_Event,
	DCTR_CLOSE_SHUTTER_Event,
	DCTR_TRIGGER_CAMERA_Event,
	DCTR_TRIGGER_CAMERA_LASER_Event,
	DCTR_PULSE_LASER_Event,
	DCTR_PURGE_ON_Event,
	DCTR_PURGE_OFF_Event,
}myEvents;

typedef enum {
	NULL_State,
	Initilisation_State,
	Health_State,
	Reset_State,
	Idle_State,
	WRSide_Train_Presence_State,
	WLSide_Train_Presence_State,
	Train_Exit_State,
	Log_Data_State,
	Direct_Control_State,
}myStates;

