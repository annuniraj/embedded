#pragma once
#ifndef INC_TCP_IP_H_
#define INC_TCP_IP_H_


#endif /* INC_TCP_IP_H_ */

#define PORT_ADDR		9099
#define GRAB_CMD		"GRABSTART"
#define LOG_START_CMD	"LOGSTART"
#define LOG_STOP_CMD	"LOGSTOP"

#include "wizchip_conf.h"
#include "socket.h"



void Init_Ethernet(void);
void cs_sel(void);
void cs_desel(void);

void Ethernet_Connect(void);
void Refresh_Watchdog(void);
