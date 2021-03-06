/******************************************************************************
 *
 * Module: Timer
 *
 * File Name: Timer1.h
 *
 * Description: Timer1
 *
 * Author: Ola Mohamed
 *
 *******************************************************************************/
#ifndef TIMER1_H_
#define TIMER1_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                        External Variables                                   *
 *******************************************************************************/

extern uint16 g_initialCounter;
extern uint16 g_CTC_OCR1A;
extern uint16 g_CTC_OCR1B;

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	OVERFLOW,CTC=4
}TIMER1_modeType;

typedef enum
{
	NORMAL,TOGGLE_OC,CLEAR_OC,SET_OC
}CTC_modeType;

typedef enum
{
	NO_CHANNEL,CHANNEL_A,CHANNEL_B
}CTC_channelType;

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,EXTERNAL_CLOCK_FALLING,EXTERNAL_CLOCK_RISING
}TIMER1_ClockType;

typedef struct
{
	TIMER1_modeType  timerMode;
	CTC_modeType     ctcMode;
	CTC_channelType  channelNumber;
	TIMER1_ClockType clock;
}TIMER1_configType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void TIMER1_init(const TIMER1_configType * config_Ptr);

void TIMER1_setCallBack(void (* a_ptr) (void));

#endif /* TIMER1_H_ */
