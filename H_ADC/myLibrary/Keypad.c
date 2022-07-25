#include "Keypad.h"
#include "LCD_I2C.h"
#include "PWM.h"
ButtonManagement Button[16];
char bufferChar[8];
char bufferPass[8]= "0123456\0";
int indexBuff = 0;
uint8_t flagDone = 0;
int time = 0;
int flag = 0;
ButtonManagement Button0;
uint8_t Keypad4x4_Read (void)
{
	/* Make ROW 1 LOW and all other ROWs HIGH */
	GPIO_WriteBit (R1_PORT, R1_PIN, GPIO_PIN_RESET);  //Pull the R1 low
	GPIO_WriteBit (R2_PORT, R2_PIN, GPIO_PIN_SET);  // Pull the R2 High
	GPIO_WriteBit (R3_PORT, R3_PIN, GPIO_PIN_SET);  // Pull the R3 High
	GPIO_WriteBit (R4_PORT, R4_PIN, GPIO_PIN_SET);  // Pull the R4 High

	if (Button_OnPress(C1_PORT, C1_PIN, &Button[0]))   // if the Col 1 is low
	{
		return 1;
	}

	if (Button_OnPress(C2_PORT, C2_PIN, &Button[1]))   // if the Col 2 is low
	{
		return 2;
	}
	
	if (Button_OnPress(C3_PORT, C3_PIN, &Button[2]))   // if the Col 3 is low
	{
		return 3;
	}
	
	if (Button_OnPress(C4_PORT, C4_PIN, &Button[3]))    // if the Col 4 is low
	{
		return 4;
	}
	
	/* Make ROW 2 LOW and all other ROWs HIGH */
	GPIO_WriteBit (R1_PORT, R1_PIN, GPIO_PIN_SET);  //Pull the R1 HIGH
	GPIO_WriteBit (R2_PORT, R2_PIN, GPIO_PIN_RESET);  // Pull the R2 LOW
	GPIO_WriteBit (R3_PORT, R3_PIN, GPIO_PIN_SET);  // Pull the R3 High
	GPIO_WriteBit (R4_PORT, R4_PIN, GPIO_PIN_SET);  // Pull the R4 High
	
	if (Button_OnPress(C1_PORT, C1_PIN, &Button[4]))   // if the Col 1 is low
	{
		return 5;
	}

	if (Button_OnPress(C2_PORT, C2_PIN, &Button[5]))   // if the Col 2 is low
	{
		return 6;
	}
	
	if (Button_OnPress(C3_PORT, C3_PIN, &Button[6]))   // if the Col 3 is low
	{
		return 7;
	}
	
	if (Button_OnPress(C4_PORT, C4_PIN, &Button[7]))    // if the Col 4 is low
	{
		return 8;
	}
		
	/* Make ROW 3 LOW and all other ROWs HIGH */
	GPIO_WriteBit (R1_PORT, R1_PIN, GPIO_PIN_SET);  //Pull the R1 low
	GPIO_WriteBit (R2_PORT, R2_PIN, GPIO_PIN_SET);  // Pull the R2 High
	GPIO_WriteBit (R3_PORT, R3_PIN, GPIO_PIN_RESET);  // Pull the R3 High
	GPIO_WriteBit (R4_PORT, R4_PIN, GPIO_PIN_SET);  // Pull the R4 High
	
	if (Button_OnPress(C1_PORT, C1_PIN, &Button[8]))   // if the Col 1 is low
	{
		return 9;
	}

	if (Button_OnPress(C2_PORT, C2_PIN, &Button[9]))   // if the Col 2 is low
	{
		return 10;
	}
	
	if (Button_OnPress(C3_PORT, C3_PIN, &Button[10]))   // if the Col 3 is low
	{
		return 11;
	}
	
	if (Button_OnPress(C4_PORT, C4_PIN, &Button[11]))    // if the Col 4 is low
	{
		return 12;
	}	
		
	/* Make ROW 4 LOW and all other ROWs HIGH */
	GPIO_WriteBit (R1_PORT, R1_PIN, GPIO_PIN_SET);  //Pull the R1 low
	GPIO_WriteBit (R2_PORT, R2_PIN, GPIO_PIN_SET);  // Pull the R2 High
	GPIO_WriteBit (R3_PORT, R3_PIN, GPIO_PIN_SET);  // Pull the R3 High
	GPIO_WriteBit (R4_PORT, R4_PIN, GPIO_PIN_RESET);  // Pull the R4 High
	
	if (Button_OnPress(C1_PORT, C1_PIN, &Button[12]))   // if the Col 1 is low
	{
		return 13;
	}

	if (Button_OnPress(C2_PORT, C2_PIN, &Button[13]))   // if the Col 2 is low
	{
		return 14;
	}
	
	if (Button_OnPress(C3_PORT, C3_PIN, &Button[14]))   // if the Col 3 is low
	{
		return 15;
	}
	
	if (Button_OnPress(C4_PORT, C4_PIN, &Button[15]))    // if the Col 4 is low
	{
		return 16;
	}
	
	return 0;
}
int Map(int x, int inMin, int inMax, int outMin, int outMax) {
  return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}
