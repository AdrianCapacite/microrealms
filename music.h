#ifndef __music_h
#define __music_h
#include <stdint.h>
#include "stm32l031lib.h"

typedef struct 
{
	const uint32_t (*pitches)[2];
	uint32_t len;
	uint32_t pos;
} audioInst;

static audioInst music;
static audioInst SFX;

void initAudio(GPIO_TypeDef *Port, uint32_t BitNumber);
void Audio_Handler(void);
void playMusic(const uint32_t(*pitches)[2], uint32_t len);
void playSFX(const uint32_t(*pitches)[2], uint32_t len);

static GPIO_TypeDef *speakerPort;
static uint32_t speakerPin;

// Music note values below -
// Rounded musical note frequencies
// 'S' is used in place of # (sharp) as that has a special meaning in C
// DS2_Eb2 is D#2 / Eb2 
#define C0	16
#define CS0_Db0	17
#define D0	18
#define DS0_Eb0	19
#define E0	21
#define F0	22
#define FS0_Gb0	23
#define G0	25
#define GS0_Ab0	26
#define A0	28
#define AS0_Bb0	29
#define B0	31
#define C1	33
#define CS1_Db1	35
#define D1	37
#define DS1_Eb1	39
#define E1	41
#define F1	44
#define FS1_Gb1	46
#define G1	49
#define GS1_Ab1	52
#define A1	55
#define AS1_Bb1	58
#define B1	62
#define C2	65
#define CS2_Db2	69
#define D2	73
#define DS2_Eb2	78
#define E2	82
#define F2	87
#define FS2_Gb2	93
#define G2	98
#define GS2_Ab2	104
#define A2	110
#define AS2_Bb2	117
#define B2	123
#define C3	131
#define CS3_Db3	139
#define D3	147
#define DS3_Eb3	156
#define E3	165
#define F3	175
#define FS3_Gb3	185
#define G3	196
#define GS3_Ab3	208
#define A3	220
#define AS3_Bb3	233
#define B3	247
#define C4	262
#define CS4_Db4	277
#define D4	294
#define DS4_Eb4	311
#define E4	330
#define F4	349
#define FS4_Gb4	370
#define G4	392
#define GS4_Ab4	415
#define A4	440
#define AS4_Bb4	466
#define B4	494
#define C5	523
#define CS5_Db5	554
#define D5	587
#define DS5_Eb5	622
#define E5	659
#define F5	698
#define FS5_Gb5	740
#define G5	784
#define GS5_Ab5	831
#define A5	880
#define AS5_Bb5	932
#define B5	988
#define C6	1047
#define CS6_Db6	1109
#define D6	1175
#define DS6_Eb6	1245
#define E6	1319
#define F6	1397
#define FS6_Gb6	1480
#define G6	1568
#define GS6_Ab6	1661
#define A6	1760
#define AS6_Bb6	1865
#define B6	1976
#define C7	2093
#define CS7_Db7	2217
#define D7	2349
#define DS7_Eb7	2489
#define E7	2637
#define F7	2794
#define FS7_Gb7	2960
#define G7	3136
#define GS7_Ab7	3322
#define A7	3520
#define AS7_Bb7	3729
#define B7	3951
#define C8	4186
#define CS8_Db8	4435
#define D8	4699
#define DS8_Eb8	4978
#define E8	5274
#define F8	5588
#define FS8_Gb8	5920
#define G8	6272
#define GS8_Ab8	6645
#define A8	7040
#define AS8_Bb8	7459
#define B8	7902

// Audio constants here

#define AUDIO_NULL_SIZE 1
static const uint32_t audioNULL[AUDIO_NULL_SIZE][2] = {{0,0}};

// ==== SFX here ====
// == UI sfx ==
// Generic beep
#define SFX_BEEP_SIZE 4
static const uint32_t SFXBeep[SFX_BEEP_SIZE][2] = {
    {0,100},{C3,100},{0,100},{0,0}
    }; 
#define SFX_BEEP_HIGH_SIZE 4
static const uint32_t SFXBeepHigh[SFX_BEEP_HIGH_SIZE][2] = {
    {0,100},{G6,100},{0,100},{0,0}
    }; 
// Input beep
#define SFX_BEEP_TWO_SIZE 5
static const uint32_t SFXBeepTwo[SFX_BEEP_TWO_SIZE][2] = {
    {0,100},{C3,100},{G6,100},{0,100},{0,0}
    };

