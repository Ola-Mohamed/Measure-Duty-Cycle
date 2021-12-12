/******************************************************************************
 *
 * Module: Interrupt
 *
 * File Name: Interrupt.c
 *
 * Description: Interrupt
 *
 * Author: Ola Mohamed
 *
 *******************************************************************************/


#include "interrupt.h"

static volatile void (*g_callBackPtr0)(void) = NULL_PTR;
static volatile void (*g_callBackPtr1)(void) = NULL_PTR;
static volatile void (*g_callBackPtr2)(void) = NULL_PTR;

ISR(INT0_vect)
{
	if(g_callBackPtr0 != NULL_PTR)
	{
		(*g_callBackPtr0)();
	}
}

ISR(INT1_vect)
{
	if(g_callBackPtr1 != NULL_PTR)
	{
		(*g_callBackPtr1)();
	}
}

ISR(INT2_vect)
{
	if(g_callBackPtr2 != NULL_PTR)
	{
		(*g_callBackPtr2)();
	}
}

void INTERRUPT_init(const INTERRUPT_configType * config_Ptr)
{
	if((config_Ptr->INTERRUPT_number) == INTERRUPT_0)
	{
		CLEAR_BIT(DDRD,PD2);
		SET_BIT(GICR,INT0);
		if((config_Ptr->mode) == LOW_LEVEL)
		{
			CLEAR_BIT(MCUCR,ISC00);
			CLEAR_BIT(MCUCR,ISC01);
		}
		else if((config_Ptr->mode) == ANY_CHANGE)
		{
			SET_BIT(MCUCR,ISC00);
			CLEAR_BIT(MCUCR,ISC01);
		}
		else if((config_Ptr->mode) == FALLING_EDGE)
		{
			CLEAR_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
		}
		else if((config_Ptr->mode) == RISING_EDGE)
		{
			SET_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
		}
	}
	else if((config_Ptr->INTERRUPT_number) == INTERRUPT_1)
	{
		CLEAR_BIT(DDRD,PD3);
		SET_BIT(GICR,INT1);
		if((config_Ptr->mode) == LOW_LEVEL)
		{
			CLEAR_BIT(MCUCR,ISC10);
			CLEAR_BIT(MCUCR,ISC11);
		}
		else if((config_Ptr->mode) == ANY_CHANGE)
		{
			SET_BIT(MCUCR,ISC10);
			CLEAR_BIT(MCUCR,ISC11);
		}
		else if((config_Ptr->mode) == FALLING_EDGE)
		{
			CLEAR_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
		}
		else if((config_Ptr->mode) == RISING_EDGE)
		{
			SET_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
		}
	}
	else if ((config_Ptr->INTERRUPT_number) == INTERRUPT_2)
	{
		CLEAR_BIT(DDRB,PD2);
		SET_BIT(GICR,INT2);
		if((config_Ptr->mode) == FALLING_EDGE)
		{
			CLEAR_BIT(MCUCSR,ISC2);
		}
		else if((config_Ptr->mode) == RISING_EDGE)
		{
			SET_BIT(MCUCSR,ISC2);
		}

	}
}

void INTERRUPT_0_callBack(void (*a_ptr)(void))
{
	g_callBackPtr0 = a_ptr;
}

void INTERRUPT_1_callBack(void (*a_ptr)(void))
{
	g_callBackPtr1 = a_ptr;
}

void INTERRUPT_2_callBack(void (*a_ptr)(void))
{
	g_callBackPtr2 = a_ptr;
}
