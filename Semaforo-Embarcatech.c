#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// Definição dos pinos dos LEDs
#define RED_LED_PIN 11
#define YELLOW_LED_PIN 12
#define GREEN_LED_PIN 13

// Variável para armazenar o estado atual do semáforo
typedef enum {
    RED,
    YELLOW,
    GREEN
} traffic_light_state_t;

traffic_light_state_t current_state = RED;

// Função de callback do temporizador
bool repeating_timer_callback(struct repeating_timer *t) {
    // Desliga todos os LEDs
    gpio_put(RED_LED_PIN, 0);
    gpio_put(YELLOW_LED_PIN, 0);
    gpio_put(GREEN_LED_PIN, 0);

    // Altera o estado do semáforo
    switch (current_state) {
        case RED:
            gpio_put(RED_LED_PIN, 1); // Acende o LED vermelho
            current_state = YELLOW;     // Próximo estado será amarelo
            break;
        case YELLOW:
            gpio_put(YELLOW_LED_PIN, 1); // Acende o LED amarelo
            current_state = GREEN;          // Próximo estado será verde
            break;
        case GREEN:
            gpio_put(GREEN_LED_PIN, 1); // Acende o LED verde
            current_state = RED;       // Próximo estado será vermelho
            break;
    }
    return true; // Retorna true para continuar o temporizador
}

int main() {
    // Inicializa o sistema
    stdio_init_all();

    // Configura os pinos dos LEDs como saída
    gpio_init(RED_LED_PIN);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);
    
    gpio_init(YELLOW_LED_PIN);
    gpio_set_dir(YELLOW_LED_PIN, GPIO_OUT);
    
    gpio_init(GREEN_LED_PIN);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);

    // Cria um temporizador que chama a função de callback a cada 3000 ms
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop principal
    while (true) {
        // Imprime uma mensagem a cada segundo
        printf("Projeto em produção...\n");
        sleep_ms(1000);
    }

    return 0;
}