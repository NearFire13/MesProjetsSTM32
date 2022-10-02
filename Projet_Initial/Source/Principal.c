#include "stm32f10x.h"

// Contrôler Pull Up/Down : ODR

// Valeur APB2ENR après exécution : 000001FC
// Led verte : GPIOA 5
// Bouton Poussoir Bleu : GPIOC 13

// CRL pour configurer
// IDR pour lire / ODR pour écrire

int main(void)
{
	//Activer Horloge A, B et C
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4); // 0x000001E0 -> 0000 0000 0000 0000 0000 0001 1111 1100 =| 0001 1100 -> 000001FC

	
	// PC.13 floating input
	GPIOC->CRH &= ~(0x01 << 0) | (0x01 << 2) | (0x01 << 3); //Met à zéro le 1er, 3ème et 4ème bit
	GPIOC->CRH |= (0x01 << 1); //Met à zéro le 2ème bit
	
	//GPIOC->CRH &= ~(0xF << 4 * 5); // Met tous à zéro
	//GPIOC->CRH |= (4 << 4 * 5); // Met à 0100 le port 13
	//GPIOC->CRH |= (1<<22);
	
	// PA.5 output push pull
	//GPIOA->CRL &= ~((0x01 << 0) | (0x01 << 1) | (0x01 << 3)); //Met à zéro le 1er, 2ème et 4ème bit
	//GPIOA->CRL |= (0x01 << 2); //Met à zéro le 3ème bit
	
	GPIOA->CRL &= ~(0xF << 4*5); // Met tous à zéro
	GPIOA->CRL |= (2 << 4*5); // Met à 0010 le port 5
	
	//Open Drain
	//GPIOA->CRL &= ~(0xF << 4*5); // Met tous à zéro
	//GPIOA->CRL |= (6 << 4*5); // Met à 0110 le port 5

	while(1)
	{
		if(( (GPIOC->IDR) & (0x01 << 13) ) == 0) // Si le bouton est enfoncé
		{
			GPIOA->ODR |= (0x01 << 5); // Allume la LED
		}
		else
		{
			GPIOA->ODR &= ~(0x01 << 5); // Eteint la LED
		}
	}
}
