#include"WiFi.h"
#include"AsyncUDP.h"
#include<ArduinoJson.h>
const char* ssid= "Grupo6xD";
const char* password= "12345678";
char texto[200]; //arraypara recibir los datos como texto
int hora;
boolean rec=0;
AsyncUDP udp;
void setup()
{
Serial.begin(115200);
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);
if(WiFi.waitForConnectResult() != WL_CONNECTED) {
Serial.println("WiFiFailed");
while(1) {
delay(1000);
}
}
if(udp.listen(1234)) {
Serial.print("UDP ListeningonIP: ");
Serial.println(WiFi.localIP());
udp.onPacket([](AsyncUDPPacket packet) {
int i=200;
while(i--) {*(texto+i)=*(packet.data()+i);}
rec=1; //recepcionde un mensaje
});
}
}
void loop()
{
if(rec){
rec=0;
udp.broadcastTo("Recibido",1234); //Confirmación
udp.broadcastTo(texto,1234); //reenvía lo recibido
hora=atol(texto); //paso de texto a int
StaticJsonDocument<200> jsonBufferRecv; //definición buffer para almacenar el objeto JSON, 200 máximo
DeserializationError error = deserializeJson(jsonBufferRecv, texto); //paso de texto a formato JSON
if(error)
return;
serializeJson(jsonBufferRecv, Serial); //envío por el puerto serie el objeto "jsonBufferRecv"
Serial.println(); //nueva línea
int segundo=jsonBufferRecv["Segundo"]; //extraigo el dato "Segundo" del objeto " jsonBufferRecv" y lo //almaceno en la variable "segundo"
Serial.println(segundo); //envío por el puerto serie la variable segundo
}
}
