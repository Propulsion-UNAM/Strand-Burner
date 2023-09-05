#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/irq.h"

#define TIMER_INTERVAL_US 1000000
#define START_PIN 2
#define STOP_PIN 3

uint32_t start_time = 0;

void timer_callback() {
    static bool led_on = false;
    gpio_put(PICO_DEFAULT_LED_PIN, led_on);
    led_on = !led_on;
}

void start_timer_interrupt_handler(uint gpio, uint32_t events) {
    start_time = time_us_32();  // almacenamos el tiempo actual
}

void stop_timer_interrupt_handler(uint gpio, uint32_t events) {
    if (start_time != 0) {
        uint32_t stop_time = time_us_32();
        uint32_t elapsed_time = stop_time - start_time;
        printf("Tiempo transcurrido: %u microsegundos\n", elapsed_time);
        start_time = 0;  // Restablecer para el próximo ciclo
    }
}


int main() {
    gpio_set_irq_enabled_with_callback(START_PIN, GPIO_IRQ_EDGE_RISE, true, &start_timer_interrupt_handler);
    gpio_set_dir(START_PIN, GPIO_IN);
    gpio_pull_up(START_PIN);

    gpio_set_irq_enabled_with_callback(STOP_PIN, GPIO_IRQ_EDGE_RISE, true, &stop_timer_interrupt_handler);
    gpio_set_dir(STOP_PIN, GPIO_IN);
    gpio_pull_up(STOP_PIN);

    while (true) {
        
    }
}