#include "stm32f10x.h"
#include "Driver_GPIO.h"
// Contrôler Pull Up/Down : ODR

// Valeur APB2ENR après exécution : 000001FC
// Led verte : GPIOA 5
// Bouton Poussoir Bleu : GPIOC 13

// CRL pour configurer
// IDR pour lire / ODR pour écrire

int main(void)
{
	MyGPIO_Struct_TypeDef BoutonPoussoir = { GPIOC, 13, In_Floating };
	MyGPIO_Struct_TypeDef LedVerte = { GPIOA, 5, Out_Ppull };
	
	//Test Port C - Définition de Structure
	MyGPIO_Struct_TypeDef Pinpf1 = { GPIOC, 1, In_Floating };
	MyGPIO_Struct_TypeDef PinPF1 = { GPIOC, 8, In_PullDown };
	MyGPIO_Struct_TypeDef PinMilieu1 = { GPIOC, 13, In_PullUp };
	
	MyGPIO_Struct_TypeDef Pinpf2 = { GPIOC, 2, In_Analog };
	MyGPIO_Struct_TypeDef PinPF2 = { GPIOC, 9, Out_Ppull };
	MyGPIO_Struct_TypeDef PinMilieu2 = { GPIOC, 14, Out_OD };
	
	MyGPIO_Struct_TypeDef Pinpf3 = { GPIOC, 3, AltOut_Ppull };
	MyGPIO_Struct_TypeDef PinPF3 = { GPIOC, 10, AltOut_OD };
	MyGPIO_Struct_TypeDef PinMilieu3 = { GPIOC, 15, In_PullDown };
	
	MyGPIO_Init(&BoutonPoussoir);
	MyGPIO_Init(&LedVerte);
	
	//Test Port C - Initialisation
	MyGPIO_Init(&Pinpf1);
	MyGPIO_Init(&PinPF1);
	MyGPIO_Init(&PinMilieu1);
	MyGPIO_Init(&Pinpf2);
	MyGPIO_Init(&PinPF2);
	MyGPIO_Init(&PinMilieu2);
	MyGPIO_Init(&Pinpf3);
	MyGPIO_Init(&PinPF3);
	MyGPIO_Init(&PinMilieu3);
	
	//Periode_Timer = Periode_Horloge * (PSC + 1) * (ARR + 1) = 500 ms
	//Periode_Timer = 1/72*10^6 * (PSC + 1) * (ARR + 1) = 500 ms
	//Periode_Timer = (PSC + 1) * (ARR + 1) = 500 ms * 72*10^6
	//Periode_Timer = (PSC + 1) * (ARR + 1) = 36 * 10^6
	//Periode_Timer = 
	//
	
	//Activer Timer 2
	//RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	RCC->APB1ENR &= ~(0xF << 0);
	RCC->APB1ENR |= (0x1 << 0);
	
	//TIM2->CR1 = ?????;
	TIM2->CR1 &= ~(0xF << 0);
	TIM2->CR1 |= (0x1 << 0);
	
	TIM2->PSC &= ~(0xF << 2);
	TIM2->PSC |= (0x1 << 2);
	
	TIM2->ARR &= ~(0xF << 2);
	TIM2->ARR |= (0x1 << 2);

	while(1)
	{
		if( (MyGPIO_Read(GPIOC, 13) ) == 0) // Si le bouton est enfoncé
		{
			MyGPIO_Set(GPIOA, 5);
		}
		else
		{
			MyGPIO_Reset(GPIOA, 5);
		}
	}
}
