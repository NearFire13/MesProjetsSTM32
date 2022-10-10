#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"
// Contrôler Pull Up/Down : ODR

// Valeur APB2ENR après exécution : 000001FC
// Led verte : GPIOA 5
// Bouton Poussoir Bleu : GPIOC 13

// CRL pour configurer
// IDR pour lire / ODR pour écrire

#define PORT_LED GPIOA
#define PIN_LED 5

void Callback(void)
{
	// Le code à exécuter pendant l’interruption
	
	MyGPIO_Toggle(PORT_LED, PIN_LED);
}

int main(void)
{
	/*
	// **** Version Sans Driver ****
	
	//Periode_Timer = Periode_Horloge * (PSC + 1) * (ARR + 1) = 500 ms
	//Periode_Timer = 1/72*10^6 * (PSC + 1) * (ARR + 1) = 500 ms
	//Periode_Timer = (PSC + 1) * (ARR + 1) = 500 ms * 72*10^6
	//Periode_Timer = (PSC + 1) * (ARR + 1) = 36 * 10^6
	// (599 + 1) * (59 999 + 1) * 1/(72*10^6) = 0,5 s = 500 ms
	
	//Activer Timer 2
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->CR1 |= 0x01;
	TIM2->ARR = 0xEA60 - 0x01; // 60 000 - 1 = 59 999 (0xEA5F)
	TIM2->PSC = 0x0258 - 0x01; // 600 - 1 = 599 (0x0257)
	*/
	
	// **** Version Avec Driver ****
	MyGPIO_Struct_TypeDef LedVerte = { PORT_LED, PIN_LED, Out_Ppull };
	MyTimer_Struct_TypeDef Timer2 = { TIM2, 60000-1, 600-1 };
	
	MyGPIO_Init(&LedVerte);
	MyTimer_Base_Init(&Timer2);
	MyTimer_Base_Start(Timer2.Timer);
	MyTimer_ActiveIT(Timer2.Timer, 0, Callback);
	//MyTimer_Base_Stop(&Timer2);

	while(1)
	{
	}
}
