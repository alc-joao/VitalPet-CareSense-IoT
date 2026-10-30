# 🐾 VitalPet CareSense IoT — Sprint 3

## 👨‍💻 Integrantes

- João Victor Alcântara — RM562707
- Phillipo Barbosa — RM565399
- Leonardo Aragaki — RM562944
- Eduardo Martins — RM562259

---

## 🚀 Sprint 4 — Integração com CareSense AI v2

Na Sprint 4, o protótipo IoT compõe a camada de aquisição de dados ambientais utilizada pela CareSense AI v2, implementada no repositório do Dashboard.

### Papel do ESP32

O ESP32 realiza:

- Leitura de temperatura e umidade pelo sensor DHT22.
- Detecção de presença pelo sensor PIR.
- Classificação ambiental local em SEGURO, ATENCAO ou CRITICO.
- Sinalização por LEDs verde e vermelho.
- Envio periódico das leituras via HTTP POST e JSON para `/api/iot`.

### Integração com a inteligência artificial

O fluxo previsto é:

```text
ESP32 / Wokwi
    |
    v
DHT22 + PIR
    |
    v
POST /api/iot
    |
    v
Dashboard
    |
    v
POST /api/ia + perfil demonstrativo do pet
    |
    v
CareSense AI v2
    |
    v
Pontuação + risco + justificativa + recomendação
```

A CareSense AI v2 utiliza um motor de regras explicáveis. A análise considera temperatura, umidade, presença e características do pet. Raça e idade contribuem para a pontuação quando a temperatura é igual ou superior a 29°C.

O motor de IA está no Dashboard, não no firmware do ESP32. A classificação local dos LEDs é independente da classificação personalizada da IA.

### Comunicação e execução

O firmware atual envia dados para:

```text
https://vital-pet-care-sense-dashboard.vercel.app/api/iot
```

Para testar com um servidor local, é necessário configurar um endereço acessível ao ESP32 ou ao simulador. `localhost` não representa automaticamente o computador host dentro do Wokwi.

O Dashboard e seus testes automatizados estão disponíveis em:

https://github.com/alc-joao/VitalPet-CareSense-Dashboard

### Validação

A integração entre `/api/iot` e `/api/ia` foi validada localmente com testes automatizados no repositório do Dashboard.

A comunicação de ponta a ponta entre o ESP32/Wokwi e a aplicação publicada ainda precisa ser validada separadamente.

### Limitações

A API IoT atualmente mantém a última leitura em memória, sem banco de dados persistente. Em hospedagem serverless, a continuidade e o compartilhamento dessas leituras entre requisições não são garantidos.

O sistema é um protótipo acadêmico preventivo e não substitui orientação veterinária.

### Vídeo da Sprint 4

O vídeo pitch de aproximadamente cinco minutos será adicionado após a gravação e publicação no YouTube em modo não listado.

---

## 📌 Descrição do Projeto

O VitalPet CareSense é uma solução de monitoramento inteligente de ambientes destinados a pets.

A solução combina IoT e análise inteligente para coletar dados ambientais em tempo real, identificar situações potencialmente perigosas e gerar análises contextualizadas considerando as características do animal monitorado.

O protótipo utiliza ESP32, sensor DHT22 e sensor PIR no simulador Wokwi.

---

## 🚨 Problema

Pets podem permanecer em ambientes inadequados sem supervisão do tutor.

Temperaturas elevadas, baixa umidade e a presença do animal em um ambiente crítico podem representar riscos.

Um monitoramento convencional apresenta os valores dos sensores, mas não necessariamente interpreta esses dados considerando também características do animal.

---

## ✅ Solução

O CareSense utiliza sensores conectados ao ESP32 para coletar:

- temperatura;
- umidade;
- presença do animal.

Os dados são enviados via HTTP para a API do Dashboard VitalPet.

No Dashboard, os dados ambientais são combinados com informações do perfil do pet e processados pelo CareSense AI.

A solução permite:

- monitorar temperatura;
- monitorar umidade;
- detectar presença;
- classificar o ambiente;
- enviar dados pela internet;
- integrar ESP32 e aplicação web;
- calcular nível de risco;
- identificar fatores de risco;
- gerar justificativa;
- gerar recomendação contextualizada.

---

## 🧠 CareSense AI

Na Sprint 3, o projeto foi evoluído com um motor de decisão contextual.

A análise utiliza:

### Dados ambientais

- temperatura;
- umidade;
- presença.

### Dados do pet

- nome;
- espécie;
- raça;
- idade;
- peso.

Como resultado, o CareSense AI retorna:

- pontuação;
- nível de risco;
- fatores identificados;
- justificativa;
- recomendação.

---

## 🤖 Abordagem de Inteligência Artificial

O protótipo utiliza uma abordagem de IA simbólica baseada em regras, semelhante a um sistema especialista.

O motor avalia simultaneamente variáveis ambientais e características do animal para determinar uma pontuação de risco.

Entre os fatores analisados estão:

- temperatura elevada;
- baixa umidade;
- presença do animal;
- idade;
- características associadas à raça.

A escolha permite que o protótipo seja explicável e reproduzível: além da classificação, o sistema informa quais fatores contribuíram para o resultado.

A arquitetura também permite evolução futura para modelos de Machine Learning ou modelos generativos.

---

## 🔄 Fluxo de Dados

```text
DHT22 ─────┐
           │
PIR ───────┤
           ▼
         ESP32
           │
           │ HTTP / JSON
           ▼
       API /api/iot
           │
           ▼
    Dashboard VitalPet
           │
           ├── Dados ambientais
           │
           └── Perfil do pet
                    │
                    ▼
              CareSense AI
                    │
       ┌────────────┼────────────┐
       ▼            ▼            ▼
     Risco     Justificativa  Recomendação
                    │
                    ▼
              Dashboard Web
```

