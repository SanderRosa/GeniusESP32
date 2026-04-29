#ifndef WEB_UI_H
#define WEB_UI_H

const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Genius Memory - ESP32</title>
    <style>
        :root {
            --bg: #0f172a;
            --glass: rgba(255, 255, 255, 0.1);
            --primary: #38bdf8;
            --danger: #ef4444;
            --success: #22c55e;
            --text: #f8fafc;
        }

        body {
            font-family: 'Inter', sans-serif;
            background: radial-gradient(circle at top left, #1e293b, #0f172a);
            color: var(--text);
            display: flex; flex-direction: column; align-items: center; justify-content: center;
            min-height: 100vh; margin: 0; overflow: hidden;
        }

        @keyframes shake {
            0% { transform: translate(1px, 1px) rotate(0deg); }
            10% { transform: translate(-1px, -2px) rotate(-1deg); }
            20% { transform: translate(-3px, 0px) rotate(1deg); }
            30% { transform: translate(3px, 2px) rotate(0deg); }
            40% { transform: translate(1px, -1px) rotate(1deg); }
            50% { transform: translate(-1px, 2px) rotate(-1deg); }
            60% { transform: translate(-3px, 1px) rotate(0deg); }
            70% { transform: translate(3px, 1px) rotate(-1deg); }
            80% { transform: translate(-1px, -1px) rotate(1deg); }
            90% { transform: translate(1px, 2px) rotate(0deg); }
            100% { transform: translate(1px, -2px) rotate(-1deg); }
        }

        .shaking { animation: shake 0.2s infinite; }

        .container {
            background: var(--glass); backdrop-filter: blur(12px);
            padding: 2.5rem; border-radius: 24px;
            box-shadow: 0 8px 32px rgba(0,0,0,0.5);
            border: 1px solid rgba(255,255,255,0.1);
            text-align: center; max-width: 400px; width: 90%; z-index: 10;
        }

        h1 { font-weight: 800; margin-bottom: 0.5rem; letter-spacing: -1px; }
        .status { font-size: 1.1rem; margin-bottom: 1rem; color: var(--primary); font-weight: 600; min-height: 1.5em; }

        .grid {
            display: grid; grid-template-columns: repeat(3, 1fr); gap: 12px; margin-bottom: 1.5rem;
        }

        .btn {
            aspect-ratio: 1; background: rgba(255,255,255,0.05);
            border: 2px solid rgba(255,255,255,0.1); border-radius: 16px;
            color: var(--text); font-size: 1.5rem; font-weight: bold;
            cursor: pointer; transition: all 0.2s;
            display: flex; align-items: center; justify-content: center;
        }

        .btn:hover { background: rgba(255,255,255,0.1); transform: scale(1.05); }
        .btn:active { background: var(--primary); transform: scale(0.95); }

        .input-display {
            background: rgba(0,0,0,0.2);
            padding: 10px; border-radius: 12px;
            margin-bottom: 1rem; min-height: 2.5rem;
            display: flex; align-items: center; justify-content: center;
            gap: 8px; font-size: 1.2rem; font-weight: 800;
            border: 1px dashed rgba(255,255,255,0.2);
        }

        .input-digit {
            background: var(--primary); color: #0f172a;
            width: 30px; height: 30px; border-radius: 6px;
            display: flex; align-items: center; justify-content: center;
        }

        .controls { margin-top: 1rem; display: flex; flex-direction: column; gap: 10px; }
        .main-btn {
            background: var(--primary); color: #0f172a; border: none;
            padding: 14px 32px; border-radius: 12px; font-weight: 700;
            cursor: pointer; transition: all 0.2s; width: 100%;
        }

        #nextBtn { background: var(--success); display: none; }

        .level-badge {
            background: rgba(56, 189, 248, 0.2); padding: 6px 16px;
            border-radius: 20px; font-size: 1rem; margin-bottom: 1rem;
            display: inline-block; font-weight: 800;
        }

        #overlay {
            position: fixed; top: 0; left: 0; right: 0; bottom: 0;
            background: rgba(239, 68, 68, 0.4); display: none;
            flex-direction: column; align-items: center; justify-content: center;
            z-index: 100; backdrop-filter: blur(8px);
        }

        #overlay h2 { color: white; font-size: 3rem; margin: 0; }
        
        .particle { position: absolute; width: 8px; height: 8px; border-radius: 50%; pointer-events: none; z-index: 99; }
        @keyframes explode { to { transform: translate(var(--x), var(--y)); opacity: 0; } }
    </style>
