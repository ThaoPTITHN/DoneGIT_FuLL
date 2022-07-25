#include "RTC.h"
#include "stm32f10x.h"
#include "LCD_I2C.h"
#include "DelayTimer.h"
uint32_t Time = 0,hours = 20, minute = 24, second = 45;
void RTC_Configuration(){ 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);//B1
	PWR_BackupAccessCmd(ENABLE);//B2 
	if ((RCC->BDCR & RCC_BDCR_RTCEN) != RCC_BDCR_RTCEN)
	{
		RCC_BackupResetCmd(ENABLE);
		RCC_BackupResetCmd(DISABLE);
		RCC_LSEConfig(RCC_LSE_ON);
		while ((RCC->BDCR & RCC_BDCR_LSERDY) != RCC_BDCR_LSERDY) {}
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		RTC_SetPrescaler(0x7FFF); 
		RCC_RTCCLKCmd(ENABLE);
		RTC_WaitForSynchro();

	}
}
void Time_Current(void)
{
  /* cho ghi xong data cho bo RTC */
  RTC_WaitForLastTask();
  /* Thay doi gia tri thoi gian hien tai */
	RTC_SetCounter(hours*3600 + minute*60 + second);
  /* cho ghi xong data cho bo RTC */
  RTC_WaitForLastTask();
}
void Clock_Config(void){
    /* RCC system reset */
    RCC_DeInit();
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div2);
    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);
    /*enable HSI source clock*/
    RCC_HSICmd(ENABLE); 
    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET){}
    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x00) {}    
}
void GetTIMER(){
		Time  = RTC_GetCounter()%86400;
		hours  =Time/3600;
		minute =(Time%3600)/60;
		second =(Time%3600)%60;
	  LCD_Gotoxy(2,3);
	  LCD_Printf("Dong Ho RTC");
	  LCD_Gotoxy(3,2);
	  LCD_Printf("%02d : %02d : %02d", hours, minute, second);
}
		


