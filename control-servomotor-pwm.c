#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include <stdio.h>

#define SERVO_PIN 22 

// Função para configurar o ângulo do servomotor
void set_servo_angle(uint slice_num, uint angle) {
    uint16_t duty_cycle;
    if (angle == 0) {
        // 0 graus -> 500μs, com período de 20ms -> Duty Cycle = 500 / 20000 = 0.025% 
        duty_cycle = 500;  // Cálculo para 0 graus
        printf("Servo movido para 0 graus\n");
    } else if (angle == 90) {
        // 90 graus -> 1470μs, com período de 20ms -> Duty Cycle = 1470 / 20000 = 0.0735% 
        duty_cycle = 1470; // Cálculo para 90 graus
        printf("Servo movido para 90 graus\n");
    } else if (angle == 180) {
        // 180 graus -> 2400μs, com período de 20ms -> Duty Cycle = 2400 / 20000 = 0.12% 
        duty_cycle = 2400; // Cálculo para 180 graus
        printf("Servo movido para 180 graus\n");
    }
    pwm_set_chan_level(slice_num, PWM_CHAN_A, duty_cycle);
}

int main() {
    stdio_init_all();  // Inicializa a comunicação serial para printf

    // Configura o GPIO 22 (servoPin) como PWM
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);

    // Configura a frequência do PWM para 50 Hz
    pwm_set_clkdiv(slice_num, 125.0f); // (125MHz / (20ms * 20000) = 50 Hz)
    pwm_set_wrap(slice_num, 20000);    // Período de 20 ms (equivalente a 50 Hz)
    pwm_set_enabled(slice_num, true);  // Habilita o PWM como true

    // Move o servomotor para 180 graus e espera 5 segundos
    set_servo_angle(slice_num, 180);
    sleep_ms(5000);

    // Move o servomotor para 90 graus e espera 5 segundos
    set_servo_angle(slice_num, 90);
    sleep_ms(5000);

    // Move o servomotor para 0 graus e espera 5 segundos
    set_servo_angle(slice_num, 0);
    sleep_ms(5000);

    // Inicia a movimentação suave do servomotor entre 0 e 180 graus
    uint16_t duty_cycle = 500;  // Começa em 0 graus (500μs)
    while (true) {
        
        // Move de 0 a 180 graus
        while (duty_cycle <= 2400) {
            pwm_set_chan_level(slice_num, PWM_CHAN_A, duty_cycle);
            duty_cycle += 5;  // Incrementa o ciclo ativo em 5μs
            sleep_ms(10);     // Pausa de 10ms entre os ajustes
        }
        printf("Servo movido para 180 graus\n");

        // Move de 180 a 0 graus
        while (duty_cycle >= 500) {
            pwm_set_chan_level(slice_num, PWM_CHAN_A, duty_cycle);
            duty_cycle -= 5;  // Decrementa o ciclo ativo em 5μs
            sleep_ms(10);     // Pausa de 10ms entre os ajustes
        }
        printf("Servo movido para 0 graus\n");
    }

    return 0;
}