</head>
<body id="body">

    <div class="container" id="gameContainer">
        <h1>Genius Memory</h1>
        <div class="level-badge">SEQUÊNCIA: <span id="level">1</span> dígitos</div>
        
        <div id="status" class="status">Pressione Iniciar</div>
        
        <div class="input-display" id="inputDisplay">
            <!-- Digitos aparecerão aqui temporariamente -->
        </div>

        <div class="grid">
            <button class="btn" onclick="sendMove(1)">1</button>
            <button class="btn" onclick="sendMove(2)">2</button>
            <button class="btn" onclick="sendMove(3)">3</button>
            <button class="btn" onclick="sendMove(4)">4</button>
            <button class="btn" onclick="sendMove(5)">5</button>
            <button class="btn" onclick="sendMove(6)">6</button>
            <button class="btn" onclick="sendMove(7)">7</button>
            <button class="btn" onclick="sendMove(8)">8</button>
            <button class="btn" onclick="sendMove(9)">9</button>
        </div>

        <div class="controls">
            <button class="main-btn" id="nextBtn" onclick="nextRound()">PRÓXIMA RODADA</button>
            <button class="main-btn" id="startBtn" onclick="startGame()">INICIAR JOGO</button>
        </div>
    </div>

    <div id="overlay">
        <h2>GAME OVER</h2>
        <p style="font-weight: bold; margin: 15px 0;">Você esqueceu a sequência!</p>
        <button class="main-btn" style="width: auto; background: white; color: var(--danger);" onclick="closeOverlay()">RECOMEÇAR</button>
    </div>

    <script>
        let isWaiting = false;
        let isGameOver = false;
        let currentInput = [];
        const audioCtx = new (window.AudioContext || window.webkitAudioContext)();

        function createExplosionSound() {
            const bufferSize = audioCtx.sampleRate * 0.5;
            const buffer = audioCtx.createBuffer(1, bufferSize, audioCtx.sampleRate);
            const data = buffer.getChannelData(0);
            for (let i = 0; i < bufferSize; i++) data[i] = Math.random() * 2 - 1;
            const noise = audioCtx.createBufferSource(); noise.buffer = buffer;
            const filter = audioCtx.createBiquadFilter(); filter.type = 'lowpass';
            filter.frequency.setValueAtTime(1000, audioCtx.currentTime);
            filter.frequency.exponentialRampToValueAtTime(0.01, audioCtx.currentTime + 0.5);
            const gain = audioCtx.createGain(); gain.gain.setValueAtTime(0.5, audioCtx.currentTime);
            gain.gain.exponentialRampToValueAtTime(0.01, audioCtx.currentTime + 0.5);
            noise.connect(filter); filter.connect(gain); gain.connect(audioCtx.destination);
            noise.start();
        }

        function updateDisplay() {
            const display = document.getElementById('inputDisplay');
            display.innerHTML = '';
            currentInput.forEach(num => {
                const span = document.createElement('div');
                span.classList.add('input-digit');
                span.innerText = num;
                display.appendChild(span);
            });
        }

        function updateStatus() {
            fetch('/status')
                .then(r => r.json())
                .then(data => {
                    document.getElementById('level').innerText = data.level;
                    const statusText = document.getElementById('status');
                    const nextBtn = document.getElementById('nextBtn');
                    const container = document.getElementById('gameContainer');
                    
                    if (data.state === 'SHOWING_SEQUENCE') {
                        statusText.innerText = "Observe o NOVO número na placa...";
                        isWaiting = false;
                        isGameOver = false;
                        nextBtn.style.display = 'none';
                        currentInput = [];
                        updateDisplay();
                    } else if (data.state === 'WAITING_INPUT') {
                        statusText.innerText = "Digite a sequência COMPLETA!";
                        isWaiting = true;
                        isGameOver = false;
                        nextBtn.style.display = 'none';
                    } else if (data.state === 'WAITING_CONFIRMATION') {
                        statusText.innerText = "Acertou! Prepare-se para o próximo.";
                        nextBtn.style.display = 'block';
                        isWaiting = false;
                        isGameOver = false;
                        currentInput = []; // Limpa ao acertar
                        updateDisplay();
                    } else if (data.state === 'GAME_OVER') {
                        if (!isGameOver) {
                            isGameOver = true;
                            document.getElementById('overlay').style.display = 'flex';
                            container.classList.add('shaking');
                            createExplosionSound();
                            setTimeout(() => container.classList.remove('shaking'), 1000);
                        }
                    } else if (data.state === 'IDLE') {
                        statusText.innerText = "Pressione Iniciar";
                        nextBtn.style.display = 'none';
                    }
                });
        }

        function startGame() {
            if (audioCtx.state === 'suspended') audioCtx.resume();
            currentInput = [];
            updateDisplay();
            fetch('/start').then(() => {
                document.getElementById('startBtn').innerText = "REINICIAR";
                updateStatus();
            });
        }

        function nextRound() {
            fetch('/next').then(() => updateStatus());
        }

        function sendMove(num) {
            if (!isWaiting) return;
            currentInput.push(num);
            updateDisplay();
            fetch(`/move?val=${num}`).then(() => updateStatus());
        }

        function closeOverlay() {
            document.getElementById('overlay').style.display = 'none';
            startGame();
        }

        setInterval(updateStatus, 500);
    </script>
</body>
</html>
)rawliteral";

#endif
