#ifndef WEB_UI_H
#define WEB_UI_H

const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Genius ESP32 - Premium Edition</title>
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Outfit:wght@300;500;700;900&display=swap" rel="stylesheet">
    <style>
        :root {
            --bg-dark: #090e1a;
            --bg-card: rgba(30, 41, 59, 0.4);
            --glass-border: rgba(255, 255, 255, 0.08);
            --primary: #6366f1;
            --primary-hover: #4f46e5;
            --success: #10b981;
            --danger: #ef4444;
            --warning: #f59e0b;
            --text-main: #f8fafc;
            --text-muted: #94a3b8;
            
            /* Cores dos Botões Genius */
            --color-1: #ef4444;
            --color-2: #3b82f6;
            --color-3: #10b981;
            --color-4: #f59e0b;
            --color-5: #8b5cf6;
            --color-6: #ec4899;
            --color-7: #06b6d4;
            --color-8: #f97316;
            --color-9: #f8fafc;
        }

        * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
            font-family: 'Outfit', sans-serif;
        }

        body {
            background: radial-gradient(circle at center, #1e1b4b 0%, #090e1a 100%);
            color: var(--text-main);
            min-height: 100vh;
            display: flex;
            align-items: center;
            justify-content: center;
            padding: 20px;
            overflow-x: hidden;
        }

        /* Animações */
        @keyframes shake {
            0%, 100% { transform: translateX(0); }
            20%, 60% { transform: translateX(-10px); }
            40%, 80% { transform: translateX(10px); }
        }

        .shaking {
            animation: shake 0.4s ease-in-out;
        }

        /* Container Principal */
        .game-wrapper {
            width: 100%;
            max-width: 450px;
            perspective: 1000px;
        }

        .card {
            background: var(--bg-card);
            backdrop-filter: blur(16px);
            -webkit-backdrop-filter: blur(16px);
            border: 1px solid var(--glass-border);
            border-radius: 24px;
            padding: 2.5rem;
            box-shadow: 0 25px 50px -12px rgba(0, 0, 0, 0.5);
            text-align: center;
            transition: all 0.5s cubic-bezier(0.4, 0, 0.2, 1);
        }

        h1 {
            font-weight: 900;
            font-size: 2.5rem;
            background: linear-gradient(to right, #818cf8, #c084fc);
            -webkit-background-clip: text;
            -webkit-text-fill-color: transparent;
            margin-bottom: 1.5rem;
            letter-spacing: -0.05em;
        }

        p {
            color: var(--text-muted);
            margin-bottom: 1.5rem;
            font-size: 1.1rem;
        }

        /* Telas */
        .screen {
            display: none;
        }

        .screen.active {
            display: block;
            animation: fadeIn 0.5s ease-out forwards;
        }

        @keyframes fadeIn {
            from { opacity: 0; transform: translateY(10px); }
            to { opacity: 1; transform: translateY(0); }
        }

        /* Formulário Inicial */
        .input-group {
            margin-bottom: 1.5rem;
            text-align: left;
        }

        label {
            display: block;
            margin-bottom: 0.5rem;
            color: var(--text-muted);
            font-size: 0.9rem;
            font-weight: 500;
        }

        input[type="text"] {
            width: 100%;
            background: rgba(15, 23, 42, 0.6);
            border: 1px solid var(--glass-border);
            border-radius: 12px;
            padding: 12px 16px;
            color: var(--text-main);
            font-size: 1rem;
            transition: all 0.3s;
            outline: none;
        }

        input[type="text"]:focus {
            border-color: var(--primary);
            box-shadow: 0 0 0 2px rgba(99, 102, 241, 0.2);
        }

        /* Botões */
        .btn-action {
            background: linear-gradient(135deg, var(--primary), #4f46e5);
            color: white;
            border: none;
            padding: 14px 28px;
            border-radius: 12px;
            font-size: 1.1rem;
            font-weight: 700;
            cursor: pointer;
            transition: all 0.3s;
            width: 100%;
            box-shadow: 0 4px 6px -1px rgba(0, 0, 0, 0.2);
        }

        .btn-action:hover {
            transform: translateY(-2px);
            box-shadow: 0 10px 15px -3px rgba(99, 102, 241, 0.4);
            filter: brightness(1.1);
        }

        /* Display de Dígitos Digitados */
        .input-display {
            background: rgba(15, 23, 42, 0.6);
            padding: 12px;
            border-radius: 12px;
            margin-bottom: 1.5rem;
            min-height: 3.5rem;
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 10px;
            border: 1px dashed var(--glass-border);
        }

        .input-digit {
            background: linear-gradient(135deg, var(--primary), #4f46e5);
            color: white;
            width: 35px;
            height: 35px;
            border-radius: 8px;
            display: flex;
            align-items: center;
            justify-content: center;
            font-weight: 700;
            font-size: 1.2rem;
            animation: popIn 0.2s cubic-bezier(0.175, 0.885, 0.32, 1.275);
            box-shadow: 0 4px 6px -1px rgba(0, 0, 0, 0.2);
        }

        @keyframes popIn {
            0% { transform: scale(0); opacity: 0; }
            100% { transform: scale(1); opacity: 1; }
        }

        /* Grid do Jogo */
        .grid {
            display: grid;
            grid-template-columns: repeat(3, 1fr);
            gap: 16px;
            margin: 1.5rem 0;
        }

        .genius-btn {
            aspect-ratio: 1;
            border: none;
            border-radius: 20px;
            font-size: 1.8rem;
            font-weight: 900;
            color: rgba(255, 255, 255, 0.8);
            cursor: pointer;
            transition: all 0.2s cubic-bezier(0.4, 0, 0.2, 1);
            display: flex;
            align-items: center;
            justify-content: center;
            box-shadow: 0 4px 6px -1px rgba(0, 0, 0, 0.3);
            position: relative;
            overflow: hidden;
        }

        #btn-1 { background: rgba(239, 68, 68, 0.2); border: 2px solid rgba(239, 68, 68, 0.4); color: #f87171; }
        #btn-2 { background: rgba(59, 130, 246, 0.2); border: 2px solid rgba(59, 130, 246, 0.4); color: #60a5fa; }
        #btn-3 { background: rgba(16, 185, 129, 0.2); border: 2px solid rgba(16, 185, 129, 0.4); color: #34d399; }
        #btn-4 { background: rgba(245, 158, 11, 0.2); border: 2px solid rgba(245, 158, 11, 0.4); color: #fbbf24; }
        #btn-5 { background: rgba(139, 92, 246, 0.2); border: 2px solid rgba(139, 92, 246, 0.4); color: #a78bfa; }
        #btn-6 { background: rgba(236, 72, 153, 0.2); border: 2px solid rgba(236, 72, 153, 0.4); color: #f472b6; }
        #btn-7 { background: rgba(6, 182, 212, 0.2); border: 2px solid rgba(6, 182, 212, 0.4); color: #22d3ee; }
        #btn-8 { background: rgba(249, 115, 22, 0.2); border: 2px solid rgba(249, 115, 22, 0.4); color: #fb923c; }
        #btn-9 { background: rgba(248, 250, 252, 0.2); border: 2px solid rgba(248, 250, 252, 0.4); color: #cbd5e1; }

        .genius-btn:hover { transform: scale(1.05); filter: brightness(1.2); }
        .genius-btn:active { transform: scale(0.95); }

        .genius-btn.active {
            transform: scale(1.1);
            filter: brightness(1.5);
            box-shadow: 0 0 30px var(--btn-color, #fff);
            border-color: white;
            z-index: 10;
        }

        /* Status */
        .game-status {
            font-size: 1.2rem;
            font-weight: 500;
            color: var(--primary);
            min-height: 2.5rem;
            margin-bottom: 0.5rem;
            display: flex;
            align-items: center;
            justify-content: center;
        }

        /* Ranking */
        .ranking-container {
            margin-top: 2rem;
            text-align: left;
            background: rgba(15, 23, 42, 0.4);
            border-radius: 16px;
            padding: 1.5rem;
            border: 1px solid var(--glass-border);
        }

        .ranking-title {
            font-size: 1.2rem;
            font-weight: 700;
            margin-bottom: 1rem;
            color: var(--text-main);
            display: flex;
            align-items: center;
            gap: 8px;
        }

        .ranking-list {
            list-style: none;
            max-height: 200px;
            overflow-y: auto;
        }

        .ranking-item {
            display: flex;
            justify-content: space-between;
            padding: 8px 0;
            border-bottom: 1px solid rgba(255, 255, 255, 0.05);
            font-size: 0.95rem;
        }

        .ranking-item:last-child { border-bottom: none; }
        .ranking-name { font-weight: 500; color: var(--text-main); }
        .ranking-score { font-weight: 700; color: var(--warning); }
        .ranking-date { color: var(--text-muted); font-size: 0.8rem; }

        /* Tela de Derrota */
        .game-over-title {
            color: var(--danger);
            font-size: 3rem;
            font-weight: 900;
            margin-bottom: 1rem;
        }

        .score-display {
            font-size: 4rem;
            font-weight: 900;
            color: var(--warning);
            margin: 1rem 0;
        }

        .score-label {
            font-size: 1.2rem;
            color: var(--text-muted);
            text-transform: uppercase;
            letter-spacing: 0.1em;
        }
    </style>
</head>
<body>

    <div class="game-wrapper">
        <div class="card" id="mainCard">
            
            <!-- TELA INICIAL -->
            <div id="screen-start" class="screen active">
                <h1>Genius ESP32</h1>
                <p>Teste sua memória nesta versão premium.</p>
                
                <div class="input-group">
                    <label for="playerName">Seu Nome</label>
                    <input type="text" id="playerName" placeholder="Digite seu nome ou apelido" value="Jogador">
                </div>
                
                <button class="btn-action" onclick="iniciarJogo()">INICIAR JOGO</button>
                
                <div class="ranking-container">
                    <div class="ranking-title">
                        🏆 Ranking Local
                    </div>
                    <ul class="ranking-list" id="rankingList"></ul>
                </div>
            </div>

            <!-- TELA DE JOGO -->
            <div id="screen-game" class="screen">
                <h1>Genius ESP32</h1>
                <div class="game-status" id="gameStatus">Observe o NOVO número na placa...</div>
                
                <!-- Display de Dígitos Digitados -->
                <div class="input-display" id="inputDisplay"></div>
                
                <div class="grid">
                    <button class="genius-btn" id="btn-1" style="--btn-color: var(--color-1)" onclick="enviarJogada(1)">1</button>
                    <button class="genius-btn" id="btn-2" style="--btn-color: var(--color-2)" onclick="enviarJogada(2)">2</button>
                    <button class="genius-btn" id="btn-3" style="--btn-color: var(--color-3)" onclick="enviarJogada(3)">3</button>
                    <button class="genius-btn" id="btn-4" style="--btn-color: var(--color-4)" onclick="enviarJogada(4)">4</button>
                    <button class="genius-btn" id="btn-5" style="--btn-color: var(--color-5)" onclick="enviarJogada(5)">5</button>
                    <button class="genius-btn" id="btn-6" style="--btn-color: var(--color-6)" onclick="enviarJogada(6)">6</button>
                    <button class="genius-btn" id="btn-7" style="--btn-color: var(--color-7)" onclick="enviarJogada(7)">7</button>
                    <button class="genius-btn" id="btn-8" style="--btn-color: var(--color-8)" onclick="enviarJogada(8)">8</button>
                    <button class="genius-btn" id="btn-9" style="--btn-color: var(--color-9)" onclick="enviarJogada(9)">9</button>
                </div>

                <button class="btn-action" id="btnProximaRodada" style="display: none; background: linear-gradient(135deg, var(--success), #059669);" onclick="proximaRodada()">PRÓXIMA RODADA</button>
            </div>

            <!-- TELA DE DERROTA -->
            <div id="screen-gameover" class="screen">
                <div class="game-over-title">FIM DE JOGO</div>
                <div class="score-label">Rodada Alcançada</div>
                <div class="score-display" id="finalScore">0</div>
                <p id="gameOverMessage">Você esqueceu a sequência!</p>
                
                <button class="btn-action" onclick="voltarParaInicio()">JOGAR NOVAMENTE</button>
            </div>

        </div>
    </div>

    <script>
        let isWaitingInput = false;
        let isGameOver = false;
        let currentLevel = 0;
        let playerName = "Jogador";
        let currentInput = []; // Guarda os dígitos digitados na rodada atual
        const audioCtx = new (window.AudioContext || window.webkitAudioContext)();

        document.addEventListener("DOMContentLoaded", () => {
            carregarRanking();
        });

        function tocarSomExplosao() {
            if (audioCtx.state === 'suspended') audioCtx.resume();
            const now = audioCtx.currentTime;
            
            const osc = audioCtx.createOscillator();
            const gainOsc = audioCtx.createGain();
            osc.type = 'sawtooth';
            osc.frequency.setValueAtTime(180, now);
            osc.frequency.exponentialRampToValueAtTime(10, now + 0.4);
            gainOsc.gain.setValueAtTime(0.8, now);
            gainOsc.gain.exponentialRampToValueAtTime(0.01, now + 0.4);
            osc.connect(gainOsc);
            gainOsc.connect(audioCtx.destination);
            
            const bufferSize = audioCtx.sampleRate * 0.5;
            const buffer = audioCtx.createBuffer(1, bufferSize, audioCtx.sampleRate);
            const data = buffer.getChannelData(0);
            for (let i = 0; i < bufferSize; i++) data[i] = Math.random() * 2 - 1;
            
            const noise = audioCtx.createBufferSource();
            noise.buffer = buffer;
            const filter = audioCtx.createBiquadFilter();
            filter.type = 'lowpass';
            filter.frequency.setValueAtTime(1000, now);
            filter.frequency.exponentialRampToValueAtTime(50, now + 0.5);
            const gainNoise = audioCtx.createGain();
            gainNoise.gain.setValueAtTime(0.6, now);
            gainNoise.gain.exponentialRampToValueAtTime(0.01, now + 0.5);
            
            noise.connect(filter);
            filter.connect(gainNoise);
            gainNoise.connect(audioCtx.destination);
            
            osc.start(now);
            noise.start(now);
            osc.stop(now + 0.5);
            noise.stop(now + 0.5);
        }

        function showScreen(screenId) {
            document.querySelectorAll('.screen').forEach(s => s.classList.remove('active'));
            document.getElementById(`screen-${screenId}`).classList.add('active');
        }

        function atualizarDisplayInput() {
            const display = document.getElementById('inputDisplay');
            display.innerHTML = '';
            currentInput.forEach(num => {
                const div = document.createElement('div');
                div.className = 'input-digit';
                div.innerText = num;
                display.appendChild(div);
            });
        }

        function iniciarJogo() {
            playerName = document.getElementById('playerName').value.trim() || "Jogador";
            if (audioCtx.state === 'suspended') audioCtx.resume();
            
            currentInput = [];
            atualizarDisplayInput();
            
            fetch('/start').then(() => {
                showScreen('game');
                verificarStatus();
            });
        }

        function enviarJogada(num) {
            if (!isWaitingInput) return;
            
            // Adiciona ao histórico visual
            currentInput.push(num);
            atualizarDisplayInput();
            
            const btn = document.getElementById(`btn-${num}`);
            btn.classList.add('active');
            setTimeout(() => btn.classList.remove('active'), 200);

            fetch(`/move?val=${num}`).then(() => verificarStatus());
        }

        function proximaRodada() {
            currentInput = [];
            atualizarDisplayInput();
            fetch('/next').then(() => verificarStatus());
        }

        function voltarParaInicio() {
            showScreen('start');
            carregarRanking();
        }

        function verificarStatus() {
            fetch('/status')
                .then(r => r.json())
                .then(data => {
                    currentLevel = data.level;
                    const statusText = document.getElementById('gameStatus');
                    const btnProxima = document.getElementById('btnProximaRodada');
                    const card = document.getElementById('mainCard');
                    
                    if (data.state === 'SHOWING_SEQUENCE') {
                        statusText.innerText = "Observe o NOVO número na placa...";
                        isWaitingInput = false;
                        isGameOver = false;
                        btnProxima.style.display = 'none';
                        // Limpa o display para a nova rodada de digitação
                        if (currentInput.length > 0) {
                            currentInput = [];
                            atualizarDisplayInput();
                        }
                    } else if (data.state === 'WAITING_INPUT') {
                        statusText.innerText = "Sua vez! Digite a sequência COMPLETA.";
                        isWaitingInput = true;
                        isGameOver = false;
                        btnProxima.style.display = 'none';
                    } else if (data.state === 'WAITING_CONFIRMATION') {
                        statusText.innerText = "Acertou! Prepare-se para o próximo.";
                        btnProxima.style.display = 'block';
                        isWaitingInput = false;
                        isGameOver = false;
                    } else if (data.state === 'GAME_OVER') {
                        if (!isGameOver) {
                            isGameOver = true;
                            statusText.innerText = "Game Over!";
                            card.classList.add('shaking');
                            tocarSomExplosao();
                            setTimeout(() => card.classList.remove('shaking'), 500);
                            
                            salvarNoRanking(playerName, currentLevel, "Perdeu");
                            
                            document.getElementById('finalScore').innerText = currentLevel;
                            showScreen('gameover');
                        }
                    } else if (data.state === 'IDLE') {
                        statusText.innerText = "Pressione Iniciar";
                        btnProxima.style.display = 'none';
                    }
                });
        }

        function salvarNoRanking(nome, rodada, status) {
            let ranking = JSON.parse(localStorage.getItem('genius_ranking') || '[]');
            const novoRegistro = {
                nome: nome,
                rodada: rodada,
                data: new Date().toLocaleString('pt-BR'),
                status: status
            };
            ranking.push(novoRegistro);
            ranking.sort((a, b) => b.rodada - a.rodada);
            ranking = ranking.slice(0, 10);
            localStorage.setItem('genius_ranking', JSON.stringify(ranking));
        }

        function carregarRanking() {
            const list = document.getElementById('rankingList');
            list.innerHTML = '';
            const ranking = JSON.parse(localStorage.getItem('genius_ranking') || '[]');
            
            if (ranking.length === 0) {
                list.innerHTML = '<li class="ranking-item"><span class="ranking-name">Nenhum jogo registrado</span></li>';
                return;
            }

            ranking.forEach(item => {
                const li = document.createElement('li');
                li.className = 'ranking-item';
                li.innerHTML = `
                    <div>
                        <span class="ranking-name">${item.nome}</span>
                        <div class="ranking-date">${item.data}</div>
                    </div>
                    <span class="ranking-score">${item.rodada} 🏅</span>
                `;
                list.appendChild(li);
            });
        }

        setInterval(() => {
            const screenGame = document.getElementById('screen-game');
            if (screenGame.classList.contains('active')) {
                verificarStatus();
            }
        }, 1000);
    </script>
</body>
</html>
)rawliteral";

#endif
