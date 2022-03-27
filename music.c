/*
    music.c
    Functionality for music and SFX playback
    Only 1 note can be played at a time
*/
#include <stdint.h>
#include "stm32l031lib.h"
#include "music.h"

static GPIO_TypeDef *speakerPort;
static uint32_t speakerPin;

// Sets Speaker Port and Pin then sets music and SFX to NULL
void initAudio(GPIO_TypeDef *Port, uint32_t BitNumber)
{
    speakerPort = Port;
    speakerPin = BitNumber;
    playMusic(audioNULL, AUDIO_NULL_SIZE);
    playSFX(audioNULL, AUDIO_NULL_SIZE);
}
// Handles music and SFX playback
void Audio_Handler(void)
{
	static uint32_t soundDuration = 0;
	static uint32_t pitch = 0;
	uint32_t duration = 0;
	uint8_t hasSFX = (SFX.pitches[SFX.pos][0] != 0) || (SFX.pitches[SFX.pos][1] != 0);

	if (soundDuration <= 0)
	{
		// If there is a sfx read, play the sfx otherwise default to playing music in a loop
		if (hasSFX == 1)
		{
			pitch = SFX.pitches[SFX.pos][0];
			duration = SFX.pitches[SFX.pos][1];
			SFX.pos++;
		}
		else
		{
			pitch = music.pitches[music.pos][0];
			duration = music.pitches[music.pos][1];
			music.pos++;
            
			if (music.pos > music.len - 1)
			{
				music.pos = 0;
			}	
		}

		// Set speaker pitch
		if (pitch == 0)
		{
			SysTick->LOAD = 16000;
		}
		else
		{	
			SysTick->LOAD = CPU_FREQ / (2 * pitch);
		}

		// Set speaker play duration
		soundDuration =  (uint32_t)(duration * (CPU_FREQ/1000.0) / SysTick->LOAD);
	}
    else
    {
		soundDuration--;
        if (pitch != 0)
        {
    		speakerPort->ODR = speakerPort->ODR ^ (1 << speakerPin); // Toggle Speaker pin		
        }
    }
}
// Sets music audio to play audio in a loop
void playMusic(const uint32_t(*pitches)[2], uint32_t len)
{
	music.pitches = pitches;
	music.len = len;
	music.pos = 0;
}
// Sets SFX audio to play audio once, pauses music when playing
void playSFX(const uint32_t(*pitches)[2], uint32_t len)
{
	SFX.pitches = pitches;
	SFX.len = len;
	SFX.pos = 0;
}
