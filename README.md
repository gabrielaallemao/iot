# Sistema de monitoramento remoto de reservatório de água

💡 [Descrição do Projeto](#descricao) |   
💻 [Software Desenvolvido](#software) |   
⚙️ [Hardware Utilizado](#hardware) |   
📡 [Protocolos e Módulos](#protocolos) |   
🌐 [Comunicação via Internet](#comunicacao) |   
🤖 [Programação](#programacao) |   
📄 [Documentações](#documentacoes) |   
👩🏻‍🚀 [Autoras](#autoras)   

## 💡 <a name="descricao"></a> Descrição
Este projeto consiste em um sistema de monitoramento de reservatório de água que utiliza uma placa Arduino com módulos ATmega328P e ESP8266 para coletar e transmitir dados sobre a temperatura, umidade e nível da água. Os dados são coletados através de um sensor DHT11 (temperatura e umidade) e um sensor de boia magnético (nível da água). Quando o nível da água atinge um ponto crítico, um LED é aceso como alerta. O sistema possui comunicação e controle via internet (TCP/IP) e utiliza o protocolo MQTT. A programação é realizada com linguagem C/C++ no VSCode, utilizando as extensões PlatformIO IDE e Serial Monitor e HiveMQ com Node-Red.

### Objetivo:
Monitorar e registrar umidade, nível e temperatura da água em ambientes como pequenos reservatórios. Ao coletar essas métricas, a solução se torna adaptável para aplicações maiores, como proteção animal e preservação ambiental, permitindo aos usuários analisar os dados e tomar decisões para garantir a qualidade da água e do ambiente estudado.

### Aplicações:
* Monitoramento de nível de água em caixas d'água residenciais e comerciais.
* Controle de irrigação em sistemas agrícolas.
* Monitoramento de reservatórios em estações de tratamento de água.
* Sistemas de alerta para prevenção de transbordamentos.

## 💻 <a name="software"></a> Software Desenvolvido
O software do projeto é composto por duas partes principais:    
**Código do Arduino (ATmega328P):**
* Responsável pela leitura dos sensores DHT11 e boia magnético.
* Controla o acionamento do LED de alerta.
* Envia os dados coletados para o módulo ESP8266.   

**Código do Módulo ESP8266:**  
* Responsável pela comunicação com a rede Wi-Fi.
* Implementa a comunicação TCP/IP e o protocolo MQTT.
* Envia os dados dos sensores para um servidor ou plataforma de IoT.
### Documentação do Código:
O código-fonte completo, incluindo comentários detalhados, está disponível no repositório do GitHub. A documentação abrange:
* Estrutura do código e organização dos arquivos.
* Descrição das funções e variáveis utilizadas.
* Fluxo de execução do programa.
* Explicação dos algoritmos utilizados para leitura dos sensores e controle do sistema.

## ⚙️ <a name="hardware"></a> Hardware Utilizado
* **Placa Arduino:** Utilizada como microcontrolador principal para leitura dos sensores e controle do sistema.
* **Módulo ATmega328:** Microcontrolador de 8 bits que executa o código principal do Arduino.
* **Módulo ESP8266:** Módulo Wi-Fi que permite a conexão do sistema à internet.
* **Sensor DHT11:** Sensor de temperatura e umidade.
* **Sensor Boia Magnético (ICOS LA16M-40):** Sensor de nível de água.
* **LED:** Utilizado para indicar nível de água atingido.
* **Resistores:** Utilizados para limitar a corrente nos circuitos.
* **Protoboard:** Utilizada para montar o circuito eletrônico.
* **Jumpers:** Utilizados para conectar os componentes eletrônicos.
* **Fonte de Alimentação:** Utilizada para alimentar o sistema.

## 📡 <a name="interfaces"></a> Protocolos e Módulos de Comunicação
* **Serial/USB:** Comunicação entre o Arduino e o computador via USB para programação e monitoramento através do Serial Monitor do PlatformIO.
* **DHT11:** Comunicação serial através dos pinos digitais para obter dados de temperatura e umidade.
* **Sensor Boia Magnético:** Sinal digital de nível de água (aberto ou fechado).
* **ESP8266:** Módulo com comunicação Wi-Fi integrada.
* **TCP/IP:** Protocolo de comunicação da internet para transmissão de dados.
* **MQTT:** Protocolo de mensagens leve, baseado em publicação/subscrição, utilizado para enviar os dados dos sensores para um servidor ou plataforma de IoT.

## 🌐 <a name="comunicacao"></a> Comunicação e Controle via Internet
O sistema utiliza o módulo ESP8266 para se conectar à rede Wi-Fi e enviar os dados coletados pelos sensores para um servidor ou plataforma de IoT. A comunicação é realizada através dos seguintes protocolos:
* **TCP/IP:** O ESP8266 utiliza o protocolo TCP/IP para estabelecer uma conexão com a internet e transmitir os dados.
* **MQTT:** O protocolo MQTT é utilizado para enviar os dados dos sensores de forma eficiente e confiável para um servidor MQTT. O servidor MQTT está localizado na nuvem (HiveMQ). Os dados podem ser visualizados e analisados em tempo real através de um painel de controle (NodeRED).
### Configuração:
Para configurar a comunicação via internet, é necessário:
1. Configurar as credenciais da rede Wi-Fi no código do ESP8266.
2. Configurar o endereço do servidor MQTT e as credenciais de autenticação, definidas através do HiveMQ.
3. Implementar a lógica para publicar os dados dos sensores nos tópicos MQTT desejados.

## 🤖 <a name="programacao"></a> Programação com VSCode e PlatformIO IDE
O projeto é programado utilizando o VSCode com as extensões PlatformIO IDE e Serial Monitor.
* **VSCode:** Editor e compilador de código-fonte.
* **PlatformIO IDE:** Extensão do VSCode que fornece um ambiente de desenvolvimento completo para projetos Arduino, incluindo gerenciamento de bibliotecas, compilação e upload de código.
* **Serial Monitor:** Ferramenta do PlatformIO para monitorar a comunicação serial entre o Arduino e o computador, permitindo visualizar os dados dos sensores e depurar o código.
* **HiveMQ:** Plataforma de mensagens MQTT para configurar a conexão e o gerenciamento de dispositivos IoT.
* **NodeRED:** Ferramenta de programação visual baseada em fluxo para receber os dados MQTT enviados pelo Arduino através do HiveMQ

### Passos para configurar o ambiente de desenvolvimento:
1. Instalar o VSCode.
2. Instalar as extensões PlatformIO IDE e Serial Monitor no VSCode.
3. Conectar o Arduino ao computador via USB.
4. Abrir o projeto no VSCode.
5. Configurar a placa e a porta serial no PlatformIO.
6. Compilar e fazer upload do código para o Arduino.
7. Abrir o Serial Monitor (conectado à porta usb correta) para visualizar os dados.

## 📄 <a name="documentacoes"></a> Documentações
[ATmega328](https://docs.platformio.org/en/latest/boards/atmelavr/ATmega328P.html)  
[DHT 11](https://learn.adafruit.com/dht/overview)  
[ESP 8266](https://arduino-esp8266.readthedocs.io/en/latest/)  
[Fritzing](https://fritzing.org/learning/)  
[Visual Studio Code](https://code.visualstudio.com/docs)  
[PlatformIO IDE](https://docs.platformio.org/en/latest/integration/ide/vscode.html)  
[Serial Monitor](https://marketplace.visualstudio.com/items?itemName=ms-vscode.vscode-serial-monitor)  
[HiveMQ](https://docs.hivemq.com/hivemq/latest/user-guide/index.html)  
[MQTT](https://mqtt.org/)  
[Node-RED](https://nodered.org/docs/)  

## 👩🏻‍🚀 <a name="autoras"></a>Autoras  
Gabriela Faria Allemão  
Olivia Helena Borges Silva  
Roberta Lima Santos
