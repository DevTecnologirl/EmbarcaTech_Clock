//Camilly Duarte 
#include "pico/stdlib.h"

#define LED_PIN 20
#define BUTTON_A 5 
#define BUTTON_B 6
#define TIMER_INTERVAL 100

volatile uint button_count = 0;
volatile bool led_blinking = false;
volatile uint freq = 10;
volatile uint32_t blink_start_time = 0;

void timer_callback(uint gpio, uint32_t events) {
    if (gpio == BUTTON_A && !gpio_get(BUTTON_A)) {
        button_count++;
        printf("contagem de apertos: %d\n", button_count);
        if (button_count >= 5) {
            led_blinking = true;
            blink_start_time = time_us_32();
            button_count = 0;
        }
    }

    if (gpio == BUTTON_B && !gpio_get(BUTTON_B)) {
        freq = (freq == 10) ? 1 : 10;
        printf("Frequência alterada para %d Hz\n", freq);
    }
}

int main() {
    stdio_init_all();
    
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);
    
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &timer_callback);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &timer_callback);
    
    while (true) {
        if (led_blinking) {
            if ((time_us_32() - blink_start_time) < 10000000) {
                gpio_put(LED_PIN, 1);
                sleep_ms(1000 / freq);
                gpio_put(LED_PIN, 0);
                sleep_ms(1000 / freq);
            } else {
                led_blinking = false;
            }
        }
        
        sleep_ms(10);
    }
}
