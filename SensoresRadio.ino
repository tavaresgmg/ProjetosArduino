#include <SPI.h>
#include <Ethernet.h>
#include "EmonLib.h" //INCLUSÃO DE BIBLIOTECA Sensores de Tensão
#include "DHT.h" //INCLUSÃO DE BIBLIOTECA DE TEMPERATURA DHT11

//Pinos Utilizados
const int pintensao0 = 1; //PINO ANALÓGICO UTILIZADO PELO SENSOR
const int pintensao1 = 2; //PINO ANALÓGICO UTILIZADO PELO SENSOR
const int pintemp = A4; //PINO ANALÓGICO UTILIZADO PELO SENSOR

#define VOLT_CAL 215.3   //VALOR DE CALIBRAÇÃO (DEVE SER AJUSTADO EM PARALELO COM UM MULTÍMETRO)

#define DHTTYPE    DHT11     // DHT 22 (AM2302)
EnergyMonitor emon1; //CRIA UMA INSTÂNCIA
EnergyMonitor emon2; //CRIA UMA INSTÂNCIA
//dht DHT; //VARIÁVEL DO TIPO DHT
DHT dht(pintemp, DHTTYPE);

void setup() {
   byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEA };  
   byte ip[] = { 192, 168, 19, 215 }; 
   //Configuração da UART
   Serial.begin(115200);
   
  //SENSORES DE TENSÃO
  emon1.voltage(pintensao0, VOLT_CAL, 1.7); //PASSA PARA A FUNÇÃO OS PARÂMETROS (PINO ANALÓGIO / VALOR DE CALIBRAÇÃO / MUDANÇA DE FASE)
  emon2.voltage(pintensao1, VOLT_CAL, 1.7); //PASSA PARA A FUNÇÃO OS PARÂMETROS (PINO ANALÓGIO / VALOR DE CALIBRAÇÃO / MUDANÇA DE FASE)
   
}

void loop() {

  
  //sensores de tensão
  emon1.calcVI(17,500); //FUNÇÃO DE CÁLCULO (17 SEMICICLOS, TEMPO LIMITE PARA FAZER A MEDIÇÃO)  
  emon2.calcVI(17,500); //FUNÇÃO DE CÁLCULO (17 SEMICICLOS, TEMPO LIMITE PARA FAZER A MEDIÇÃO)  
  float t0  = emon1.Vrms; //VARIÁVEL RECEBE O VALOR DE TENSÃO RMS OBTIDO
  float t1  = emon2.Vrms; //VARIÁVEL RECEBE O VALOR DE TENSÃO RMS OBTIDO
  
  //sensor de temperatura
//  DHT.read11(pintemp); //LÊ AS INFORMAÇÕES DO SENSOR
  float  temperatura = dht.readTemperature(); //VARIÁVEL RECEBE A TEMPERATURA MEDIDA
  float  umidade = dht.readHumidity(); //VARIÁVEL RECEBE A UMIDADE MEDIDA

//    Serial.println("Tensão do sensor1 : ");
//    Serial.println(t0, 0);
//    Serial.println("");
//    Serial.println("Tensão do sensor2 : ");
//    Serial.println(t1, 0);
//    Serial.println("");  
//    Serial.println("Tensão de Temperatura : ");
//    Serial.println(temperatura);
//    Serial.println("");
//    Serial.println("--------------------");
//    Serial.print("Umidade: "); //IMPRIME O TEXTO NA SERIAL
//    Serial.print(umidade, 0); //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO
//    Serial.print("%"); //ESCREVE O TEXTO EM SEGUIDA
//    Serial.print(" / Temperatura: "); //IMPRIME O TEXTO NA SERIAL
//    Serial.print(temperatura, 0); //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO E REMOVE A PARTE DECIMAL
//    Serial.println("*C"); //IMPRIME O TEXTO NA SERIAL

Serial.println(umidade);
  delay(100);
   
}
