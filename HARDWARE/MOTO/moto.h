#ifndef __MOTO_H
#define	__MOTO_H

#include "stm32f4xx.h"

#define MOTO11_PIN                  GPIO_Pin_1                 
#define MOTO11_GPIO_PORT            GPIOA                      
#define MOTO11_GPIO_CLK             RCC_AHB1Periph_GPIOA

#define MOTO12_PIN                  GPIO_Pin_4                
#define MOTO12_GPIO_PORT            GPIOA                      
#define MOTO12_GPIO_CLK             RCC_AHB1Periph_GPIOA

#define MOTO21_PIN                  GPIO_Pin_5                 
#define MOTO21_GPIO_PORT            GPIOA                      
#define MOTO21_GPIO_CLK             RCC_AHB1Periph_GPIOA

#define MOTO22_PIN                  GPIO_Pin_6                 
#define MOTO22_GPIO_PORT            GPIOA                      
#define MOTO22_GPIO_CLK             RCC_AHB1Periph_GPIOA

#define ON  0
#define OFF 1

/* 带参宏，可以像内联函数一样使用 */
#define MOTO11(a)	if (a)	\
					GPIO_SetBits(MOTO11_GPIO_PORT,MOTO11_PIN);\
					else		\
					GPIO_ResetBits(MOTO11_GPIO_PORT,MOTO11_PIN)
					
#define MOTO12(a)	if (a)	\
					GPIO_SetBits(MOTO12_GPIO_PORT,MOTO12_PIN);\
					else		\
					GPIO_ResetBits(MOTO12_GPIO_PORT,MOTO12_PIN)
		
#define MOTO21(a)	if (a)	\
					GPIO_SetBits(MOTO21_GPIO_PORT,MOTO21_PIN);\
					else		\
					GPIO_ResetBits(MOTO21_GPIO_PORT,MOTO21_PIN)
					
#define MOTO22(a)	if (a)	\
					GPIO_SetBits(MOTO22_GPIO_PORT,MOTO22_PIN);\
					else		\
					GPIO_ResetBits(MOTO22_GPIO_PORT,MOTO22_PIN)
					


					

void CAR_UP(void);
void CAR_BACK(void);
void CAR_LEFT(void);
void CAR_RIGHT(void);
void CAR_STOP(void);
void MOTO_GPIO_Config(void);					
					

#endif /* __MOTO_H */
