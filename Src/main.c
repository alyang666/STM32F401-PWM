/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include "stm32f4xx.h"




/* Partie 1 Timer

int main(void)
{
    GPIO_TypeDef * PA = GPIOA;

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Configurer PA5 en fonction alternance
    PA->MODER &= ~GPIO_MODER_MODER5_Msk;
    PA->MODER |= GPIO_MODER_MODER5_1;
    PA->AFR[0] |= (1 << 4*5);

    SystemInit();
    SystemCoreClockUpdate();

    // Configuration de TIM2 CH1
    TIM2->BDTR |= TIM_BDTR_MOE;
    TIM2->CCMR1 |= (6 << TIM_CCMR1_OC1M_Pos);    // Set output mode and PWM1 mode
    // TIM2->CCMR1 |= (6 << 4);
    // TIM2->CCMR1 |= (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2);
    TIM2->CCER |= TIM_CCER_CC1E;                 // Enable output

    TIM2->PSC = (SystemCoreClock / 100000) - 1;  // Give 10us time base (100kHz)

    TIM2->EGR |= TIM_EGR_UG ;                    // Force update
    TIM2->SR &= ~TIM_SR_UIF;                     // Clear UIF
    TIM2->CR1 &= ~TIM_CR1_OPM;                   // Mettre compteur compte en boucle
    TIM2->CR1 |= TIM_CR1_CEN;                    // Activer compteur CR1
    TIM2->ARR = 0;                               // Clear time max count
    TIM2->CNT = 0;                               // Reset counter
    TIM2->ARR = 999;                             // Comptez 1000 fois

    int  i;
    uint32_t k = 0, add = 0;

    while(1)
    {
      TIM2->CCR1 = add;
      for(i=0;i<30000;i++);         // Maintenir la durée d’une intensité 300ms
      add += k;
      k++;                          // Incrémenter l'augmentation
    }
    return 0;
}

*/




/* Partie 2 PWM

void delay_ms(uint32_t ms);

int main(void)
{
    GPIO_TypeDef * PA = GPIOA;

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;


    PA->MODER &= ~GPIO_MODER_MODER5_Msk;
    PA->MODER |= GPIO_MODER_MODER5_0;

    SystemInit();
    SystemCoreClockUpdate();


    TIM5->PSC = (SystemCoreClock / 1000) - 1;  //  Give 1ms time base


    TIM5->EGR = 1;                             // Force update
    TIM5->ARR = 0;                             // Clear time max count
    TIM5->SR &= ~0x1;                          // Clear UIF
    TIM5->CNT = 0;                             // Reset counter
    TIM5->CR1 &= ~TIM_CR1_OPM;                 // Mettre compteur compte en boucle
    TIM5->CR1 |= TIM_CR1_CEN;                  // Activer CR1

while(1)
{
	PA->ODR |= GPIO_ODR_OD5;                   // led on
	delay_ms(500);
	PA->ODR &= ~GPIO_ODR_OD5;	               // led off
	delay_ms(500);
}
return 0;
}


void delay_ms(uint32_t ms)
{
  TIM5->ARR = ms;                     // Set time max count
  TIM5->SR &= ~0x1;                   // Clear UIF
  TIM5->CNT = 0;                      // Reset counter
  while(!(TIM5->SR & TIM_SR_UIF));    // Attendre le bit UIF à 1 (overflow)
}
*/




/* Partie 3 Capture mode */

int main(void)
{
    GPIO_TypeDef * PB = GPIOB;

    /* Activer GPIOB, GPIOC et Timer */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

    /* Configurer PB en utilisant l'alternate fonction */
    PB->MODER &= ~GPIO_MODER_MODER7_Msk;
    PB->MODER |= GPIO_MODER_MODER7_1;
    PB->AFR[0] |= (2 << 4*7);

    SystemInit();
    SystemCoreClockUpdate();

    /* Inactive capture mode */
    TIM4->CCER &= ~TIM_CCER_CC1E;
    TIM4->CCER &= ~TIM_CCER_CC2E;

    /* Configuration de TIM4 */
    TIM4->CCMR1 |= (0x10 << TIM_CCMR1_CC1S_Pos);   // Select the active input for TIM4_CCR1 TI2
    TIM4->CCMR1 |= (0x01 << TIM_CCMR1_CC2S_Pos);   // Select the active input for TIM4_CCR2 TI2

    /* Capture every event */
    TIM4->CCMR1 |= (0x0 << TIM_CCMR1_IC1PSC_Pos);
    TIM4->CCMR1 |= (0x0 << TIM_CCMR1_IC2PSC_Pos);
    TIM4->CCMR1 |= (0x0 << TIM_CCMR1_IC2F_Pos);   // Filter

    /* Used both for capture in TIMx_CCR1 and counter clear, active on rising edge */
    TIM4->CCER &= ~TIM_CCER_CC1P;
    TIM4->CCER &= ~TIM_CCER_CC1NP;

    /* Used for capture in TIMx_CCR2, active on falling edge */
    TIM4->CCER |= TIM_CCER_CC2P;
    TIM4->CCER &= ~TIM_CCER_CC2NP;

    // TIM4->SMCR |= (0x110 << TIM_SMCR_TS_Pos);      // Select the valid trigger input of CH2
    // TIM4->SMCR |= TIM_SMCR_SMS_2;                  // Configure the slave mode controller in reset mode

    TIM4->PSC = (SystemCoreClock / 1000) - 1;      // Give 1ms time base (1000Hz)
    TIM4->EGR |= TIM_EGR_UG ;                      // Force update
    TIM4->SR &= ~TIM_SR_UIF;                       // Clear UIF
    TIM4->CR1 &= ~TIM_CR1_OPM;                     // Mettre compteur compte en boucle
    TIM4->CR1 |= TIM_CR1_CEN;                      // Activer compteur CR1
    TIM4->ARR = 0;                                 // Clear time max count
    TIM4->CNT = 0;                                 // Reset counter
    TIM4->ARR = 999;                               // Compter 1000 fois

    TIM4->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E;   // Enable capture mode for CC1 and CC2

    int temp, a, b;

    while(1){
         a = (int)(TIM4->CCR1);
         b = (int)(TIM4->CCR2);
    	 temp = a-b;
    }
    return 0;
}





