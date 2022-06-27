/*
 * event.c
 *
 *  Created on: Jun 24, 2022
 *      Author: Dhruv
 */
#include"common.h"
#include"event.h"

struct EventStruct test_Events = {NULL_Event,NULL_Event};

myEvents Get_event()
{

	return test_Events.Next_Event;
}

void Set_event(myEvents N_E)
{
	test_Events.Next_Event = N_E;
}



void Reset_event()
{
	test_Events.Next_Event=NULL_Event;
}
