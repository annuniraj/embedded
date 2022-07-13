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
#include "TCP_IP.h"
#include "ring.h"

unsigned long int	WR_Counts, // Wheel Right Counts
					FCT_Counts,// Fraucher Central trigger Counts
					WL_Counts; // Wheel Left Counts

buff_size			WR_Instant,
					WL_Instant,
					TR_Instant,
					TL_Instant;

void Lan_Interrupt_Service(void);
void WR_Interrupt_Service(void);
void TR_Interrupt_Service(void);
void WL_Interrupt_Service(void);
void TL_Interrupt_Service(void);
void Manual_delay(void);