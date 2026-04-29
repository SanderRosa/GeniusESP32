# 🎮 Genius IoT ESP32 (Simon Says)

Este projeto é uma implementação moderna e robusta do clássico jogo **Genius** (Simon Says) para **ESP32**. Ele utiliza **Programação Orientada a Objetos (POO)** e uma **interface Web** responsiva com design premium, sendo ideal para demonstrações acadêmicas e ensino de IoT.

Esta versão foi otimizada para ser **100% compatível com a Arduino IDE**, mantendo todos os arquivos na mesma pasta para evitar erros de compilação e linker.

## 🌟 Destaques do Projeto
- **Arquitetura POO**: Código modular e organizado em classes reutilizáveis.
- **Não Bloqueante**: Uso intensivo de `millis()` para garantir que o servidor web e o LED funcionem simultaneamente sem travamentos.
- **Interface Web Premium**: Design com efeitos de vidro (Glassmorphism) e feedback em tempo real.
- **Conectividade Total**: Projetado para conectar-se ao Hotspot do celular, permitindo apresentações em qualquer lugar sem depender de Wi-Fi local.

---

## 🛠️ Requisitos
- **Hardware**: ESP32 (qualquer modelo) + Cabo USB.
- **LED**: Utiliza o LED interno (Pino 2) por padrão (ajustável no código).
- **Software**: Arduino IDE com suporte a ESP32 instalado.

---

## 🚀 Guia de Uso (Passo a Passo)

### 1. Instalação
1. Baixe todos os arquivos e coloque-os em uma pasta chamada `Genius_ESP32`.
2. Abra o arquivo `Genius_ESP32.ino` na Arduino IDE.

### 2. Configuração do Wi-Fi
No arquivo `Genius_ESP32.ino`, altere as seguintes linhas com os dados do roteador ou hotspot do seu celular:
```cpp
const char* ssid = "NOME_DO_HOTSPOT";
const char* password = "SENHA_DO_HOTSPOT";
```

### 3. Upload
1. Conecte o ESP32 ao seu computador.
2. Na Arduino IDE, selecione a placa (ex: `DOIT ESP32 DEVKIT V1`) e a porta COM correta.
3. Clique em **Upload**.

### 4. Execução
1. Abra o **Serial Monitor** (Velocidade: 115200 baud).
2. O ESP32 exibirá o endereço IP após conectar (ex: `192.168.43.15`).
3. Conecte seu computador/celular no **mesmo Wi-Fi/Hotspot**.
4. No navegador, digite o IP exibido.

---

## 📁 Arquivos do Projeto
Para garantir compatibilidade com a Arduino IDE, todos os arquivos devem estar na raiz da pasta:
- **`Genius_ESP32.ino`**: Ponto de entrada e configuração.
- **`LEDController.h / .cpp`**: Controle do hardware e efeitos do LED.
- **`SequenceManager.h / .cpp`**: Geração e gerenciamento da sequência aleatória.
- **`GameController.h / .cpp`**: Máquina de estados principal do jogo.
- **`WebServerHandler.h / .cpp`**: Servidor HTTP e endpoints da API.
- **`web_ui.h`**: Interface HTML/CSS/JS moderna embutida.

---
> [!NOTE]
> Todos os arquivos estão na mesma pasta para evitar o erro "undefined reference" comum na Arduino IDE ao usar subpastas.