// Low health beep
#define SFX_LOW_HEALTH_SIZE 7
static const uint32_t SFXLowHealth[SFX_LOW_HEALTH_SIZE][2] = {
    {0,100},{DS5_Eb5,100},{C5,250},{0,100},{DS5_Eb5,100},{C5,250},{0,0}
    }; 
// Blocked beep
#define SFX_BLOCKED_SIZE 6
static const uint32_t SFXBlocked[SFX_BLOCKED_SIZE][2] = {
    {0,100},{C3,100},{0,10},{C3,250},{0,100},{0,0}
};
// Typing
#define SFX_TYPE_SIZE 5
static const uint32_t SFXType[SFX_TYPE_SIZE][2] = {
    {C2,20},{C2,20},{C2,20},{0,50},{0,0}
};

// == Game outcome sfx ==
// http://steellemon.com/2020/11/19/how-to-play-the-legend-of-zelda-secret-sound/
// Secret Unlock
#define SFX_SECRET_SIZE 11
static const uint32_t SFXSecret[SFX_SECRET_SIZE][2] = {
    {0,500},{G5,250},{FS5_Gb5,250},{DS5_Eb5,250},{A4,250},{GS4_Ab4,250},{E5,250},{GS5_Ab5,250},{C6,500},{0,500},{0,0}
};
// https://musescore.com/crowred/final-fantasy-vi-victory-fanfare
#define SFX_VICTORY_SIZE 13
static const uint32_t SFXVictory[SFX_VICTORY_SIZE][2] = {
    {0,500},{D5,125},{D5,125},{D5,125},{D5,250},{AS4_Bb4,250},{C5,250},{D5,125},{0,125},{C5,62},{D5,750},{0,500},{0,0}
};
// https://virtualpiano.net/music-sheet/reunion-final-fantasy-ii-nobuo-uematsu/
#define SFX_DEFEAT_SIZE 32
static const uint32_t SFXDefeat[SFX_DEFEAT_SIZE][2] = {
    {0,500},{C6,500},{C5,500},{E5,500},{C6,500},{B5,500},{B4,500},{D5,500},{B5,500},{A5,500},{A4,500},{F5,500},{A5,500},{GS5_Ab5,500},{GS4_Ab4,500},{E5,500},{GS4_Ab4,500},{F5,500},{F4,500},{A4,500},{F5,500},{A5,500},{A4,500},{GS5_Ab5,500},{A5,500},{B5,500},{GS4_Ab4,500},{B4,500},{GS4_Ab4,500},{E5,500},{0,500},{0,0}
};

// == Character SFX ==
// Health
#define SFX_HEALTH_SIZE 32
static const uint32_t SFXHealth[SFX_HEALTH_SIZE][2] = {
    {0,100},{C4,100},{D4,100},{E4,100},{D4,100},{E4,100},{F4,100},{E4,100},{F4,100},{G4,100},{F4,100},{G4,100},{A4,100},{G4,100},{A4,100},{B4,100},{A4,100},{B4,100},{C5,100},{B4,100},{C5,100},{0,100},{0,0}
};


