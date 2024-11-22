# Projeto de Monitoramento IoT com ESP32 Integrado ao Thinger.io e MQTT

## Descrição
Este projeto tem como objetivo configurar um ESP32 para realizar a coleta de dados ambientais de sensores (como luz, temperatura, umidade e velocidade do vento) e integrá-los a plataformas de gerenciamento e visualização de dados. Através de uma conexão Wi-Fi, o ESP32 envia os dados coletados para o Thinger.io e para um broker MQTT simultaneamente, permitindo tanto o armazenamento quanto a análise em tempo real.

## Funcionalidades
- **Coleta de Dados Ambientais**:  
   O ESP32 está conectado a sensores de luz (LDR), umidade, temperatura (DHT22) e velocidade do vento (potenciômetro simulando anemômetro).  

- **Envio de Dados ao Thinger.io**:  
   - Os dados são integrados ao **Thinger.io Dashboard**, permitindo a visualização em tempo real através de gráficos interativos e widgets.  
   - Armazenamento no **Data Bucket do Thinger.io**, onde as informações são organizadas e mantidas para análises históricas e consulta pelo backend.  

- **Publicação MQTT**:  
   - Simultaneamente, os dados são enviados para um broker MQTT. Isso facilita a integração com outras aplicações, como o **Node-RED**, para processamento adicional ou automações.

## Fluxo Node-Red
<div>
   <img src="https://drive.google.com/uc?export=view&id=1i0nk37Y2NWWdG41w3pe7xwrtT7TEo75z" alt="Logo">
</div>

## Thinger.io
<div>
   <img src="https://drive.google.com/uc?export=view&id=1i0nk37Y2NWWdG41w3pe7xwrtT7TEo75z" alt="Logo">
</div>


### **Ferramentas Utilizadas**  
- **Wokwi**: Simulador online para prototipação do ESP32 e seus sensores.  
- **Thinger.io**: Plataforma de IoT para visualização de dados em dashboards e armazenamento em buckets.  
- **PlatformIO com Visual Studio Code**: Ambiente de desenvolvimento integrado para programação e depuração do ESP32.  
- **Broker MQTT**: Para transmissão de dados em tempo real, viabilizando aplicações integradas.  

### **Objetivo Final**  
O projeto serve como um exemplo prático de integração IoT, mostrando como dados de sensores podem ser coletados, enviados e utilizados por diferentes ferramentas para criar uma solução robusta e eficiente. O backend poderá acessar os dados armazenados no **Data Bucket do Thinger.io** para gerar insights e alimentar aplicações finais, como painéis ou sistemas automatizados.  
