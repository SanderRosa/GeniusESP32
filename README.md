# 🕹️ Genius IoT ESP32 — Sistema Embarcado em Tempo Real

Uma recriação moderna do clássico jogo Genius (Simon) implementada em hardware embarcado ESP32. O sistema atua como uma Máquina de Estados Finitos com controle multitarefa cooperativo e um servidor Web em tempo real integrado.

## 🚀 Funcionalidades
- **Máquina de Estados Finitos (FSM)**: Controle rígido do fluxo de jogo (Aguardando, Correto, Errado, Game Over).
- **Multitarefa Cooperativa**: Uso de `millis()` (não-bloqueante) para debounce de botões e leitura simultânea sem congelar a CPU.
- **Memória Estática Previsível**: Buffers de arrays fixos garantindo zero alocação dinâmica, evitando travamentos por fragmentação de RAM.
- **Servidor Web Embarcado**: O ESP32 atua como Access Point, servindo uma interface web HTML/CSS/JS nativa para monitoramento e controle remoto.

## 🛠️ Tecnologias Utilizadas
- **C++ (Arduino Core)** (Controle fino e eficiente de hardware)
- **ESP32** (Microcontrolador com WiFi nativo)
- **HTML / CSS / JavaScript** (Interface web IoT hospedada no ESP32)
- **Componentes Físicos**: LEDs, Buzzer, Botões táteis.

## ⚙️ Como Executar
1. Carregue o arquivo `Genius_ESP32.ino` na IDE do Arduino.
2. Selecione a placa baseada no ESP32.
3. Compile e envie (Upload) o firmware para a placa via USB.
4. Conecte os componentes (LEDs, botões e buzzer) aos pinos mapeados no código.
5. Conecte-se à rede WiFi gerada pelo ESP32 para visualizar a interface web embarcada no navegador.

## 📸 Demonstração
*(Ver imagens na pasta extra_files)*
