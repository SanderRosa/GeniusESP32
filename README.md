# 🕹️ Genius IoT ESP32 — Sistema Embarcado em Tempo Real

> Uma recriação moderna do clássico jogo Genius (Simon) implementada em hardware embarcado ESP32, modelada como uma Máquina de Estados Finitos com controle multitarefa cooperativo e servidor Web integrado.

---

## 🚀 Visão Geral e Contexto de Engenharia

Este projeto simula fielmente o comportamento de **sistemas embarcados de tempo real** (como controladores de equipamentos médicos, robótica ou CLPs industriais). 

O desafio de engenharia aqui é o gerenciamento de múltiplos eventos físicos concorrentes (leituras de botões com ruídos elétricos, controle de LEDs, buzzer para efeitos sonoros e um servidor web) sem permitir que o processador fique ocioso ou perca eventos cruciais de segurança.

---

## 🛠️ Tecnologias Utilizadas e Justificativa Técnica

### 1. Linguagem e Framework: C++ (Arduino Core)
* **Por que C++?** É a linguagem padrão do mercado eletrônico industrial. Fornece total controle fino de hardware, consumo de energia eficiente e acesso direto a registradores, permitindo otimizações a nível de hardware que linguagens interpretadas não oferecem.

### 2. Multitarefa Cooperativa com `millis()` (Não Bloqueante)
* Em sistemas embarcados tradicionais, o uso de `delay(1000)` "congela" completamente o fluxo da CPU por 1 segundo inteiro. Durante este congelamento, se o operador pressionar um botão de emergência ou ocorrer uma falha crítica, a CPU não detectará o sinal.
* A técnica do `millis()` (baseada no timer interno do ESP32) permite gerenciar loops assíncronos e temporizados. Assim, o código lê botões em microsegundos e gerencia o tempo ativo dos LEDs e sons de forma "simultânea".
* **Debounce via software:** Para evitar o efeito de "bounce" (trepidação) dos botões mecânicos físicos que geram ruídos oscilatórios de tensão rápidos, o firmware implementa o debounce via software com atraso de confirmação de cerca de 50ms não-bloqueantes.

### 3. Máquina de Estados Finitos (FSM)
* O jogo é modelado formalmente através de estados bem definidos:
  * `GERANDO_SEQUENCIA`
  * `ESPERANDO_JOGADOR`
  * `JOGADA_CORRETA`
  * `JOGADA_ERRADA`
  * `GAME_OVER`
* Essa modelagem robusta garante previsibilidade matemática de funcionamento, impedindo que o hardware execute comandos inválidos ou entre em estados indeterminados.

### 4. Memória Estática Previsível
* Toda a lógica de jogo e buffers de sequência foram construídos em **arrays estáticos e de tamanho fixo**, evitando alocações dinâmicas de memória (como `new`, `malloc` ou uso excessivo da classe `String`) que fragmentam a RAM limitada do chip e causam travamentos espontâneos a longo prazo.

### 5. Servidor Web Embarcado (IoT)
* O ESP32 atua como um ponto de acesso sem fio (Access Point / Station), servindo uma interface web embarcada em tempo real. Isso permite que qualquer smartphone ou computador na mesma rede visualize o progresso do jogo e controle configurações remotamente sem cabos.

---

## 📊 Arquitetura do Software

O código foi projetado sob os pilares da programação modular em C++:
- `Genius_ESP32.ino`: Ponto de entrada e loop principal de controle.
- `GameController`: Gerencia o fluxo de estados (FSM) e validações.
- `LEDController`: Controle de baixo nível dos pinos GPIO correspondentes aos LEDs.
- `SequenceManager`: Algoritmo de geração randômica e manipulação da sequência de cores.
- `WebServerHandler` & `web_ui.h`: Hospedagem do servidor HTTP e da interface HTML/CSS/JS moderna embutida no próprio chip.
