#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/irq.h"
#include "hardware/adc.h"
#include "pico/multicore.h"
#include "hardware/flash.h"

#define TIMER_INTERVAL_US 1000000
#define START_PIN 2
#define STOP_PIN 3
#define ADC_PIN 26
#define DATA_FLASH_START (256 * 1024) //dejamos 256kb al inicio para el programa, debe estar alineado a un sector de 4096 bytes
#define DATA_AVAILABLE_FLASH_SIZE  (2 * 1024 * 1024 - DATA_FLASH_START) // espacio que podemos ocupar, debe ser multiplo de 4096
#define BUFFER_SIZE 4096 // debe ser múltiplo de 256 bytes

uint32_t start_time = 0;
uint32_t elapsed_time = 0;

void start_timer_interrupt_handler(uint gpio, uint32_t events) {
    start_time = time_us_32();  // almacenamos el tiempo actual
}

void stop_timer_interrupt_handler(uint gpio, uint32_t events) {
    if (start_time != 0) {
        elapsed_time = time_us_32() - start_time;
        printf("Elapsed Time: " + elapsed_time);
        start_time = 0;  // Restablecer para el próximo ciclo
    }
}

//quizá cambiar por floats
uint32_t map(uint32_t au32_IN, uint32_t au32_INmin, uint32_t au32_INmax, uint32_t au32_OUTmin, uint32_t au32_OUTmax) {
    return ((((au32_IN - au32_INmin)*(au32_OUTmax - au32_OUTmin))/(au32_INmax - au32_INmin)) + au32_OUTmin);
}

// Builtin XIP flash
void print_buf(const uint8_t *buf, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        printf("%02x", buf[i]);
        if (i % 16 == 15)
            printf("\n");
        else
            printf(" ");
    }
}

void appendUInt16ToBuffer(uint16_t value, uint8_t *buf, size_t *index) {
    buf[*index] = (value >> 8) & 0xFF;      // Byte más significativo
    buf[*index + 1] = value & 0xFF;         // Byte menos significativo
    *index += 2;
}

uint16_t getUInt16FromBuffer(uint8_t *buf, size_t index) {
    uint16_t result = ((uint16_t)buf[index] << 8) | buf[index + 1];
    return result;
}


//Core 1 - ADC Reading

void core1_entry() {
    adc_init();
    adc_gpio_init(ADC_PIN);
    adc_select_input(0); // 0 - 26, 1 - 27, 2 - 28
    const float conversion_factor = 3.3f / (1 << 12);

    while (true) {
        uint16_t adc_value = adc_read();
        uint16_t voltage = adc_value * conversion_factor;
        uint32_t pressure = map(voltage, 0.5, 3.3, 0, 1600);
        printf(adc_value);
    }
    
}

int main() {

    stdio_init_all();
    sleep_ms(2000);

    gpio_set_irq_enabled_with_callback(START_PIN, GPIO_IRQ_EDGE_RISE, true, &start_timer_interrupt_handler);
    gpio_set_dir(START_PIN, GPIO_IN);
    gpio_pull_up(START_PIN);

    gpio_set_irq_enabled_with_callback(STOP_PIN, GPIO_IRQ_EDGE_RISE, true, &stop_timer_interrupt_handler);
    gpio_set_dir(STOP_PIN, GPIO_IN);
    gpio_pull_up(STOP_PIN);

    // Borramos sector a usar
    //flash_range_erase(DATA_FLASH_START, );

    while (true) {
    
    }
}