#include "LAN8720.h"
#include "delay.h"
#include "key.h"
#include "led.h"
#include "lwip_comm.h"
#include "sys.h"
#include "usart.h"
//#include "usmart.h"
#include "adc.h"
#include "beep.h"
#include "dht11.h"
#include "ds18b20.h"
#include "exti.h"
#include "httpd.h"
#include "lcd.h"
#include "lwip/netif.h"
#include "lwip_comm.h"
#include "lwipopts.h"
#include "malloc.h"
#include "moto.h"
#include "rtc.h"
#include "sram.h"
#include "temperature.h"
#include "timer.h"
#include "usart3.h"
// hello
//#include "timer7.h"
// myhhhhhhh
// ALIENTEK ̽����STM32F407������
// LWIP LWIP�ۺ�ʵ��
//����֧�֣�www.openedv.com
//�������������ӿƼ����޹�˾
extern u8 DS18B20_Init(void);
extern void Adc_Temperate_Init(void); //�����ڲ��¶ȴ�������ʼ������

// u16 USART_RX_STA=0;
//����UI
// mode:
// bit0:0,������;1,����ǰ�벿��UI
// bit1:0,������;1,���غ��벿��UI
void lwip_test_ui(u8 mode) {
  u8 speed;
  u8 buf[30];
  POINT_COLOR = RED;
  if (mode & 1 << 0) {
    LCD_Fill(30, 30, lcddev.width, 110, WHITE); //������ʾ
    LCD_ShowString(30, 30, 200, 16, 16, "Explorer STM32F4");
    LCD_ShowString(30, 50, 200, 16, 16, "LWIP Webserver Test");
    LCD_ShowString(30, 70, 200, 16, 16, "ATOM@ALIENTEK");
    LCD_ShowString(30, 90, 200, 16, 16, "2014/8/15");
  }
  if (mode & 1 << 1) {
    LCD_Fill(30, 110, lcddev.width, lcddev.height, WHITE); //������ʾ
    LCD_ShowString(30, 110, 200, 16, 16, "lwIP Init Successed");
    if (lwipdev.dhcpstatus == 2)
      sprintf((char *)buf, "DHCP IP:%d.%d.%d.%d", lwipdev.ip[0], lwipdev.ip[1],
              lwipdev.ip[2], lwipdev.ip[3]); //��ӡ��̬IP��ַ
    else
      sprintf((char *)buf, "Static IP:%d.%d.%d.%d", lwipdev.ip[0],
              lwipdev.ip[1], lwipdev.ip[2], lwipdev.ip[3]); //��ӡ��̬IP��ַ
    LCD_ShowString(30, 130, 210, 16, 16, buf);
    speed = LAN8720_Get_Speed(); //�õ�����
    if (speed & 1 << 1)
      LCD_ShowString(30, 150, 200, 16, 16, "Ethernet Speed:100M");
    else
      LCD_ShowString(30, 150, 200, 16, 16, "Ethernet Speed:10M");
  }
}

int main(void) {
  u32 i;
  delay_init(168);
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�жϷ�������
                                                  //��ʱ��ʼ��
  uart_init(9600); //���ڲ���������
  usart3_init(115200);
  // usmart_dev.init(84); 	                        //��ʼ��USMART
  LED_Init(); // LED��ʼ��

  KEY_Init();       //������ʼ��
  LCD_Init();       // LCD��ʼ��
  BEEP_Init();      //��������ʼ��
  RTC_Timer_Init(); // RTC��ʼ��
  Adc_Init();       // ADC1_CH5��ʼ��
  DS18B20_Init();
  Adc_Temperate_Init(); //�ڲ��¶ȴ�������ʼ��
  FSMC_SRAM_Init();     //��ʼ���ⲿSRAM
  DHT11_Init();
  EXTIX_Init();
  mymem_init(SRAMIN);  //��ʼ���ڲ��ڴ���
  mymem_init(SRAMEX);  //��ʼ���ⲿ�ڴ���
  mymem_init(SRAMCCM); //��ʼ��CCM�ڴ���
  MOTO_GPIO_Config();
  POINT_COLOR = RED;       //��ɫ����
  lwip_test_ui(1);         //����ǰ�벿��UI
  TIM3_Int_Init(999, 839); // 100khz��Ƶ��,����1000Ϊ10ms
  // TIM7_Int_Init(1000-1,8400-1);
  CAR_STOP();

  while (lwip_comm_init()) // lwip��ʼ��
  {
    LCD_ShowString(30, 150, 200, 20, 16, "LWIP Init Falied!");
    delay_ms(1200);
    LCD_Fill(30, 110, 230, 130, WHITE); //������ʾ
    LCD_ShowString(30, 110, 200, 16, 16, "Retrying...");
  }
  LCD_ShowString(30, 110, 200, 20, 16, "LWIP Init Success!");
  LCD_ShowString(30, 130, 200, 16, 16, "DHCP IP configing..."); //�ȴ�DHCP��ȡ
#if LWIP_DHCP
  while ((lwipdev.dhcpstatus != 2) &&
         (lwipdev.dhcpstatus != 0XFF)) //�ȴ�DHCP��ȡ�ɹ�/��ʱ����
  {
    lwip_periodic_handle();
  }
#endif
  lwip_test_ui(2); //���غ��벿��UI
  delay_ms(500);   //��ʱ1s
  delay_ms(500);
  httpd_init(); // Web Serverģʽ
  while (1) {
    lwip_periodic_handle();
    i++;
    if (i % 5000 == 0)
      LED0 = !LED0;
    delay_us(100);
  }
}
