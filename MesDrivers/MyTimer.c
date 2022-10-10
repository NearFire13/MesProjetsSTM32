#include "MyTimer.h"

void (* pFnc) (void); // Déclaration d'un pointeur de fonction

void MyTimer_Base_Init(MyTimer_Struct_TypeDef * Timer)
{
	if(Timer->Timer == TIM1)
	{
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; //Activer Timer 1
	}
	else if(Timer->Timer == TIM2)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //Activer Timer 2
	}
	else if(Timer->Timer == TIM3)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; //Activer Timer 3
	}
	else if(Timer->Timer == TIM4)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; //Activer Timer 4
	}
	
	Timer->Timer->ARR = Timer->ARR; // Configure Prescaler : 60 000 - 1 = 59 999
	Timer->Timer->PSC = Timer->PSC; // Configurer Auto-Reload Register : 600 - 1 = 599
}


void MyTimer_ActiveIT(TIM_TypeDef * Timer, char Prio, void (*IT_function) (void))
{
	/*
	Timer :
	Sur quels bits : UIE/UIF
	Sur quels registres : TIM2_DIER / TIM2_SR
	
	NVIC :
	Sur quels bits : 
	Sur quels champs de bits : 0 - 31 / 24-31 (28)
	Sur quels registres : NVIC_ISERx / NVIC_IPRx
	*/
	
	if(Timer == TIM1)
	{
		TIM1->DIER |= 0x01; // Active l'interruption côté Timer
		NVIC_EnableIRQ(TIM1_UP_IRQn); // Active l'interruption côté NVIC
		NVIC_SetPriority(TIM1_UP_IRQn, Prio); // Défini la priorité
		pFnc = IT_function; // Affectation du pointeur
	}
	else if(Timer == TIM2)
	{
		TIM2->DIER |= 0x01; // Active l'interruption côté Timer
		NVIC_EnableIRQ(TIM2_IRQn); // Active l'interruption côté NVIC
		NVIC_SetPriority(TIM2_IRQn, Prio); // Défini la priorité
		pFnc = IT_function; // Affectation du pointeur
	}
	else if(Timer == TIM3)
	{
		TIM3->DIER |= 0x01; // Active l'interruption côté Timer
		NVIC_EnableIRQ(TIM3_IRQn); // Active l'interruption côté NVIC
		NVIC_SetPriority(TIM3_IRQn, Prio); // Défini la priorité
		pFnc = IT_function; // Affectation du pointeur
	}
	else if(Timer == TIM4)
	{
		TIM4->DIER |= 0x01; // Active l'interruption côté Timer
		NVIC_EnableIRQ(TIM4_IRQn); // Active l'interruption côté NVIC
		NVIC_SetPriority(TIM4_IRQn, Prio); // Défini la priorité 
		pFnc = IT_function; // Affectation du pointeur
	}
}

void TIM1_UP_IRQHandler(void)
{
	TIM1->DIER &= ~(0x01); // Désactive l'interruption côté Timer
	if (pFnc != 0) (*pFnc) (); // Appel indirect de la fonction
}

void TIM2_IRQHandler(void)
{
	TIM2->DIER &= ~(0x01); // Désactive l'interruption côté Timer
	if (pFnc != 0) (*pFnc) (); // Appel indirect de la fonction
}

void TIM3_IRQHandler(void)
{
	TIM3->DIER &= ~(0x01); // Désactive l'interruption côté Timer
	if (pFnc != 0) (*pFnc) (); // Appel indirect de la fonction
}

void TIM4_IRQHandler(void)
{
	TIM4->DIER &= ~(0x01); // Désactive l'interruption côté Timer
	if (pFnc != 0) (*pFnc) (); // Appel indirect de la fonction
}
