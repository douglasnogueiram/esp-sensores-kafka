# esp-sensores-kafka
Código-fonte para ESP32 LoRa, para leitura de dados de temperarura e umidade e envio para broker Kafka

![alt text](https://github.com/douglasnogueiram/esp-sensores-kafka/blob/main/Arquitetura%20controle%20temperatura.png)


![alt text](https://github.com/douglasnogueiram/esp-sensores-kafka/blob/main/Execucao.gif)

Para que toda a solução possa ser executada, é necessário ter os seguintes serviços/componentes em execução:

- Kafka (versão da Confluent, com o serviço Kafka REST, pois o ESP32 irá enviar as mensagens via API REST/HTTP)
  * É necessário criar dois tópicos: "sensores" e "sensores-dlt" (este segundo, para as mensagens que não puderem serem enviadas para o Elasticsearch, como uma dead letter)

- Elasticsearch + Kibana + Elastic APM
  * O Elasticsearch tem papel de banco de dados. As medições são armazenadas e lidas de forma agrupada, como uma média dos últimos x minutos (esse valor pode ser ajustado por variável de ambiente)


Os componentes em Springboot podem ser obtidos nos repositórios:

- https://github.com/douglasnogueiram/ms-communication-lersensores
- https://github.com/douglasnogueiram/ms-communication-controlar-temperatura

Eles também podem ser executados via Docker, através das imagens:

- https://hub.docker.com/repository/docker/douglasnogueiram/ms-communication-lersensores
- https://hub.docker.com/repository/docker/douglasnogueiram/ms-communication-controlar-temperatura


O componente de acionamento utiliza uma API REST do ESP8266 para controlar o Ar Condicionado, conforme projeto no endereço https://github.com/douglasnogueiram/API_Node_AC

O fluxograma abaixo apresenta todo o processo, desde a leitura dos sensores até a lógica de comando do ar condicionado. O algoritmo presente no componente ˜Controlar Temperatura" é baseado no Heat Index (https://www.wpc.ncep.noaa.gov/html/heatindex_equation.shtml), que leva em consideração a umidade relativa na definição da temperatura de conforto.

![alt text](https://github.com/douglasnogueiram/esp-sensores-kafka/blob/main/Fluxo%20de%20controle.png)
