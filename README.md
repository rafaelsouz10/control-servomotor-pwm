# Controle de servomotor por PWM

---

## Descrição do Projeto

Este projeto implementa o controle de um **servomotor** utilizando **PWM** na **Raspberry Pi Pico W**. O código inicializa o servomotor no **GPIO 22**, permitindo movimentação entre os ângulos **0°, 90° e 180°**, seguido de um movimento contínuo e suave entre **0° e 180°**.  

![image](https://github.com/user-attachments/assets/2c04047a-f957-4449-ac28-aea841a564c5)

## 🚀 Funcionalidades  
✅ Configuração do **PWM** no GPIO 22 com frequência de **50 Hz**  
✅ Movimentação inicial entre **0°, 90° e 180°** com **5s de pausa** entre cada posição  
✅ Movimentação contínua e suave de **0° a 180° e vice-versa**  
✅ Impressão no **serial monitor** indicando mudanças de posição  

---

## Requisitos

- **Microcontrolador**: Raspberry Pi Pico ou Raspberry Pi Pico W (opcional)
- **Placa de Desenvolvimento:** BitDogLab (opcional).
- **Conta Criada no Wokwi Simulator**: [Wokwi](https://wokwi.com/).
- **Editor de Código**: Visual Studio Code (VS Code).
- **SDK do Raspberry Pi Pico** configurado no sistema.
- Ferramentas de build: **CMake** e **Ninja**.

---

## Instruções de Uso

### 1. Clone o Repositório

Clone o repositório para o seu computador:
```bash
git clone https://github.com/rafaelsouz10/control-servomotor-pwm.git
cd control-servomotor-pwm
code .
```
---

### 2. Instale as Dependências

Certifique-se de que o SDK do Raspberry Pi Pico está configurado corretamente no VS Code. As extensões recomendadas são:

- **C/C++** (Microsoft).
- **CMake Tools**.
- **Wokwi Simulator**.
- **Raspberry Pi Pico**.

---

### 3. Configure o VS Code

Abra o projeto no Visual Studio Code e siga as etapas abaixo:

1. Certifique-se de que as extensões mencionadas anteriormente estão instaladas.
2. No terminal do VS Code, compile o código clicando em "Compile Project" na interface da extensão do Raspberry Pi Pico.
3. O processo gerará o arquivo `.uf2` necessário para a execução no hardware real.

---

### 4. Teste no Simulador Wokwi Integrado ao VS Code

Após ter configurado o VS Code conforme descrito no item 3, siga os passos abaixo para simular o projeto:

1. Abra o arquivo `diagram.json` no Visual Studio Code.
2. Clique no botão "Play" disponível na interface.
3. Divirta-se interagindo com os componentes disponíveis no simulador integrado!

---

### 5. Teste no Hardware Real

#### Utilizando a Placa de Desenvolvimento BitDogLab com Raspberry Pi Pico W:

1. Conecte a placa ao computador no modo BOTSEEL:
   - Pressione o botão **BOOTSEL** (localizado na parte de trás da placa de desenvolvimento) e, em seguida, o botão **RESET** (localizado na frente da placa).
   - Após alguns segundos, solte o botão **RESET** e, logo depois, solte o botão **BOOTSEL**.
   - A placa entrará no modo de programação.

2. Compile o projeto no VS Code utilizando a extensão do [Raspberry Pi Pico W](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico):
   - Clique em **Compile Project**.

3. Execute o projeto clicando em **Run Project USB**, localizado abaixo do botão **Compile Project**.

---

### 📌 6. Conexões e Esquemático 

#### 🔧 Componentes Necessários  
- ✅ **Raspberry Pi Pico W**  
- ✅ **Servomotor SG90/MG995 (ou equivalente)**  

#### 🔌 Esquema de Ligação  

| Componente | Pino Pico W |
|------------|------------|
| Servo VCC  | VCC         |
| Servo GND  | GND        |
| Servo Sinal | GPIO 22   |

---

### 🛠️ 7. Funcionamento do Sistema    

#### 🔹 1. Configuração do PWM  
A função `pwm_setup()` configura o **GPIO 22** para operar com PWM na frequência de **50 Hz** (20ms por ciclo).  

#### 🔹 2. Movimentação Inicial  
A função `set_servo_angle()` posiciona o servo em **180°, 90° e 0°** para determinar o **ciclo de trabalho (duty cycle)** adequado.  

Sabendo que o período total do PWM é 20.000μs (20ms), já que a frequência do PWM está configurada para 50 Hz, temos então que:

| Ângulo | Pulso (μs) | Cálculo                                         | Duty Cycle (%) |
|--------|------------|-------------------------------------------------|----------------|
|   -    |     -      | DC(%) = (Pulso Ativo(μs)/Período Total(μs))/100 |        -       |
| 0°     | 500        | (500/20000)×100  | 2.5%          |
| 90°    | 1470       | (1470/20000)×100 | 7.35%         |
| 180°   | 2400       | (2400/20000)×100 | 12%           |
 


Cada posição é mantida por **5 segundos** antes da próxima movimentação.  

#### 🔹 3. Movimentação Contínua  
Após a movimentação inicial, o código entra em um `while (true)` que move o servo de **0° a 180° e de volta para 0°**, ajustando o PWM gradualmente (**5μs por vez**) a cada **10ms** para um movimento mais suave.  

#### 🔹 4. Monitoramento via Serial  
Mensagens são exibidas no **terminal** (`printf()`) informando as mudanças de posição do servo.  

---


### 8. Vídeo Demonstrativo

Click [AQUI](https://drive.google.com/file/d/1EcFzGqHcQVa54JidrvR_63xwFbsR92mS/view?usp=sharing) para acessar o link do Vídeo Ensaio
