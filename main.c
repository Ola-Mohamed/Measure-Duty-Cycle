/******************************************************************************
 *
 * Module: Calculate the duty cycle
 *
 * File Name: main.c
 *
 * Author: Ola Mohamed
 *
 *******************************************************************************/
#include "timer1.h"
#include "lcd.h"
#include "interrupt.h"

uint8 g_edgeCount = 0;
uint16 g_timeHigh = 0;
uint16 g_timePeriod = 0;
uint16 g_timePeriodPlusHigh = 0;

void APP_edgeProcessing(void)
{
	g_edgeCount++;
	if(g_edgeCount == 1)
	{   TCNT1 = 0;
		INTERRUPT_configType Interrupt_config ={ FALLING_EDGE};
	}
	else if(g_edgeCount == 2)
	{
		/* Store the High time value */
		g_timeHigh = TCNT1;
		/* Detect rising edge */
		INTERRUPT_configType Interrupt_config ={ RISING_EDGE};
	}
	else if(g_edgeCount == 3)
	{
		/* Store the Period time value */
		g_timePeriod =	TCNT1;
		/* Detect falling edge */
		INTERRUPT_configType Interrupt_config ={ FALLING_EDGE};
	}
	else if(g_edgeCount == 4)
	{
		/* Store the Period time value + High time value */
		g_timePeriodPlusHigh = 	TCNT1;
		/* Clear the timer counter register to start measurements again */
		TCNT1 = 0;
		/* Detect rising edge */
		INTERRUPT_configType Interrupt_config ={RISING_EDGE};
	}

}
int main(){

	uint32 dutyCycle = 0;

	/* Enable Global Interrupt I-Bit */
		SREG |= (1<<7);

	/* Initialize both the LCD , TIMER  and INTERRUPT driver */
			TIMER1_configType Timer1_config = {OVERFLOW , NORMAL,NO_CHANNEL ,F_CPU_CLOCK};

			INTERRUPT_configType Interrupt_config ={INTERRUPT_0 , RISING_EDGE};
			INTERRUPT_0_callBack(APP_edgeProcessing);
			LCD_init();
			TIMER1_init(& Timer1_config);
			INTERRUPT_init(&Interrupt_config);
           LCD_displayString("Duty = ");
	while(1){
		if(g_edgeCount == 4)
				{
					g_edgeCount = 0;
					/* calculate the dutyCycle */
					dutyCycle = ((float)(g_timePeriodPlusHigh-g_timePeriod) / (g_timePeriodPlusHigh - g_timeHigh)) * 100;
					/* display the dutyCycle on LCD screen */
					LCD_intgerToString(dutyCycle);
					LCD_displayCharacter('%');
				}
	}






}
