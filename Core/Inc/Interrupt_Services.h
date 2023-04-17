/*
 * Inturrpt_Services.h
 *
 *  Created on: 27-May-2022
 *      Author: Anil
 */

#ifndef INC_INTERRUPT_SERVICES_H_
#define INC_INTERRUPT_SERVICES_H_

#endif /* INC_INTERRUPT_SERVICES_H_ */

#include <stdio.h>
#include <string.h>
#include "TCP_IP.h"
#include "ring.h"

extern unsigned long int	WR_Counts, // Wheel Right Counts
					FCT_Counts,// Fraucher Central trigger Counts
					WL_Counts; // Wheel Left Counts

extern buff_size			WR_Instant,
					WL_Instant,
					FCT_Instant;

extern uint16_t			Lt_Rt_flag,
					Rt_Lt_flag,
					Entry_flag;


void Lan_Interrupt_Service(void);
void WR_Interrupt_Service(void);
void FCT_Interrupt_Service(void);
void WL_Interrupt_Service(void);
void Manual_delay(void);
void Save_delay(void);
