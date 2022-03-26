#include "stm32l031lib.h"
#include "realm.h"
#include "music.h"

void SysTick_Handler(void);

int main()
{
	initPins();
	initClock();
	initSerial();
	initAudio(c_speakerPin.Port, c_speakerPin.BitNumber);
	
	{
		runGame();
	}
}

void SysTick_Handler(void)
{
	Audio_Handler();
	Delay_Handler();
	Health_Display_Handler();
}
