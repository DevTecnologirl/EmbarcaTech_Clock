//Camilly Duarte
#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>
#include "hardware/uart.h"

#define UART0_TX_PIN 0
#define UART0_RX_PIN 1
#define UART1_TX_PIN 5
#define UART1_RX_PIN 6

char info[50];

int main() {
    stdio_init_all(); // Inicializa a comunicação com o console

    // Configuração das interfaces UART0 e UART1
    uart_init(uart0, 115200);
    uart_init(uart1, 115200);
    
    gpio_set_function(UART0_TX_PIN, GPIO_FUNC_UART); // TX da UART0
    gpio_set_function(UART0_RX_PIN, GPIO_FUNC_UART); // RX da UART0
    gpio_set_function(UART1_TX_PIN, GPIO_FUNC_UART); // TX da UART1
    gpio_set_function(UART1_RX_PIN, GPIO_FUNC_UART); // RX da UART1

    // Habilita ou desabilita o FIFO (false para processamento imediato)
    uart_set_fifo_enabled(uart0, true);
    uart_set_fifo_enabled(uart1, true);

    printf("Digite a informação a enviar: ");
    scanf("%49s", info); // Lê uma string e limita para evitar estouro de buffer

    uart_puts(uart0, info); // Envia pela UART0
    sleep_ms(100);

    if (uart_is_readable(uart1)) {
        printf("UART1 está pronta para leitura!\n");

        char info2[50];
        int i = 0;

        while (uart_is_readable(uart1) && i < sizeof(info2) - 1) {
            info2[i++] = uart_getc(uart1);
        }
        info2[i] = '\0';
        sleep_ms(50);

        printf("\nMensagem recebida: %s\n", info);
    } else {
        printf("Nenhuma mensagem recebida\n");
    }
}
