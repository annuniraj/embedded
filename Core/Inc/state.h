#pragma once
#ifndef INC_STATE_H_
#define INC_STATE_H_

#endif /* INC_STATE_H_ */

#include "common.h"

struct StatesStruct
{

	myStates Current_State,Next_State;
};

extern struct StatesStruct test_states;

myStates Read_state();
void Set_state(myStates N_S);
