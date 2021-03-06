/******************************************************************************
 *
 * Module: Timer
 *
 * File Name: Timer1.c
 *
 * Description: Timer1
 *
 * Author: Ola Mohamed
 *
 *******************************************************************************/


#include "timer1.h"

static volatile void (*g_callBackPtr)(void) = NULL_PTR;

uint16 g_initialCounter = 0;
uint16 g_CTC_OCR1A;
uint16 g_CTC_OCR1B;


ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER1_COMPB_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

void TIMER1_init(const TIMER1_configType * config_Ptr)
{
	SET_BIT(TCCR1A,FOC1A);
	SET_BIT(TCCR1A,FOC1B);
	TCNT1 = g_initialCounter;
	if(config_Ptr->timerMode == OVERFLOW)
	{
		 TCCR1A &= ~((1<<WGM10) | (1<<WGM11));
		 TCCR1B &= ~((1<<WGM12) | (1<<WGM13));
		 SET_BIT(TIMSK,TOIE1);
	}
	else if(config_Ptr->timerMode == CTC)
	{
		TCCR1A &= ~((1<<WGM10) | (1<<WGM11));
		SET_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);
		if(config_Ptr->channelNumber == CHANNEL_A )
		{
			SET_BIT(PORTD,PD5);
			TCCR1A = (TCCR1A & 0x3F) | ((config_Ptr->ctcMode) << 6);
			SET_BIT(TIMSK,OCIE1A);
			OCR1A = g_CTC_OCR1A;
		}
		else if(config_Ptr->channelNumber == CHANNEL_B)
		{
			SET_BIT(PORTD,PD4);
			TCCR1A = (TCCR1A & 0xCF) | ((config_Ptr->ctcMode) << 4);
			SET_BIT(TIMSK,OCIE1B);
			OCR1A = g_CTC_OCR1B;
		}
	}
	TCCR1B = (TCCR1B & 0xF8) | (config_Ptr->clock);
}

void TIMER1_setCallBack(void (* a_ptr) (void))
{
	g_callBackPtr = a_ptr;
}
