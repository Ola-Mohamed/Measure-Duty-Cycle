/******************************************************************************
 *
 * Module: Interrupt
 *
 * File Name: Interrupt.h
 *
 * Description: Interrupt
 *
 * Author: Ola Mohamed
 *
 *******************************************************************************/

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/


/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	INTERRUPT_0,INTERRUPT_1,INTERRUPT_2
}INTERRUPT_numberType;

typedef enum
{
	LOW_LEVEL,ANY_CHANGE,FALLING_EDGE,RISING_EDGE
}INTERRUPT_mode;

typedef struct
{
	INTERRUPT_numberType INTERRUPT_number;
	INTERRUPT_mode       mode;
}INTERRUPT_configType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void INTERRUPT_init(const INTERRUPT_configType * config_Ptr);
void INTERRUPT_callBack(void (*a_ptr)(void));

#endif /* INTERRUPT_H_ */
