/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  Vuong Viet Thao
  * @version V3.5.0
  * @date    9-2-2022
  * @brief   Main program body
  ******************************************************************************
  * @attention
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>

#include "Keypad.h"
/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "LCD_I2C.h"
#include "RTC.h"
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
	long xColumn;
	signed char *pcMessage;
} logmsg_t;
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
QueueHandle_t xlogQueue;
/* Private functions ---------------------------------------------------------*/
int count = 0;
void LED_Init(void)		   
{	
    GPIO_InitTypeDef GPIO_InitStructure;
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB, ENABLE);
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;			 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);

	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;			 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
static void LED1Task( void *pvParameters )
{
		logmsg_t a;
		while(1)
		{
			vTaskDelay(1000);
			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
			vTaskDelay(1000);
			GPIO_SetBits(GPIOC, GPIO_Pin_13);
		}
}
static void DongHo( void *pvParameters )
{
	  logmsg_t a;
		while(1)
		{
			vTaskDelay(100);
			 GetTIMER();
			vTaskDelay(100);
		}
}
static void PasswordSend( void *pvParameters )
{
	  logmsg_t a;
		while(1)
		{
			vTaskDelay(100);
			 Password();
			vTaskDelay(100);
		}
}
static void LOGTASK( void *pvParameters )
{
	logmsg_t a;
	for( ;; )
	{
		/* Wait for a message to arrive that requires displaying. */
		while( xQueueReceive( xlogQueue, &a, portMAX_DELAY ) != pdPASS );
		printf(( char const * ) a.pcMessage );
	}
}
int main(void)
{
	SystemInit();			 //系统时钟配置system_stm32f10x.c中
	LED_Init();
	DelayTimer_Init();
	RTC_Configuration();
	Time_Current();
  LCD_I2C_Configuration();
	Keypad4x4_Config();
	LCD_Init();
	xTaskCreate( LED1Task, "led1", 128, NULL, 3, NULL );
	xTaskCreate( PasswordSend, "Pass", 128, NULL, 4, NULL );
	xTaskCreate( DongHo, "DongHo", 128, NULL, 2, NULL );
	vTaskStartScheduler();
  while (1)
  {
		
  }
}

