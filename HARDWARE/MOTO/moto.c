#include "moto.h"   

 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void MOTO_GPIO_Config(void)
{		
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_AHB1PeriphClockCmd ( MOTO11_GPIO_CLK| MOTO12_GPIO_CLK|MOTO21_GPIO_CLK| MOTO22_GPIO_CLK, ENABLE);															   
		GPIO_InitStructure.GPIO_Pin = MOTO11_PIN;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
	
		GPIO_Init(MOTO11_GPIO_PORT, &GPIO_InitStructure);	//////电机1的第一个端口定义OK
/////////////////////////////////////////////////////////////////
												   
		GPIO_InitStructure.GPIO_Pin = MOTO12_PIN;	
		GPIO_Init(MOTO12_GPIO_PORT, &GPIO_InitStructure);	//电机1的第二个端口定义OK
///////////////////////////////////////////////////////////////////	

		GPIO_InitStructure.GPIO_Pin = MOTO21_PIN;	
		GPIO_Init(MOTO21_GPIO_PORT, &GPIO_InitStructure);	//电机2的第一个端口定义OK
///////////////////////////////////////////////////////////////////	
	
		GPIO_InitStructure.GPIO_Pin = MOTO22_PIN;	
		GPIO_Init(MOTO22_GPIO_PORT, &GPIO_InitStructure);	//电机2的第二个端口定义OK
///////////////////////////////////////////////////////////////////	

  
}
void CAR_UP(void)
{
	MOTO11(OFF);
	MOTO12(ON);
	MOTO21(ON);
	MOTO22(OFF);
}

void CAR_BACK(void)
{
	MOTO11(ON);
	MOTO12(OFF);
	MOTO21(OFF);
	MOTO22(ON);
}

void CAR_LEFT(void)
{
	MOTO11(ON);
	MOTO12(OFF);
	MOTO21(ON);
	MOTO22(OFF);
}

void CAR_RIGHT(void)
{
	MOTO11(OFF); //  0
	MOTO12(ON);//    1
	MOTO21(OFF);//   0
	MOTO22(ON);//    1
}
void CAR_STOP(void)
{
	MOTO11(OFF);
	MOTO12(OFF);
	MOTO21(OFF);
	MOTO22(OFF);
}
