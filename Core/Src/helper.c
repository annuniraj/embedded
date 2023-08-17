#include"helper.h"
#include"Interrupt_Services.h"

void trigger_camera(uint32_t delay_milliseconds)
{
	HAL_GPIO_WritePin(GPIOA, CA_TRIG_LED_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, CA_OP_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, CA_OP1_Pin, GPIO_PIN_SET);
	//HAL_Delay(200);

	//Camera OFF
	//Manual_delay();
	Manual_delay();
	HAL_GPIO_WritePin(GPIOA, CA_TRIG_LED_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, CA_OP_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, CA_OP1_Pin, GPIO_PIN_RESET);
	Manual_delay();
}

void pulse_laser(uint32_t delay_milliseconds)
{
	HAL_GPIO_WritePin(GPIOA, LA_TRIG_LED_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, LA_OP_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LA_OP1_Pin, GPIO_PIN_RESET);
	Manual_delay();
	Manual_delay();
	Manual_delay();
	HAL_GPIO_WritePin(GPIOA, LA_TRIG_LED_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, LA_OP_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LA_OP1_Pin, GPIO_PIN_SET);
}

void trigger_camera_laser(uint32_t delay_milliseconds)
{
	//Laser ON
	HAL_GPIO_WritePin(GPIOA, LA_TRIG_LED_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, LA_OP_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LA_OP1_Pin, GPIO_PIN_RESET);
	Manual_delay();

	//Camera ON
	HAL_GPIO_WritePin(GPIOA, CA_TRIG_LED_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, CA_OP_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, CA_OP1_Pin, GPIO_PIN_SET);
	//HAL_Delay(200);

	//Camera OFF
	//Manual_delay();
	Manual_delay();
	HAL_GPIO_WritePin(GPIOA, CA_TRIG_LED_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, CA_OP_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, CA_OP1_Pin, GPIO_PIN_RESET);
	Manual_delay();

	//Laser OFF
	HAL_GPIO_WritePin(GPIOA, LA_TRIG_LED_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, LA_OP_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LA_OP1_Pin, GPIO_PIN_SET);
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