// ==== Music here ====
// https://virtualpiano.net/music-sheet/links-memories-the-legend-of-zelda-koji-kondo/
// Links memories
#define MUSIC_TITLE_SIZE 55
static const uint32_t musicTitle[MUSIC_TITLE_SIZE][2] = {
    {G5,500},{C5,500},{C6,500},{C4,500},{G4,500},{AS5_Bb5,500},{G5,500},{C5,500},{C6,500},{C4,500},{G4,500},{AS5_Bb5,500},{D6,500},{C5,500},{C6,500},{C4,500},{G4,500},{AS5_Bb5,500},{D6,500},{C5,500},{C6,500},{C4,500},{G4,500},{D6,500},{C6,500},{G6,500},{G4,500},{DS6_Eb6,500},{G5,500},{C5,500},{C6,500},{C4,500},{G4,500},{AS5_Bb5,500},{G5,500},{C5,500},{C6,500},{C4,500},{G4,500},{AS5_Bb5,500},{CS2_Db2,1000},{F3,250},{AS3_Bb3,250},{C4,250},{F4,250},{AS4_Bb4,250},{C5,250},{F5,250},{AS5_Bb5,250},{C6,250},{F6,250},{AS6_Bb6,250},{C7,250},{0,1000},{0,0}
};
// https://virtualpiano.net/music-sheet/scattered-and-lost-celeste-lena-raine/
#define MUSIC_EXPLORE_SIZE 289
static const uint32_t musicExplore[MUSIC_EXPLORE_SIZE][2] = {
    {A4,250},{A5,250},{B5,250},{C6,250},{E5,500},{A5,500},{F4,250},{A5,250},{B5,250},{C6,250},{D5,500},{B4,500},{A4,250},{A5,250},{B5,250},{C6,250},{E5,500},{A5,500},{F4,250},{A5,250},{B5,250},{C6,250},{D5,250},{C5,250},{B4,250},{E5,250},{A4,250},{A5,250},{B5,250},{C6,250},{E5,500},{A5,500},{F4,250},{A5,250},{B5,250},{C6,250},{D5,500},{B4,500},{A4,250},{A5,250},{B5,250},{C6,250},{E5,500},{A5,500},{F4,250},{A5,250},{B5,250},{C6,250},{D5,250},{C5,250},{B4,250},{E5,250},{F4,250},{F5,250},{G5,250},{A5,250},{C5,500},{F5,500},{D4,250},{F5,250},{G5,250},{A5,250},{D5,250},{C5,250},{B4,250},{E5,250},{E4,250},{E5,250},{G5,250},{B5,250},{B4,500},{E5,500},{E3,250},{B4,250},{E5,250},{G5,250},{B3,250},{B4,250},{DS5_Eb5,250},{FS5_Gb5,250},{E4,250},{E5,250},{FS5_Gb5,250},{G5,250},{B4,500},{E5,500},{C4,250},{E5,250},{FS5_Gb5,250},{G5,250},{A4,500},{FS4_Gb4,500},{E4,250},{E5,250},{FS5_Gb5,250},{G5,250},{B4,500},{E5,500},{C4,250},{E5,250},{FS5_Gb5,250},{G5,250},{A4,250},{G4,250},{FS4_Gb4,250},{B4,250},{E4,250},{E5,250},{FS5_Gb5,250},{G5,250},{B4,500},{E5,500},{C4,250},{E5,250},{FS5_Gb5,250},{G5,250},{A4,500},{FS4_Gb4,500},{E4,250},{E5,250},{FS5_Gb5,250},{G5,250},{B4,500},{E5,500},{C4,250},{E5,250},{FS5_Gb5,250},{G5,250},{A4,250},{G4,250},{FS4_Gb4,250},{B4,250},{C4,250},{C5,250},{D5,250},{E5,250},{G4,500},{C5,500},{A3,250},{C5,250},{D5,250},{E5,250},{A4,250},{G4,250},{FS4_Gb4,250},{B4,250},{B3,250},{B4,250},{D5,250},{FS5_Gb5,250},{FS4_Gb4,500},{B4,500},{B2,250},{FS4_Gb4,250},{B4,250},{D5,250},{FS3_Gb3,250},{FS4_Gb4,250},{AS4_Bb4,250},{CS5_Db5,250},{B4,250},{FS4_Gb4,250},{B5,250},{FS5_Gb5,250},{B4,250},{FS4_Gb4,250},{B5,250},{FS5_Gb5,250},{B4,250},{FS4_Gb4,250},{B5,250},{FS5_Gb5,250},{B4,250},{FS4_Gb4,250},{B5,250},{CS6_Db6,250},{AS4_Bb4,250},{FS4_Gb4,250},{AS5_Bb5,250},{FS5_Gb5,250},{AS4_Bb4,250},{FS4_Gb4,250},{AS5_Bb5,250},{FS5_Gb5,250},{AS4_Bb4,250},{FS4_Gb4,250},{AS5_Bb5,250},{FS5_Gb5,250},{AS4_Bb4,250},{FS4_Gb4,250},{AS5_Bb5,250},{AS4_Bb4,250},{A4,250},{FS4_Gb4,250},{A5,250},{FS5_Gb5,250},{A4,250},{FS4_Gb4,250},{A5,250},{FS5_Gb5,250},{A4,250},{FS4_Gb4,250},{A5,250},{FS5_Gb5,250},{A4,250},{FS4_Gb4,250},{A5,250},{B5,250},{GS4_Ab4,250},{E4,250},{GS5_Ab5,250},{E5,250},{GS4_Ab4,250},{E4,250},{GS5_Ab5,250},{E5,250},{GS4_Ab4,250},{E4,250},{GS5_Ab5,250},{E5,250},{GS4_Ab4,250},{E4,250},{GS5_Ab5,250},{AS5_Bb5,250},{B4,250},{FS4_Gb4,250},{B5,250},{FS5_Gb5,250},{B4,250},{FS4_Gb4,250},{B5,250},{FS5_Gb5,250},{B4,250},{FS4_Gb4,250},{B5,250},{FS5_Gb5,250},{B4,250},{FS4_Gb4,250},{B5,250},{CS6_Db6,250},{AS4_Bb4,250},{FS4_Gb4,250},{AS5_Bb5,250},{FS5_Gb5,250},{AS4_Bb4,250},{FS4_Gb4,250},{AS5_Bb5,250},{FS5_Gb5,250},{AS4_Bb4,250},{FS4_Gb4,250},{AS5_Bb5,250},{FS5_Gb5,250},{AS4_Bb4,250},{FS4_Gb4,250},{AS5_Bb5,250},{AS4_Bb4,250},{A4,250},{FS4_Gb4,250},{A5,250},{FS5_Gb5,250},{A4,250},{FS4_Gb4,250},{A5,250},{FS5_Gb5,250},{A4,250},{FS4_Gb4,250},{A5,250},{FS5_Gb5,250},{A4,250},{FS4_Gb4,250},{A5,250},{B5,250},{GS4_Ab4,250},{E4,250},{GS5_Ab5,250},{E5,250},{GS4_Ab4,250},{E4,250},{GS5_Ab5,250},{E5,250},{GS4_Ab4,250},{E4,250},{GS5_Ab5,250},{E5,250},{E4,250},{GS4_Ab4,250},{GS5_Ab5,250},{AS5_Bb5,250},{0,0}
};

