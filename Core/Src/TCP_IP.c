/*
 * TCP_IP.c
 *
 *  Created on: 25-May-2022
 *      Author: Anil
 */
#include "main.h"
#include "TCP_IP.h"

uint8_t Connect_Reply;
uint8_t Phy_TCP_IP;
uint8_t  server_Add[4] = {192,168,1,111}; // Change in main.c line 203

//uint8_t  Connect_Reply;
uint8_t  Sock_Rx_Flag;
uint8_t  Ethernet_Rx_DataBuff[2048];
uint8_t  IntStatus;
uint8_t  Sock_Rx_Flag;
uint8_t  Sock_Disconnect_Flag;

void cs_sel(void)
{
	HAL_GPIO_WritePin(LAN_CS_GPIO_Port, LAN_CS_Pin, GPIO_PIN_RESET); //CS LOW
}

void cs_desel(void)
{
	HAL_GPIO_WritePin(LAN_CS_GPIO_Port, LAN_CS_Pin, GPIO_PIN_SET); //CS HIGH
}


void Init_Ethernet(void)
{
	uint8_t bufSize[] = {2, 2, 2, 2};

	reg_wizchip_cs_cbfunc(cs_sel, cs_desel);
	reg_wizchip_spi_cbfunc(spi_rb, spi_wb);

	wizchip_init(bufSize, bufSize);
	wiz_NetInfo netInfo = { .mac = {0x00, 0x08, 0xdc, 0xab, 0xcd, 0xef}, // Mac address
	 .ip = {192, 168, 1, 204},    // IP address
	 .sn = {255, 255, 255, 0},    // Subnet mask
	 .gw = {192, 168, 1, 1}};    // Gateway address

	wizchip_setnetinfo(&netInfo);
	wizchip_getnetinfo(&netInfo);

	setSn_IMR(0, 0x06);
	WIZCHIP_WRITE(SIMR,0x01);
}

void Ethernet_Connect(void)
{
	Init_Ethernet();


	while(Connect_Reply !=SOCK_OK)
	{
		socket(0, Sn_MR_TCP, PORT_ADDR, SF_TCP_NODELAY);
		Refresh_Watchdog();
		Connect_Reply = connect(0,server_Add,PORT_ADDR);
	}

	if(Connect_Reply == 1)
	{
		Connect_Reply = 0;
	}
	HAL_Delay(500);
	Refresh_Watchdog();

}

void Refresh_Watchdog(void)
{
	IWDG->KR  = 0x0000AAAA;
}
