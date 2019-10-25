#include <SD.h>
#include <M5Stack.h>

#include"WiFi.h"
#include "AsyncUDP.h"
#include <ArduinoJson.h>
const char * ssid = "Grupo6xD";
const char * password = "12345678";
char texto[200]; //array para recibir los datos como texto
int hora;
boolean rec=0;
AsyncUDP udp;
void setup()
{
  Serial.begin(115200);
  M5.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.println("WiFi Failed");
        while(1) {
          delay(1000);
          }
    M5.Lcd.setTextSize(3);
  M5.Lcd.print("Conectando...");
  }
  
  M5.Lcd.println("Conectado a la red Wi-Fi");
    if(udp.listen(1234)) {
      Serial.print("UDP Listening on IP: ");
      Serial.println(WiFi.localIP());
      udp.onPacket([](AsyncUDPPacket packet) {
      int i=200;
       while (i--) {*(texto+i)=*(packet.data()+i);}
        rec=1; //recepcion de un mensaje
      });
    }
  }
  void loop()
    { 
  if (rec){
  rec=0;
  udp.broadcastTo("Recibido",1234); //Confirmación
  udp.broadcastTo(texto,1234); //reenvía lo recibido
  hora=atol(texto); //paso de texto a int
  StaticJsonDocument<200> jsonBufferRecv; //definición buffer para almacenar el objeto JSON, 200 máximo
  DeserializationError error = deserializeJson(jsonBufferRecv, texto); //paso de texto a formato JSON
  if (error)
    return;
    serializeJson(jsonBufferRecv, Serial); //envío por el puerto serie el objeto "jsonBufferRecv"
    Serial.println(); //nueva línea
    bool movimiento =jsonBufferRecv["Movimiento"];
    String minutos = jsonBufferRecv["Minuto"];
    String hora=jsonBufferRecv["Hora"];
    String distancia=jsonBufferRecv["Distancia"];
    String segundo=jsonBufferRecv["Segundo"]; //extraigo el dato "Segundo" del objeto " jsonBufferRecv " y lo
  //almaceno en la variable "segundo"
    Serial.println(segundo); //envío por el puerto serie la variable segundo

    M5.Lcd.print("Disstancia " + distancia);
    if(movimiento == true){
      M5.Lcd.print( " Se ha detectado alguien en la habitacion");
    }
  }
    delay(2000);
}
void limpiarPantalla(){
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0,0);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(3);
}