// https://virtualpiano.net/music-sheet/mortal-kombat-theme-the-immortals/
// Mortal combat theme
#define MUSIC_COMBAT_SIZE 160
static const uint32_t musicCombat[MUSIC_COMBAT_SIZE][2] = {
    {A4,125},{A4,125},{C5,125},{A4,125},{D5,125},{A4,125},{E5,125},{D5,125},{C5,125},{C5,125},{E5,125},{C5,125},{G5,125},{C5,125},{E5,125},{C5,125},{G4,125},{G4,125},{B4,125},{G4,125},{C5,125},{G4,125},{C5,125},{B4,125},{F4,125},{F4,125},{A4,125},{F4,125},{B4,125},{F4,125},{B4,125},{A4,125},{A4,125},{A4,125},{C5,125},{A4,125},{D5,125},{A4,125},{E5,125},{D5,125},{C5,125},{C5,125},{E5,125},{C5,125},{G5,125},{C5,125},{E5,125},{C5,125},{G4,125},{G4,125},{B4,125},{G4,125},{C5,125},{G4,125},{C5,125},{B4,125},{F4,125},{F4,125},{A4,125},{F4,125},{B4,125},{F4,125},{B4,500},{A4,500},{A4,500},{A4,500},{A4,500},{A4,500},{G4,125},{C5,500},{A4,500},{A4,500},{A4,500},{A4,500},{G4,125},{E4,500},{A4,500},{A4,500},{A4,500},{A4,500},{G4,125},{C5,500},{A4,500},{A4,500},{A4,500},{A4,125},{A4,500},{A4,125},{A4,500},{A4,500},{A4,500},{A4,500},{A4,500},{G4,125},{C5,500},{A4,500},{A4,500},{A4,500},{A4,500},{G4,125},{E4,500},{A4,500},{A4,500},{A4,500},{A4,500},{G4,125},{C5,500},{A4,500},{A4,500},{A4,500},{A4,125},{A4,500},{A4,125},{A4,500},{A4,125},{A4,125},{A4,125},{E5,125},{A4,125},{C5,125},{A4,125},{AS4_Bb4,125},{A4,125},{C5,125},{A4,125},{AS4_Bb4,125},{G4,500},{A4,125},{E5,125},{A4,125},{C5,125},{A4,125},{AS4_Bb4,125},{A4,125},{C5,125},{A4,125},{AS4_Bb4,125},{G4,500},{A4,125},{E5,125},{A4,125},{C5,125},{A4,125},{AS4_Bb4,125},{A4,125},{C5,125},{A4,125},{AS4_Bb4,125},{G4,500},{A4,125},{E5,125},{A4,125},{C5,125},{G4,125},{G4,125},{G4,125},{G4,125},{A4,125},{A4,500},{0,0}
};

#endif
