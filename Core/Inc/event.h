#pragma once
#ifndef INC_EVENT_H_
#define INC_EVENT_H_

#endif /* INC_EVENT_H_ */
#include "common.h"

struct EventStruct
{

	myEvents Current_Event,Next_Event;
};

extern struct EventStruct test_Events;

myEvents Get_event();
void Set_event(myEvents N_E);
void Reset_event();

