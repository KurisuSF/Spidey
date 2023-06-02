#include <avr/io.h>

float lecturaEMG, diferencia;
float tmp = 0;
bool tercero, segundo, primero = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(0, OUTPUT);
  pinMode(3, INPUT);
}

void loop() {
  put your main code here, to run repeatedly:
  lecturaEMG = analogRead(3) * 100;
  diferencia = abs(lecturaEMG - tmp);
  tmp = lecturaEMG;
  delay(50);

  if(diferencia <= 200){
    if(primero == true){
      if(segundo == true){
        if(tercero == true){
        digitalWrite(0, LOW);
        }
        tercero = true;
      }
      segundo = true;
    }
    primero = true;
  }else{
    digitalWrite(0, HIGH);
    delay(500);
    primero = false;
    segundo = false;
    tercero = false;
  }
}
