#include <stdio.h>
#include "pico/stdlib.h"
#include <inc/pwm_config.h>

int main() {
    stdio_init_all();  // Inicializa a comunicação serial para printf
    pwm_setup();    //Inicializa as configurações pra o PWM

    // Move o servomotor de 180 graus por 5s, 90 graus por 5s 0 grau por 5s
    set_servo_angle(); //slice_num definido em pwm_setup()

    // Inicia a movimentação suave do servomotor entre 0 e 180 graus
    duty_cycle = 500;  // Começa em 0 graus (500μs)
    while (true) { 
        // Move de 0 a 180 graus
        while (duty_cycle <= 2400) {
            duty_cycle += 5;  // Incrementa o ciclo ativo em 5μs
            pwm_set_chan_level(slice_num, PWM_CHAN_A, duty_cycle); //canal pwm será incrementado +5μs o duty cycle até chegar a 2400μs (180 graus) 
            sleep_ms(10);     // Pausa de 10ms entre os ajustes
        }
        printf("Servo movido de 0 para 180 graus\n");

        // Move de 180 a 0 graus
        while (duty_cycle >= 500) {
            duty_cycle -= 5;  // Decrementa o ciclo ativo em 5μs
            pwm_set_chan_level(slice_num, PWM_CHAN_A, duty_cycle); //canal pwm será decrementado +5μs o duty cycle até chegar a 500μs (0 graus)
            sleep_ms(10);     // Pausa de 10ms entre os ajustes
        }
        printf("Servo movido de 180 para 0 graus\n");
    }
    return 0;
}
