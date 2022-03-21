#include "stm32l031lib.h"
#include "realm.h"

void SysTick_Handler(void);

int main()
{
	initPins();
	initClock();
	initSerial();
	while(1)
	{
		//runGame();
		printDecimal(getKeypadValue(keypadPins));
		eputs("\r\n");
	}
}

void SysTick_Handler(void)
{

}
