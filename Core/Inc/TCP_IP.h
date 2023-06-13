#pragma once
#ifndef INC_TCP_IP_H_
#define INC_TCP_IP_H_


#endif /* INC_TCP_IP_H_ */

#define PORT_ADDR			6656
#define PING_CMD			"MCUPING#2"
#define PING_ACK_CMD		"ACK@MCUPING"

#define SYS_INIT_CMD		"SYSINIT#1"
#define ABOX_READY_CMD		"AboxReady"
#define ABOX_NOT_READY_CMD	"ABOXNOTREADY"
#define INIT_CMD			"INIT#1"
#define GRAB_START_CMD		"GRABSTART#1"
#define GRAB_STOP_CMD		"GRABSTOP#1"
#define LOG_START_CMD		"LOGSTART#1"
#define LOG_WR_CMD			"LOGNEWFILE@WR#1"
#define LOG_WL_CMD			"LOGNEWFILE@WL#1"
#define LOG_FCT_CMD			"LOGNEWFILE@FCT#1"

#define LOG_WRITE_CMD		"LOGWRITE@"
#define LOG_END_WRITE_CMD	"LOGENDFILE#1"
#define LOG_STOP_CMD		"LOGSTOP#1"


//DIRECT CONTROL MODE
#define DCTR_INIT					"DIRECTCONTROLINIT"
#define DCTR_EXIT 					"DIRECTCONTROLEXIT"
#define DCTR_OPEN_SHUTTER 			"DIRECTCONTROLOPENSHUTTER"
#define DCTR_CLOSE_SHUTTER 			"DIRECTCONTROLCLOSESHUTTER"
#define DCTR_TRIGGER_CAMERA 		"DIRECTCONTROLTRIGGERCAMERA"
#define DCTR_TRIGGER_CAMERA_LASER 	"DIRECTCONTROLTRIGGERCAMERALASER"
#define DCTR_PULSE_LASER 			"DIRECTCONTROLPULSELASER"
#define DCTR_PURGE_ON 				"DIRECTCONTROLPURGEON"
#define DCTR_PURGE_OFF 				"DIRECTCONTROLPURGEOFF"

#include "wizchip_conf.h"
#include "socket.h"

extern uint8_t Phy_TCP_IP;
extern uint8_t Receive_Buffer[255]; // defined in Interrupt_Service.c
extern uint8_t Connect_Reply;



void Init_Ethernet(void);
void cs_sel(void);
void cs_desel(void);

void Ethernet_Connect(void);
void Refresh_Watchdog(void);
