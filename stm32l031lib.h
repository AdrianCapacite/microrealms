/*
    Microprocessors microrealm - stm32l031lib
    Pin ins:
        Keypad:
            Keypad pin:  C4  C3  C2  C1  R1  R2  R3  R4
            Pin label:   D2  D3  D4  D5  D6  D9  D10 D11
            Actual Pin:  A12 B0  B7  B6  B1  A8  A11 B5
    Pin outs:
        Health LED: A0 -> A0
        Status RGB LED:
            LED pin:    Red   Green Blue
            Pin label:  A1    A2    A3  
            Actual Pin: A1    A3    A4
        Speaker: A4 -> A5
    Author: Adrian Thomas Capacite
    Date: 14 / 03 / 2022
*/

#ifndef __stm32l031lib_h
#define __stm32l031lib_h
#include <stdint.h>
#include <stm32l031xx.h>
#define enable_interrupts() __asm(" cpsie i ")
#define disable_interrupts() __asm(" cpsie d ")
#define CPU_FREQ 16000000
// Pin constants
#define KEYPAD_SIZE 4
#define RGB_PIN_COUNT 3

// GPIO_TypeDef *Port;
// uint32_t BitNumber;
struct GPIO_Pin
{
    GPIO_TypeDef *Port;
    uint32_t BitNumber;
};

// struct GPIO_Pin row[4];
// struct GPIO_Pin col[4];
struct Pin_Matrix
{
    struct GPIO_Pin row[KEYPAD_SIZE];
    struct GPIO_Pin col[KEYPAD_SIZE];
};
struct Pin_RGBLED
{
    struct GPIO_Pin red;
    struct GPIO_Pin green;
    struct GPIO_Pin blue;
};

void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode);
void delay(volatile uint32_t dly);
void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber);

void setPinLow(GPIO_TypeDef *Port, uint32_t BitNumber);
void setPinHigh(GPIO_TypeDef *Port, uint32_t BitNumber);
uint32_t readPin(GPIO_TypeDef *Port, uint32_t BitNumber);

void initClock(void);
void initSerial(void);
void eputchar(char c);
char egetchar(void);
void eputs(const char *String);
void printDecimal(uint32_t Value);
void printBin(uint32_t Value);
void printHex(uint32_t Value);

void initPins(void);

void initKeypad(struct Pin_Matrix pins);
uint32_t getKeypadValue(struct Pin_Matrix pins);

void initRGBLED(struct Pin_RGBLED);
void setRGBLED(uint32_t RGB, struct Pin_RGBLED pins);

// Pin values constants
const static struct Pin_Matrix keypadPins = {
    // Rows
    {
        {GPIOB,1},
        {GPIOA,8},
        {GPIOA,11},
        {GPIOB,5}
    },
    // Cols
    {
        {GPIOB,6},
        {GPIOB,7},
        {GPIOB,0},
        {GPIOA,12}
    }
};
const static struct GPIO_Pin ledHeartPin = {GPIOA,0};
const static struct Pin_RGBLED ledStatusPins = {
    {GPIOA,1},{GPIOA,3},{GPIOA,4}
    };
const static struct GPIO_Pin speakerPin = {GPIOA,5};
#endif
