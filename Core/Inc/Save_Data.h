#ifndef INC_SAVE_DATA_H_
#define INC_SAVE_DATA_H_



#endif /* INC_SAVE_DATA_H_ */

#include <stdlib.h>
#include "Interrupt_Services.h"



extern uint8_t WR_Roller,
		WL_Roller,
		FCT_Roller;

extern buff_size	WR_Ring_Unit,
			WL_Ring_Unit,
			FCT_Ring_Unit;

extern unsigned char*	WR_Ring_Bulletin[10],
				WL_Ring_Bulletin[10],
				FCT_Ring_Bulletin[10],
				WR_Count_Bulletin[10],
				WL_Count_Bulletin[10],
				FCT_Count_Bulletin[10];

void Send_Data(void);
void Send_WR_Samples(void);
void Send_WL_Samples(void);
void Send_FCT_Samples(void);
