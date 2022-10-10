#ifndef MYTIMER_H
#define MYTIMER_H
#include "stm32f10x.h"

typedef struct
{
	TIM_TypeDef * Timer ; // TIM1 à TIM4
	unsigned short ARR ;
	unsigned short PSC ;
} MyTimer_Struct_TypeDef ;

/*
*****************************************************************************************
* @brief
* @param -> Paramètre sous forme d’une structure ( son adresse ) contenant les informations de base
* @Note -> Fonction à lancer systématiquement avant d’aller plus en détail dans les conf plus fines (PWM, codeur inc...)
*************************************************************************************************
*/
void MyTimer_Base_Init(MyTimer_Struct_TypeDef * Timer);

#define MyTimer_Base_Start(Timer) (Timer->CR1 |= 0x01)
#define MyTimer_Base_Stop(Timer) (Timer->CR1 &= ~(0x01))

/*
**************************************************************************************************
* @brief
* @param : 	- TIM_TypeDef * Timer : Timer concerné
						- char Prio : de 0 à 15
* @Note : La fonction MyTimer_Base_Init doit avoir été lancée au préalable
**************************************************************************************************
*/
void MyTimer_ActiveIT(TIM_TypeDef * Timer, char Prio, void (*IT_function) (void));
void Init_periph (void (* ptrFonction) (void));
#endif
