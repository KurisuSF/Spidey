float sp;
float pv; 

volatile int contador=0; //contador de pulsos detectados
int sensor=3; // puerto del sensor
unsigned long previousMillis = 0;
long interval = 100; // intervalor de tiempo en ms que pasan para que se reinicie el contador

// variables de la ecuacion de diferencias del controlador PID
float cv, cv1, error, error1, error2;

// parametros a cambiar 
float Kp = 1;       // Ganancia del sistema
float Ki = 1;
float Kd = 0.01;    //
float Tm = 0.1;     //

void setup(){
  pinMode(A1, INPUT); //EMG
  pinMode(A0, INPUT); //POT
  pinMode(8, OUTPUT); //PWN_SALIDA

  pinMode(sensor, INPUT); // puerto del sensor inicalizado
  Serial.begin(115200);
  attachInterrupt(1, interrupcion, RISING); // metodo de interrupciones incializado
}

void loop(){
  
  unsigned long currentMillis = millis();

  if((currentMillis - previousMillis) >= interval){ // se imprime el contador que arrojo a los 100ms y se reinicia 
    previousMillis = currentMillis;
    pv = 10 * contador * (60.0/12.0); //RPM del eje principal
    contador=0;
  }
  
  //rango definido por el POT

  float range = analogRead(A0);

  //---SET POINT---//
  sp = range * (1500.0/1023.0); // 0 - 1500rpm

  error = sp - pv;

  //---ECUACION DE DIFERENCIAS---//
  cv = cv1 + (Kp + Kd/Tm)*error + (-Kp + Ki*Tm - 2*Kd/Tm)*error1 + (Kd/Tm)*error2;
  
  // recursividad
  cv1 = cv;
  error2 = error1;
  error1 = error;

  // Saturacion de la salida
  if(cv > 500.0){ // valor maximo de cv (maximas revoluiciones posibles)
    cv = 500.0;
  }
  if(cv < 235.0){ // valor en el que el motor comienza a moverse (sujeto a cambios)
    cv = 235.0;
  }
  
  if(analogRead(A1) > 400){ //Solo se activa cuando hay actividad muscular
    analogWrite(8, cv * (255.0/500.0)); // 0 - 255
  }else {
    analogWrite(8, 0);
  }
  
  // impresion de las variables
  Serial.print("SP:");
  Serial.print(sp);
  Serial.print(",  PV:");
  Serial.println(pv);
  delay(100); 
}

void interrupcion(){
  contador++;
}