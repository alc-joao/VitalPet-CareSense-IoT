# 🐾 VitalPet CareSense IoT

## 👨‍💻 Integrantes

- João Victor Alcântara — RM562707
- Phillipo Barbosa — RM565399
- Vitor Madrigrano — RM564191
- Eduardo Martins — RM562259

---

# 📌 Descrição

Protótipo IoT desenvolvido para monitoramento inteligente de ambientes destinados a pets utilizando ESP32, sensor DHT22 e sensor PIR.

O sistema simula a coleta de dados ambientais e integração com dashboard web em tempo real.

---

# 🚨 Problema

Animais domésticos podem permanecer em ambientes perigosos sem supervisão, sofrendo riscos causados por:

- temperatura elevada
- baixa umidade
- ambientes fechados
- ausência de monitoramento

---

# ✅ Solução

O projeto utiliza sensores IoT conectados ao ESP32 para monitorar o ambiente e enviar informações para o dashboard VitalPet.

O sistema realiza:

- leitura de temperatura
- leitura de umidade
- detecção de presença
- integração com dashboard web

---

# 🛠️ Tecnologias Utilizadas

- ESP32
- DHT22
- PIR Sensor
- Wokwi
- C++
- HTTP

---

# 🌡️ Sensores

## DHT22

Responsável por:

- temperatura
- umidade

---

## PIR

Responsável por detectar presença no ambiente.

---

# 🔌 Comunicação

O ESP32/Wokwi simula o envio de dados para o dashboard através de requisições HTTP.

Exemplo:

```json
{
  "temperatura": 32,
  "umidade": 40,
  "presenca": true
}
```

---

# 📁 Estrutura do Projeto

```txt
sketch.ino
diagram.json
wokwi.toml
libraries.txt
```

---

# ▶️ Como Rodar no Wokwi

## 1. Abrir o projeto no Wokwi

Importar os arquivos:

- sketch.ino
- diagram.json
- wokwi.toml

---

## 2. Iniciar simulação

Executar o projeto no simulador Wokwi.

---

## 3. Simular sensores

Alterar valores do:

- DHT22
- PIR

para visualizar mudanças no dashboard.

---

# 📷 Evidências

## Circuito ESP32

Adicionar print do circuito aqui.

---

## Simulação Wokwi

Adicionar print da simulação aqui.

---

# 🔗 Dashboard Integrado

Dashboard:

```txt
https://github.com/alc-joao/VitalPet-CareSense-Dashboard
```

---

# 🎥 Vídeo Pitch

Adicionar link do YouTube não listado aqui.

---

# 📦 Entrega

O projeto contém:

- protótipo IoT
- ESP32
- sensores
- integração simulada
- dashboard
- documentação
- evidências

---

# 🐾 VitalPet CareSense IoT

Projeto acadêmico desenvolvido para o Challenge Clyvo — FIAP.