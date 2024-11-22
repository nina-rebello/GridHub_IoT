<div align="center">
<img src="https://drive.google.com/uc?export=view&id=1yt32LMSDQzqUGvMimDFcOeXnM6Blrk1s" alt="Logo">
  <br><br><br><br>
</div>

# Projeto de Monitoramento IoT com ESP32 Integrado ao Thinger.io e MQTT

## Descrição
Este projeto tem como objetivo configurar um ESP32 para realizar a coleta de dados ambientais de sensores (como luz, temperatura, umidade e velocidade do vento) e integrá-los a plataformas de gerenciamento e visualização de dados. Através de uma conexão Wi-Fi, o ESP32 envia os dados coletados para o Thinger.io e para um broker MQTT simultaneamente, permitindo tanto o armazenamento quanto a análise em tempo real.

---
# Equipe

- Breno Lemes Santiago - https://github.com/Santlago
- Felipe Guedes Gonçalves - https://github.com/FelipeGuedesGoncalves
- Luiz Felipe Soares de Sousa Lucena - https://github.com/LuizLucena97
- Nina Rebello Francisco - https://github.com/nina-rebello
- Vitória Maria de Camargo - https://github.com/VitoriaMdeCamargo

# Vídeos demonstrativos e Pitch
- [Java Application]()
- [IoT Application](https://youtu.be/LpBOj-QvhHc)
- [Pitch](https://youtu.be/tdruTbBAiNg)
  
# Repositories

- [Documentação completa e visão geral](https://github.com/nina-rebello/GridHub/blob/main/README.md)
- [IoT Application](https://github.com/nina-rebello/GridHub_IoT)
- [Backend](https://github.com/Santlago/apigridhub)
- [Frontend](https://github.com/Santlago/webgridhub)
- [Mobile](https://github.com/FelipeGuedesGoncalves/GridHubMobile)
- [C#](https://github.com/LuizLucena97/GridHub)

---
## Funcionalidades
- **Coleta de Dados Ambientais**:  
   O ESP32 está conectado a sensores de luz (LDR), umidade, temperatura (DHT22) e velocidade do vento (potenciômetro simulando anemômetro).

---

## **Arquitetura do Projeto**

<div align="center">
   <img src="https://drive.google.com/uc?export=view&id=1TbAcZS_f-vIXl4FefTg_Yn-E_O_fa4ns" alt="Diagrama do Sistema" width="350">
</div>

### **Componentes Utilizados**
1. **Sensor de Luz (LDR)**  
   Detecta a intensidade luminosa no ambiente.  
   <div align="center">
      <img src="https://drive.google.com/uc?export=view&id=1-4SrtR9lkoZwFt3DnvRr0mO54_XAn_ac" alt="Sensor LDR" width="300">
   </div>

2. **Sensor de Temperatura e Umidade (DHT22)**  
   Mede as condições ambientais de temperatura e umidade relativa.  
   <div align="center">
      <img src="https://drive.google.com/uc?export=view&id=1S5_uo-2s0s412tqCNWGFrLoD9pkEI99W" alt="Sensor DHT22" width="150">
   </div>

3. **Sensor de Velocidade do Vento (Potenciômetro simulando Anemômetro)**  
   Fornece leituras sobre a força dos ventos no ambiente.  
   <div align="center">
      <img src="https://drive.google.com/uc?export=view&id=1yA9lHiqf1-NK0_4WWWnWVNAlkPYRpf2o" alt="Sensor de Vento" width="150">
   </div>

---

## **Integrações Tecnológicas**

### **Fluxo Node-RED**  
<div align="center">
   <img src="https://drive.google.com/uc?export=view&id=1i0nk37Y2NWWdG41w3pe7xwrtT7TEo75z" alt="Fluxo Node-RED" width="500">
</div>

### **Visualização no Thinger.io**  
1.  **Histórico e Relatórios**  
   Acesso a informações detalhadas sobre as medições realizadas.
   <div align="center">
      <img src="https://drive.google.com/uc?export=view&id=1En6weEEk_0cD4ii4GezwfHO-fgL5vulO" alt="Thinger.io Dashboard" width="500">
   </div>

2. **[Dashboard de Monitoramento](https://console.thinger.io/dashboards/global_solution_GridHub?authorization=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJqdGkiOiJEYXNoYm9hcmRfZ2xvYmFsX3NvbHV0aW9uX0dyaWRIdWIiLCJzdnIiOiJ1cy1lYXN0LmF3cy50aGluZ2VyLmlvIiwidXNyIjoibmluYS1yZWJlbGxvIn0.DnziRo5Pe-t7hGpDnOV6ipdnS7gQCoEZqtMGclV2QfA)**  
   Exibição em tempo real dos dados ambientais com gráficos e widgets.  
   <div align="center">
      <img src="https://drive.google.com/uc?export=view&id=1qcdABsogtgC89AGctL8UqGVGHWR9HvTt" alt="Data Buckets no Thinger.io" width="500">
   </div>

4. **Data Buckets**  
   Armazenamento dos dados coletados para análise posterior.
   <div align="center">
      <img src="https://drive.google.com/uc?export=view&id=1l_1Ri75vumsGlDHfDXJy76wupTEbgoS8" alt="Relatórios do Thinger.io" width="500">
   </div>

---


### **Ferramentas Utilizadas**  
- **Wokwi**: Simulador online para prototipação do ESP32 e seus sensores.  
- **Thinger.io**: Plataforma de IoT para visualização de dados em dashboards e armazenamento em buckets.  
- **PlatformIO com Visual Studio Code**: Ambiente de desenvolvimento integrado para programação e depuração do ESP32.  
- **Broker MQTT**: Para transmissão de dados em tempo real, viabilizando aplicações integradas.  

### **Objetivo Final**  
O projeto serve como um exemplo prático de integração IoT, mostrando como dados de sensores podem ser coletados, enviados e utilizados por diferentes ferramentas para criar uma solução robusta e eficiente. O backend poderá acessar os dados armazenados no **Data Bucket do Thinger.io** para gerar insights e alimentar aplicações finais, como painéis ou sistemas automatizados. 

### Passo a Passo: Configuração e Uso do Projeto IoT com ESP32, Thinger.io e Node-RED  

Este guia detalha como configurar e executar o projeto de monitoramento IoT utilizando ESP32, **Thinger.io** e **Node-RED**, passo a passo.  

---

## **1. Clone o Repositório e Configure o Ambiente**

1. Abra o terminal ou prompt de comando.  
2. Clone o repositório com o comando:  
   ```bash
   git clone <URL do Repositório>
   cd <pasta-do-projeto>
   ```
3. Certifique-se de que possui o **Visual Studio Code** com o **PlatformIO** instalado:  
   - [Guia de instalação do PlatformIO](https://platformio.org/install/ide?install=vscode)  

4. Abra o projeto no **Visual Studio Code**:  
   - Navegue até a pasta clonada e abra o arquivo principal (`main.cpp` ou equivalente).  

5. Conecte o ESP32 ao computador, compile e envie o código pelo **PlatformIO**.  
   > **Nota:** Caso esteja usando o simulador **Wokwi**, carregue o arquivo JSON na plataforma para configurar os sensores virtualmente.

---

## **2. Acesse o Node-RED**

1. O **Node-RED** já está configurado e acessível no endereço público:  
   [http://74.179.84.66:1880](http://74.179.84.66:1880)  

2. Abra o navegador e acesse este link para visualizar os fluxos configurados para o projeto.  

3. No painel do Node-RED:  
   - Verifique os dados recebidos do ESP32 via MQTT.  
   - Teste os fluxos disponíveis e explore as automações configuradas.  

---

## **3. Acesse o Dashboard Público no Thinger.io**

1. O dashboard do **Thinger.io** está disponível publicamente e pode ser acessado diretamente pelo link:  
   [Dashboard Global Solution GridHub](https://console.thinger.io/dashboards/global_solution_GridHub?authorization=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJqdGkiOiJEYXNoYm9hcmRfZ2xvYmFsX3NvbHV0aW9uX0dyaWRIdWIiLCJzdnIiOiJ1cy1lYXN0LmF3cy50aGluZ2VyLmlvIiwidXNyIjoibmluYS1yZWJlbGxvIn0.DnziRo5Pe-t7hGpDnOV6ipdnS7gQCoEZqtMGclV2QfA)  

2. Você verá widgets configurados para monitorar:  
   - Temperatura e umidade.  
   - Velocidade do vento.  
   - Intensidade luminosa.  

3. Teste os dados em tempo real e valide a funcionalidade do sistema.  

---

## **4. Teste o Sistema**

### **4.1. Dados no Node-RED**  
1. Observe os dados fluindo para os nós MQTT no painel do Node-RED.  
2. Valide se os dados estão sendo recebidos corretamente e explore os fluxos de automação.  

### **4.2. Monitoramento no Thinger.io**  
1. Verifique se os dados coletados pelo ESP32 estão atualizando em tempo real no dashboard.  
2. Explore gráficos e histórico de dados armazenados no **Data Bucket** do Thinger.io.  

---

## **5. Problemas Comuns e Soluções**

- **ESP32 não conecta ao Wi-Fi**:  
  - Certifique-se de que as credenciais estão corretas e de que a rede está disponível.  

- **Dados não aparecem no Node-RED**:  
  - Verifique a conectividade do broker MQTT.  
  - Confirme que o ESP32 está publicando no tópico correto.  

- **Dashboard do Thinger.io não exibe dados**:  
  - Confirme que o dispositivo está configurado com as mesmas credenciais do código.  

---
