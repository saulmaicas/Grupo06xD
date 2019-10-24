const int EchoPin = 19; 
const int TriggerPin = 18; // para distancia

const int PIRpin = 2;

int pirState = LOW;
int val =0 ;

void setup() { 
  Serial.begin(115200); 
  pinMode(TriggerPin, OUTPUT); 
  pinMode(EchoPin, INPUT);

  pinMode(PIRpin,INPUT); // para el de presencia
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
        //M5.Lcd.printf("sensor activado");
        Serial.println("Sensor activado");
        pirState = HIGH;
      }
   } 
   else   //si esta desactivado
   {
      if (pirState == HIGH)  //si previamente estaba encendido
      {
        Serial.println("Sensor parado");
        //M5.Lcd.printf("sensor a la shit");
        pirState = LOW;
      }
  } 
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
  
