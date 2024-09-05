/*
 * operations.c
 *
 *  Created on: Jul 28, 2024
 *      Author: Abhisek
 */

#include<operations.h>
#include<usart.h>
#include<adc.h>

void print_menu(void) {
    UART2_SendString("STM32 ADC Control Menu:\r\n");
    UART2_SendString("1. Start ADC Conversion\r\n");
    UART2_SendString("2. Trigger ADC Interrupt\r\n");
    UART2_SendString("3. Exit\r\n");
}

void handle_option(char option) {
    switch (option) {
        case '1':
            start_adc_conversion();
            break;
        case '2':
            trigger_adc_interrupt();
            break;
        case '3':
            exit_program();
            break;
        default:
            UART2_SendString("Invalid Option! Please enter '1', '2', or '3'\r\n");
            break;
    }
}

void start_adc_conversion(void) {
    UART2_SendString("Starting ADC Conversion...\r\n");
    adc_init();
    adc_start_conversion();
    uint32_t value = adc_read();
    char buffer[10];
    sprintf(buffer, "%lu\n\r", value);
    UART2_SendString(buffer);

    while (1) {
        UART2_SendString("Continue ADC Conversion? (y/n): ");
        char continue_option = receiverdata();
        UART2_SendChar(continue_option);
        UART2_SendString("\r\n");
        if (continue_option == 'n') {
            break;
        } else if (continue_option == 'y') {
            adc_start_conversion();
            value = adc_read();
            sprintf(buffer, "%lu\n\r", value);
            UART2_SendString(buffer);
        } else {
            UART2_SendString("Invalid Option! Please enter 'y' or 'n'\r\n");
        }
    }
}

void trigger_adc_interrupt(void) {
    UART2_SendString("Triggering ADC Interrupt...\r\n");
    adc_init();
    adc_int_init();
    adc_start_conversion();
}

void exit_program(void) {
    UART2_SendString("Exiting...\r\n");
    while(1);
}
