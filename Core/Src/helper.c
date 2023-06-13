#include"helper.h"

void trigger_camera(uint32_t delay_milliseconds)
{
}

void pulse_laser(uint32_t delay_milliseconds)
{
}

void trigger_camera_laser(uint32_t delay_milliseconds)
{
}

void purge_on()
{
}

void purge_off()
{
}

void cycle_purge(uint32_t delay_milliseconds)
{
	purge_on();
	HAL_Delay(delay_milliseconds);
	purge_off();
}

void loop(void(*f)(uint32_t), uint8_t cycles, uint32_t delay_milliseconds, uint32_t cycle_delay_milliseconds)
{
	for (uint8_t i = 0; i < cycles; i++)
	{
		(*f)(delay_milliseconds);
		HAL_Delay(cycle_delay_milliseconds);
	}

}