void GPIO_Configure(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void PWM_Config(int goc){
	/*Cau hinh cho TIME3*/
	RCC -> APB1ENR |= 0x02;
	/*Cau hinh cho bo 3 cua TIMER*/
	TIM3 -> PSC     = 72 - 1;
	TIM3 -> ARR     = 20000 - 1;
	TIM3 -> CNT     = 0;
	/*Cau hinh cho PWM 1 channe3 ( PB0 - Channel 3 cua TIMER3*/
	TIM3 -> CCMR2   |= 0x0060;
	TIM3 -> CCER    |= 0x0100;
	int T;
	T = Map(goc, 0, 180, 500, 2500);
	TIM3 -> CCR3     = T;
	/*Cho phep bo dem hoat dong*/
	TIM3 -> CR1     |= 0x01;
	TIM3 -> EGR     |= 0x01;
}
void Keypad4x4_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	/*Configuration GPIO pin*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/*Configuration GPIO pin*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	Button_Config(GPIOB, GPIO_Pin_12, &Button0);
	GPIO_Configure();
	for (uint8_t i = 0; i < 16; i++)
	{
		Button[i].changeTime = 0;
		Button[i].flags = 0x00;
		Button[i].holdTime = 1000;
	}
}
signed char Convert(int K)
{
	if(K == 1) return '1';
	else if(K == 2) return '2';
	else if(K == 3) return '3';
	else if(K == 4) return 'A';
	else if(K == 5) return '4';
	else if(K == 6) return '5';
	else if(K == 7) return '6';
	else if(K == 8) return 'B';
	else if(K == 9) return '7';
	else if(K == 10) return '8';
	else if(K == 11) return '9';
	else if(K == 12) return 'C';
	else if(K == 13) return '*';
	else if(K == 14) return '0';
	else if(K == 15) return '#';
	else if(K == 16) return 'D';
	else return -1;
}
void Password()
{
	if (Button_OnPress(GPIOB, GPIO_Pin_12, &Button0))
	{
		bufferChar[7] = '\0';
		flagDone = 1;
		flag = 1;
		LCD_Clear();
	}
	if (flagDone == 0)
	{
		int keyPad = Keypad4x4_Read();
		if(keyPad)
		{
			char c = Convert(keyPad);
			bufferChar[indexBuff] = c;

			LCD_Gotoxy(0, indexBuff);
			LCD_Printf("%c", c);
			DelayTimer_Ms(400);
			LCD_Gotoxy(0, indexBuff);
			LCD_Printf("*");
			
			indexBuff += 1;
			if (indexBuff == 7) flagDone = 1;
		}
	}
	else
	{
		if(strcmp(bufferChar,bufferPass)==0)
		{
			LCD_Gotoxy(1, 0);
			LCD_Printf("DONE");				
			PWM_Config(90);
		}
		else
		{
			LCD_Gotoxy(1, 0);
			LCD_Printf("error");
			LCD_Gotoxy(1, 7);
			LCD_Printf("MK: %s", bufferChar);
		}
	}
}