---

## 🏗️ Arquitetura

```text
┌─────────────────────────┐
│       Wokwi / IoT       │
│                         │
│ DHT22 + PIR + ESP32     │
└────────────┬────────────┘
             │
             │ HTTP POST / JSON
             ▼
┌─────────────────────────┐
│       API /api/iot      │
└────────────┬────────────┘
             │
             ▼
┌─────────────────────────┐
│    Dashboard VitalPet   │
└────────────┬────────────┘
             │
       Sensores + Pet
             │
             ▼
┌─────────────────────────┐
│      CareSense AI       │
│   Sistema especialista  │
└────────────┬────────────┘
             │
             ▼
┌─────────────────────────┐
│ Nível de risco          │
│ Justificativa           │
│ Recomendação            │
└─────────────────────────┘
```

---

## 🛠️ Tecnologias Utilizadas

### IoT

- ESP32
- DHT22
- PIR Sensor
- LEDs
- Wokwi
- PlatformIO
- Arduino Framework
- C++

### Comunicação

- Wi-Fi
- HTTP
- REST
- JSON

### Dashboard integrado

- Next.js
- TypeScript
- API Routes
- CareSense AI

---

## 🌡️ Sensores

### DHT22

Responsável pela leitura de:

- temperatura;
- umidade.

### PIR

Responsável pela detecção de presença no ambiente.

---

## 🚦 Classificação Local do ESP32

O ESP32 possui uma primeira camada de classificação.

### SEGURO

Condições sem indicadores relevantes de risco.

### ATENÇÃO

O ambiente entra em atenção quando:

```text
temperatura >= 30°C
OU
umidade < 35%
```

### CRÍTICO

O ambiente é classificado como crítico quando:

```text
temperatura >= 35°C
OU
(temperatura >= 33°C E presença = true)
```

Essa classificação local é independente da análise contextual realizada posteriormente pelo CareSense AI.

---

## 🔌 Comunicação com a API

O ESP32 envia os dados através de uma requisição HTTP `POST` para o endpoint:

```text
/api/iot
```

Exemplo de payload:

```json
{
  "temperatura": 32.5,
  "umidade": 40.0,
  "presenca": true
}
```

O Dashboard recebe esses dados e os disponibiliza para visualização e análise.

---

## 📁 Estrutura do Projeto

```text
VitalPet-CareSense-IoT/
│
├── src/
│   └── main.cpp
│
├── diagram.json
├── platformio.ini
├── wokwi.toml
├── libraries.txt
├── image.png
├── image-1.png
└── README.md
```

---

## ▶️ Como Executar

### 1. Compilar

Com o PlatformIO instalado, execute:

```bash
pio run
```

### 2. Executar no Wokwi

O arquivo `wokwi.toml` utiliza os arquivos compilados pelo PlatformIO:

```text
.pio/build/esp32dev/firmware.bin
.pio/build/esp32dev/firmware.elf
```

Após a compilação, inicie a simulação no Wokwi.

### 3. Simular condições ambientais

Durante a execução é possível alterar:

- temperatura do DHT22;
- umidade do DHT22;
- presença no PIR.

O ESP32 envia periodicamente as novas leituras para a API.

---

## 🧪 Fluxo da Demonstração

```text
Sensores
   ↓
ESP32
   ↓
Classificação local
   ↓
HTTP POST
   ↓
API IoT
   ↓
Dashboard
   ↓
CareSense AI
   ↓
Risco + Justificativa + Recomendação
```

---

## 📷 Evidências

### Circuito ESP32

![Circuito ESP32](image.png)

### Simulação Wokwi

![Simulação Wokwi](image-1.png)

---

## 🔗 Dashboard Integrado

### Repositório

```text
https://github.com/alc-joao/VitalPet-CareSense-Dashboard
```

### Aplicação

```text
https://vital-pet-care-sense-dashboard.vercel.app/
```

---

## 📈 Evolução da Sprint 3

Nesta Sprint, o VitalPet CareSense evoluiu de um sistema de monitoramento IoT para uma solução capaz de interpretar o contexto monitorado.

Foram adicionados:

- motor de decisão contextual;
- perfil do pet como variável da análise;
- pontuação de risco;
- níveis de risco;
- identificação dos fatores considerados;
- justificativa da análise;
- recomendação contextualizada;
- integração entre IoT, API, Dashboard e CareSense AI.

---

## ⚠️ Observação

O CareSense é um protótipo acadêmico de apoio ao monitoramento ambiental e não substitui avaliação ou orientação de um profissional veterinário.

---

## 🐾 VitalPet CareSense

Projeto acadêmico desenvolvido para o Challenge Clyvo — FIAP.
---

## 🎥 Vídeo Demonstrativo — Sprint 3

O vídeo apresenta o funcionamento do VitalPet CareSense, demonstrando a integração entre IoT, Dashboard e CareSense AI.

**Link:** https://youtu.be/0aA5NGLn9Jo

## Vídeo de Apresentação — Sprint 4

[Assistir no YouTube](https://youtu.be/aasAX4S92pk)

## Como reproduzir a integração da Sprint 4

1. Inicie o Dashboard local com `npm run dev`.
2. Abra `http://localhost:3000`.
3. Compile o firmware com PlatformIO.
4. Inicie a simulação do ESP32 pelo Wokwi no VS Code.
5. O ESP32 envia as leituras para `http://host.wokwi.internal:3000/api/iot`.
6. Acompanhe as leituras e a análise de risco no Dashboard.

A integração local foi utilizada na demonstração da Sprint 4.
