/*
 * adc.c
 *
 *  Created on: Jul 28, 2024
 *      Author: Abhisek
 */


#include<adc.h>
#include<usart.h>

// ADC Configuration and functions
#define PA0_ADC_MODE (3 << 0)
#define ADC_SEQ_LEN_1 0

void adc_init(void) {
    GPIOA->MODER |= PA0_ADC_MODE;
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    ADC1->SQR1 = ADC_SEQ_LEN_1;
    ADC1->CR2 |= ADC_CR2_ADON;
}

void adc_int_init(void) {
    ADC1->CR1 |= ADC_CR1_EOCIE;
    NVIC_EnableIRQ(ADC_IRQn);
}

void adc_start_conversion(void) {
    ADC1->CR2 |= ADC_CR2_SWSTART;
}

uint32_t adc_read(void) {
    while (!(ADC1->SR & ADC_SR_EOC));
    return (ADC1->DR);
}

void ADC_IRQHandler(void) {
    if ((ADC1->SR & ADC_SR_EOC) != 0) {
        ADC1->SR &= ~ADC_SR_EOC;
        volatile uint32_t value = ADC1->DR;
        char buffer[10];
        sprintf(buffer, "%lu\n\r", value);
        UART2_SendString(buffer);
    }
}
int __io_putchar(int ch) {
    UART2_SendChar(ch);
    return ch;
}
