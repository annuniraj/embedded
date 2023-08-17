#pragma once

#include "state.h"
#include "event.h"

#include "TCP_IP.h"
#include "ring.h"
#include "Interrupt_Services.h"
#include "Save_Data.h"
#include "main.h"

#ifndef INC_STATE_HANDLER_H_
#define INC_STATE_HANDLER_H_



#endif /* INC_STATE_HANDLER_H_ */

void Initilisation_State_Handler();
void Health_State_Handler();
void Reset_State_Handler();
void Idle_State_Handler();
void WRSide_Train_Presence_State_Handler();
void WLSide_Train_Presence_State_Handler();
void Train_Exit_State_Handler();
void Log_Data_State_Handler();
void Direct_Control_State_Handler();
