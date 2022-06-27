/*
 * state.c
 *
 *  Created on: Jun 24, 2022
 *      Author: Dhruv
 */

#include"state.h"


struct StatesStruct test_states={Initilisation_State, NULL_State}; // current state defined as initilisation state, next state defined as NULL state

myStates Read_state()
{
	return	 test_states.Current_State;
}

void Set_state(myStates N_S)
{
test_states.Current_State = N_S;
}
