#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include <stdio.h>

#define SERVO_PIN 22 

int angles[3] = {180, 90, 0}; //vetor com os ângulos a serem rodados no servomotor 180 graus, 90 graus e 0 graus
uint16_t duty_cycle; //variável para ser salvo a cada ciclo de trabalho utilizado
uint slice_num; //Variável para o slice associado ao pino do servomotor

//Função para Inicializa as configurações pra o PWM
void pwm_setup(){
    // Configura o GPIO 22 (servoPin) como PWM
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(SERVO_PIN);

    // Configura a frequência do PWM para 50 Hz
    pwm_set_clkdiv(slice_num, 125.0f); // (125MHz / (20ms * 20000) = 50 Hz)
    pwm_set_wrap(slice_num, 20000);    // Período de 20 ms (equivalente a 50 Hz)
    pwm_set_enabled(slice_num, true);  // Habilita o PWM como true
}

// Função para configurar o ângulo do servomotor
void set_servo_angle(uint slice_num) {
    
    for (int i = 0; i < 3; i++){    //roda cada clico do vetor angles
        if (angles[i] == 0) {
            // 0 graus -> 500μs, com período de 20ms -> Duty Cycle = 500 / 20000 = 0.025% 
            duty_cycle = 500;  // ciclo de trabalo para 0 graus
            printf("Servo movido para 0 graus\n");
        } else if (angles[i] == 90) {
            // 90 graus -> 1470μs, com período de 20ms -> Duty Cycle = 1470 / 20000 = 0.0735% 
            duty_cycle = 1470; // ciclo de trabalo para 90 graus
            printf("Servo movido para 90 graus\n");
        } else if (angles[i] == 180) {
            // 180 graus -> 2400μs, com período de 20ms -> Duty Cycle = 2400 / 20000 = 0.12% 
            duty_cycle = 2400; // ciclo de trabalo para 180 graus
            printf("Servo movido para 180 graus\n");
        }
        pwm_set_chan_level(slice_num, PWM_CHAN_A, duty_cycle); //configura o canal pwm para cada ciclo de trabalho referente ao angulo
        sleep_ms(5000); //espera 5s para cada ciclo rodado do for
    }
}

int main() {
    stdio_init_all();  // Inicializa a comunicação serial para printf
    pwm_setup();    //Inicializa as configurações pra o PWM

    // Move o servomotor de 180 graus por 5s, 90 graus por 5s 0 grau por 5s
    set_servo_angle(slice_num);

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
