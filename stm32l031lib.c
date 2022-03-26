#include <stdint.h>
#include <stm32l031xx.h>
#include "stm32l031lib.h"

// This function writes the given Mode bits to the appropriate location for
// the given BitNumber in the Port specified.  It leaves other bits unchanged
// Mode values:
// 0 : digital input
// 1 : digital output
// 2 : Alternative function
// 3 : Analog input
void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode)
{
	uint32_t mode_value = Port->MODER; // read current value of Mode register 
	Mode = Mode << (2 * BitNumber);    // There are two Mode bits per port bit so need to shift
																	   // the mask for Mode up to the proper location
	mode_value = mode_value & ~(3u << (BitNumber * 2)); // Clear out old mode bits
	mode_value = mode_value | Mode; // set new bits
	Port->MODER = mode_value; // write back to port mode register
}
void Delay_Handler(void)
{
	if (delayDuration > 0)
	{
		delayDuration--;
	}
}
// Delay in ms
// Makes adjustments based on SysTick->LOAD, even when it changes mid delay
void delay(volatile uint32_t dly)
{
	while (dly > 100) 
	{
		delayDuration = (uint32_t)(100 * (CPU_FREQ/1000.0) / SysTick->LOAD);
		while(delayDuration>0);
		dly -= 100;
	}
	delayDuration = (uint32_t)((dly%100) * (CPU_FREQ/1000.0) / SysTick->LOAD);
	while(delayDuration>0);
}
void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber)
{
		Port->PUPDR = Port->PUPDR & ~(3u << BitNumber*2); // clear pull-up bits
		Port->PUPDR = Port->PUPDR | (1u << BitNumber*2); //  set pull-up bit
}

// Code added by Adrian Capcite

// Set digital pin low
void setPinLow(GPIO_TypeDef *Port, uint32_t BitNumber)
{
	Port->ODR = Port->ODR & ~(1u << BitNumber);
}
// Set digital pin high
void setPinHigh(GPIO_TypeDef *Port, uint32_t BitNumber)
{	
	Port->ODR = Port->ODR | (1u << BitNumber);
}
// Outputs true if pin is low
uint32_t readPin(GPIO_TypeDef *Port, uint32_t BitNumber)
{
		return ((Port->IDR & (1u << BitNumber)) != 0);
}



// Initialises the ADC
void ADCBegin()
{
	RCC->APB2ENR |= (1u << 9); // Turn on ADC 
	RCC->IOPENR |= 1; // enable GPIOA
	pinMode(GPIOA,7,3); // Make GPIOA_7 an analogue input

	ADC1->CR = 0; // disable ADC before making changes
	ADC1->CR |= (1u << 28); // turn on the voltage regulator
	ADC1->CR |= (1u << 31); // start calibration
	while ( (ADC1->CR & (1u << 31)) != 0); // Wait for calibration to complete.
	ADC1->CHSELR = (1 << 7); // select channel7
	ADC1->CR |= 1; // enable the ADC
	
}

// Reads value from ADC
uint16_t ADCRead(void)
{
	ADC1->CR |= (1 << 2); // start a conversion
	while ( (ADC1->CR & (1 << 2)) != 0); // Wait for conversion to complete.
	return (uint16_t)ADC1->DR;
}


// END code added by Adrian Capacite

void initClock()
{
	/* This function switches the STM32L031's clock to its 16MHz MSI clock */
	RCC->CR &= (1u << 24);
	RCC->CR |= 1; // Turn on HSI16
	while ( (RCC->CR & (1 <<2)) == 0); // wait for HSI to be ready
	// set HSI16 as the system clock source
	RCC->CFGR |= 1;
	
	SysTick->LOAD = 16000;   // 16MHz / 16000 = 1kHz
	SysTick->CTRL = 7;       // enable systick counting and 
}

void initSerial()
{
	/* On the nucleo board, TX is on PA2 while RX is on PA15 */
	initClock();
	RCC->IOPENR |= 1; // enable GPIOA
	RCC->APB1ENR |= (1 << 17); // enable USART2
	pinMode(GPIOA,2,2); // enable alternate function on PA2
	pinMode(GPIOA,15,2); // enable alternate function on PA15
	// AF4 = USART2 TX on PA2
	GPIOA->AFR[0] &= 0xfffff0ff;
	GPIOA->AFR[0] |= (4 << 8);
	// AF4 = USART2 RX on PA2
	GPIOA->AFR[1] &= 0x0fffffff;
	GPIOA->AFR[1] |= (4 << 28);
	USART2->CR1 = 0; // disable before configuration
	USART2->CR3 |= (1 << 12); // disable overrun detection
	USART2->BRR = 16000000/9600; // assuming 16MHz clock and 9600 bps data rate
	USART2->CR1 |= (1 << 2) + (1 << 3); // enable Transmistter and receiver
	USART2->CR1 |= 1; // enable the UART

}
void eputchar(char c)
{
	while( (USART2->ISR & (1 << 6)) == 0); // wait for any ongoing
	// transmission to finish
	USART2->TDR = c;
}
char egetchar()
{
	while( (USART2->ISR & (1 << 5)) == 0); // wait for a character
	return (char)USART2->RDR;
}
void eputs(const char *String)
{
	while(*String) // keep printing until a NULL is found
	{
		eputchar(*String);
		String++;
	}
}

