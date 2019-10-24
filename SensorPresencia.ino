#include <M5Stack.h>
const int PIRPin = 2;         // pin de entrada (for PIR sensor)
 
int pirState = LOW;           // de inicio no hay movimiento
int val = 0;                  // estado del pin
 
void setup() 
{
   pinMode(PIRPin, INPUT);
   Serial.begin(115200);
   M5.begin();
}
 
void loop()
{
   val = digitalRead(PIRPin);
   if (val == HIGH)   //si está activado
   { 
      if (pirState == LOW)  //si previamente estaba apagado
      {
        M5.Lcd.printf("sensor activado");
        Serial.println("Sensor activado");
        pirState = HIGH;
      }
   } 
   else   //si esta desactivado
   {
      if (pirState == HIGH)  //si previamente estaba encendido
      {
        Serial.println("Sensor parado");
        M5.Lcd.printf("sensor a la shit");
        pirState = LOW;
      }
   }
   M5.update();
}
