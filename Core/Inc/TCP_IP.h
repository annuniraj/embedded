#pragma once
#ifndef INC_TCP_IP_H_
#define INC_TCP_IP_H_


#endif /* INC_TCP_IP_H_ */

#define PORT_ADDR		9099
#define PING_CMD		"PING"
#define PING_ACK_CMD	"ACK_PING"
#define GRAB_START_CMD	"GRABSTART"
#define GRAB_STOP_CMD	"GRABSTOP"
#define LOG_START_CMD	"LOGSTART"
#define LOG_STOP_CMD	"LOGSTOP"

#include "wizchip_conf.h"
#include "socket.h"

uint8_t Phy_TCP_IP;
uint8_t Receive_Buffer[255];

void Init_Ethernet(void);
void cs_sel(void);
void cs_desel(void);

void Ethernet_Connect(void);
void Refresh_Watchdog(void);
