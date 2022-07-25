/**
  ******************************************************************************
  * @file    Keypad.h
  * @author  Chu Xuan Quang
  * @date    26-1-2022
  * @brief   Button program body
  ******************************************************************************
  * @attention Keypad 4x4
  ******************************************************************************
*/

#ifndef KETPAD_H
#define KETPAD_H

#include "stm32f10x.h"
#include "Button.h"

#define R1_PORT GPIOA
#define R1_PIN GPIO_Pin_7
#define R2_PORT GPIOA
#define R2_PIN GPIO_Pin_6
#define R3_PORT GPIOA
#define R3_PIN GPIO_Pin_5
#define R4_PORT GPIOA
#define R4_PIN GPIO_Pin_4
#define C1_PORT GPIOA
#define C1_PIN GPIO_Pin_3
#define C2_PORT GPIOA
#define C2_PIN GPIO_Pin_2
#define C3_PORT GPIOA
#define C3_PIN GPIO_Pin_1
#define C4_PORT GPIOA
#define C4_PIN GPIO_Pin_0

#define GPIO_PIN_RESET (BitAction)0
#define GPIO_PIN_SET (BitAction)1

void Keypad4x4_Config(void);
uint8_t Keypad4x4_Read(void);
void Display1();
signed char Convert(int K);
void Password();
void GPIO_Configure();
void PWM_Config(int goc);
int Map(int x, int inMin, int inMax, int outMin, int outMax); 
void Caculor();
void Check();
#endif
