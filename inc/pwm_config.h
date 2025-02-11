#ifndef PWM_CONFIG_H
#define PWM_CONFIG_H

#include "hardware/pwm.h"

#define SERVO_PIN 22 

int angles[3] = {180, 90, 0}; //vetor com os ângulos a serem rodados no servomotor 180 graus, 90 graus e 0 graus
uint slice_num; //Variável para o slice associado ao pino do servomotor
uint16_t duty_cycle; //variável para ser salvo a cada ciclo de trabalho utilizado

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
void set_servo_angle() {

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

#endif