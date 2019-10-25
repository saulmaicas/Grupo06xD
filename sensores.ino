
#include "AsyncUDP.h"
#include "WiFi.h"
#include <TimeLib.h>
#include <ArduinoJson.h> 

const int EchoPin = 19; 
const int TriggerPin = 18; // para distancia

const int PIRpin = 2;


const char * ssid = "Grupo6xD";
const char * password = "12345678";

int pirState = LOW;
int val =0 ;

AsyncUDP udp;

StaticJsonDocument<200> jsonBuffer; //tamaño maximo de los datos

void setup() { 
  Serial.begin(115200); 
  pinMode(TriggerPin, OUTPUT); 
  pinMode(EchoPin, INPUT);

  pinMode(PIRpin,INPUT); // para el de presencia

  setTime (9, 15, 0, 7, 10, 2018); //hora minuto segundo dia mes año
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
      if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("WiFi Failed");
        while(1) {
            delay(1000);
          }
      }if(udp.listen(1234)) {
          Serial.print("UDP Listening on IP: ");
          Serial.println(WiFi.localIP());
          udp.onPacket([](AsyncUDPPacket packet) {
            Serial.write(packet.data(), packet.length());
            Serial.println();
          });
        }
  
}
void loop() { 
  //Serial.println(TriggerPin);
  //Serial.println(EchoPin);
  Serial.print("Distancia: "); 
  Serial.println(distancia(TriggerPin, EchoPin)); 
  delay(1000); 

   val = digitalRead(PIRpin);
   if (val == HIGH)   //si está activado
   { 
      if (pirState == LOW)  //si previamente estaba apagado
      {
        Serial.println("Sensor activado");
        pirState = HIGH;
        jsonBuffer["Movimiento"]= true;
      }
   } 
   else   //si esta desactivado
   {
      if (pirState == HIGH)  //si previamente estaba encendido
      {
        Serial.println("Sensor parado");
        jsonBuffer["Movimiento"]= false;

        pirState = LOW;
      }
    }
    
    char texto[150];
     jsonBuffer["Hora"]=hour(); //Datos introducidos en el objeto “jsonbuffer"
        jsonBuffer["Minuto"]=minute(); //3 campos
        jsonBuffer["Segundo"]=second(); //
        jsonBuffer["Distancia"] = distancia(TriggerPin, EchoPin);
        
     serializeJson(jsonBuffer, texto); //paso del objeto “jsonbuffer" a te

     udp.broadcastTo(texto,1234); //se envía por el puerto 1234 el JSON

}
  int distancia(int TriggerPin, int EchoPin) { 
    long duracion, distanciaCm; 
    digitalWrite(TriggerPin, LOW); //nos aseguramos señal baja al principio 
    delayMicroseconds(4); 
    digitalWrite(TriggerPin, HIGH); //generamos pulso de 10us 
   //Serial.println(duracion);
   // Serial.println(TriggerPin);
   // Serial.println(EchoPin);
    delayMicroseconds(10); 
    digitalWrite(TriggerPin, LOW); 
    duracion = pulseIn(EchoPin, HIGH); //medimos el tiempo del pulso
    //Serial.print(duracion); 
    distanciaCm = duracion * 10 / 292 / 2; //convertimos a distancia
    return distanciaCm; 
    Serial.println(distanciaCm);
    }
  
