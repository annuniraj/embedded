/*
 * helper.h
 *
 *  Created on: Jul 21, 2022
 *      Author: user
 */
#pragma once
#ifndef INC_HELPER_H_
#define INC_HELPER_H_
#include"main.h"
void trigger_camera(uint32_t delay_milliseconds);
void pulse_laser(uint32_t delay_milliseconds);
void trigger_camera_laser(uint32_t delay_milliseconds);
void purge_on();
void purge_off();
void cycle_purge(uint32_t delay_milliseconds);
void loop(void (*f)(uint32_t), uint8_t cycles, uint32_t delay_milliseconds, uint32_t cycle_delay_milliseconds); // now now i don't know if this will work
#endif /* INC_HELPER_H_ */
