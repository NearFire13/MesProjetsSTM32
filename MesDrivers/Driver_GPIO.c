#include "Driver_GPIO.h"


void MyGPIO_Init(MyGPIO_Struct_TypeDef * GPIOStructPtr)
{
	if(GPIOStructPtr->GPIO == GPIOA)
	{
		//RCC->APB2ENR |= (0x01 << 2); //Activer Horloge A
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; //Activer Horloge A
	}
	else if(GPIOStructPtr->GPIO == GPIOB)
	{
		//RCC->APB2ENR |= (0x01 << 3); //Activer Horloge B
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; //Activer Horloge B
	}
	else if(GPIOStructPtr->GPIO == GPIOC)
	{
		//RCC->APB2ENR |= (0x01 << 4); //Activer Horloge C
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; //Activer Horloge B
	}
	else if(GPIOStructPtr->GPIO == GPIOD)
	{
		//RCC->APB2ENR |= (0x01 << 5); //Activer Horloge D
		RCC->APB2ENR |= RCC_APB2ENR_IOPDEN; //Activer Horloge B
	}

	if(GPIOStructPtr->GPIO_Pin < 8) {
		GPIOStructPtr->GPIO->CRL &= ~(0xF << 4 * GPIOStructPtr->GPIO_Pin); // Met tous � z�ro
		GPIOStructPtr->GPIO->CRL |= (GPIOStructPtr->GPIO_Conf << 4 * GPIOStructPtr->GPIO_Pin); // Met � XXXX (binaire) le port X (lettre)
	}
	else 
	{
		GPIOStructPtr->GPIO->CRH &= ~(0xF << 4 * (GPIOStructPtr->GPIO_Pin - 8)); // Met tous � z�ro
		GPIOStructPtr->GPIO->CRH |= (GPIOStructPtr->GPIO_Conf << 4 * (GPIOStructPtr->GPIO_Pin - 8)); // Met � XXXX (binaire) le port X (lettre)
	}
	
	if(GPIOStructPtr->GPIO_Conf == In_PullDown)
	{
		GPIOStructPtr->GPIO->ODR &= ~(0xF << GPIOStructPtr->GPIO_Pin); // Met � z�ro
	}
	else if(GPIOStructPtr->GPIO_Conf == In_PullUp)
	{
		GPIOStructPtr->GPIO->ODR |= (0x01 << GPIOStructPtr->GPIO_Pin); // Met � un
	}
	
}

// Renvoie 0 ou autre chose diff�rent de 0
int MyGPIO_Read(GPIO_TypeDef * GPIO, char GPIO_Pin)
{
	return (GPIO->IDR) & (0x01 << GPIO_Pin);
}

//Met � 1 le pin que l'on veut
void MyGPIO_Set(GPIO_TypeDef * GPIO, char GPIO_Pin)
{
	GPIO->ODR |= (0x01 << GPIO_Pin);
}

//Remet � z�ro le pin
void MyGPIO_Reset(GPIO_TypeDef * GPIO, char GPIO_Pin)
{
	GPIO->ODR &= ~(0x01 << GPIO_Pin);
}

//Bouton enfonc� => Mettre � 1 le pin / Bouton pas enfonc� => Reset le pin
void MyGPIO_Toggle(GPIO_TypeDef * GPIO, char GPIO_Pin)
{
		GPIO->ODR ^= (0x01 << GPIO_Pin);
}