// ModifiedPrints decimal number to serial, removing leading 0s
void printDecimal(uint32_t Value)
{
	char DecimalString[11]; // a 32 bit value can go up to about 4 billion: That's 10 digits plus a null character
	DecimalString[10] = 0;
	int index = 9;
	
	do
	{
		DecimalString[index]=(Value % 10) + '0';
		Value = Value / 10;
		
		if (Value == 0)
		{
			break;
		}
		
		index--;
	} while (index >= 0);
	eputs(&DecimalString[index]);
}
// Added code by Adrian Capacite //

// Init pins
void initPins(void)
{
	RCC->IOPENR |= (1<<0); // Enable Port A
	RCC->IOPENR |= (1<<1); // Enable Port B

	initKeypad(c_keypadPins);
	initRGBLED(c_ledStatusPins);
	pinMode(c_ledHeartPin.Port, c_ledHeartPin.BitNumber, 1); // Init speaker pin
	pinMode(c_speakerPin.Port, c_speakerPin.BitNumber, 1); // Init speaker pin
}

// Initialises keypad pins
void initKeypad(struct Pin_Matrix pins)
{
	for (int i = 0; i < KEYPAD_SIZE; i++)
	{
		pinMode(pins.row[i].Port, pins.row[i].BitNumber, 1);
		pinMode(pins.col[i].Port, pins.col[i].BitNumber, 0);
		enablePullUp(pins.col[i].Port, pins.col[i].BitNumber);
	}
}
// Reads 16 key keypad
uint8_t getKeypadValue(struct Pin_Matrix pins)
{	
	static uint8_t lastKeyVal = 0;
	uint8_t keyVal = 0;

	// Scan keypad rows and read columns
	do 
	{
		for (uint8_t i = 0; i < KEYPAD_SIZE; i++)
		{
			// Set all rows high and current low
			for (uint8_t j = 0; j < KEYPAD_SIZE; j++)
			{
				setPinHigh(pins.row[j].Port,pins.row[j].BitNumber);
			}
			setPinLow(pins.row[i].Port,pins.row[i].BitNumber);
			// Check each col if they are low
			for (uint8_t j = 0; j < KEYPAD_SIZE; j++)
			{
				if(readPin(pins.col[j].Port, pins.col[j].BitNumber) == 0)
				{
					keyVal = keyVal | (1u << i) | (1u << (4u + j));
				}
			}
		}
		if (keyVal == 0) 
		{
			// Limit polling of keypad
			delay(125);
			lastKeyVal = 0;
		}
	} while (keyVal == 0);

	// If user is still holding key down, return 0
	if (keyVal == lastKeyVal)
	{
		return 0;
	}
	lastKeyVal = keyVal;
	return keyVal;
}

// Initialise RGB LED
void initRGBLED(struct Pin_RGBLED pins)
{
	pinMode(pins.red.Port, pins.red.BitNumber, 1);
	pinMode(pins.green.Port, pins.green.BitNumber, 1);
	pinMode(pins.blue.Port, pins.blue.BitNumber, 1);
}
// Sets RGB LED value
void setRGBLED(uint32_t RGB, struct Pin_RGBLED pins)
{
	// Red
	if ((RGB & 0x0000ff) == 0x0000ff)
	{
		setPinHigh(pins.red.Port, pins.red.BitNumber);
	}
	else
	{
		setPinLow(pins.red.Port, pins.red.BitNumber);
	}
	// Green
	if ((RGB & 0x00ff00) == 0x00ff00)
	{
		setPinHigh(pins.green.Port, pins.green.BitNumber);
	}
	else
	{
		setPinLow(pins.green.Port, pins.green.BitNumber);
	}
	// Blue
	if ((RGB & 0xff0000) == 0xff0000)
	{
		setPinHigh(pins.blue.Port, pins.blue.BitNumber);
	}
	else
	{
		setPinLow(pins.blue.Port, pins.blue.BitNumber);
	}
}
// END Added code by Adrian Capacite
