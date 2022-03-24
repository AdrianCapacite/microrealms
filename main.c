#include "stm32l031lib.h"
#include "realm.h"
#include "music.h"

void SysTick_Handler(void);

int main()
{
	initPins();
	initClock();
	initSerial();
	ADCBegin();
	initAudio(c_speakerPin.Port, c_speakerPin.BitNumber);

	uint32_t test = random(ADCRead()%100); // Start to value of adc of random so next random is truely random
	delay(100);
	
	printDecimal(test);
	eputchar('\t');
	printDecimal(ADCRead());
	eputs("\r\n");
	setRGBLED(0xffffff, c_ledStatusPins);
	setPinHigh(c_ledHeartPin.Port,c_ledHeartPin.BitNumber);
	while(1)
	{
		runGame();
	}
}

void SysTick_Handler(void)
{
	static int counter = 0;
	Audio_Handler();
	Delay_Handler();
	if (counter % 100 == 0)
	{
		eputchar('\t');
		printDecimal(ADCRead());
		eputs("\r\n");
	}
	
	counter++;
}
