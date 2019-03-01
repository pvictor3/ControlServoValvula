#include <Servo.h>
#include <avr/sleep.h>
#include <avr/power.h>

Servo servoMotor;
int pinOpen = 3;
int pinClose = 4;
int pinEnable = 8;
int pinPWM = 9;
int posOpen = 0;
int posClose = 180;
String estado = "open";
int pin2 = 2;
int seconds = 0;

void pin2Int(){
  detachInterrupt(digitalPinToInterrupt(pin2));
  }

void enterSleep(){
  attachInterrupt(digitalPinToInterrupt(pin2), pin2Int, LOW);
  delay(100);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  /**/
  sleep_disable();
  }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Iniciando control de válvula");
  pinMode(pinEnable, OUTPUT);
  pinMode(pinOpen, INPUT);
  pinMode(pinClose, INPUT);

  servoMotor.attach(pinPWM);
  enableMotor();
  abrirValvula();
}

void loop() {
  if(Serial.available() > 0)
  {
    estado = Serial.readString();
    estado.trim();
    ejecutar(estado);
  }
  if(estado.equals("open") && digitalRead(pinOpen) == HIGH){
    estado = "";
    stopMotor();
    enterSleep();  
  }

  if(estado.equals("close") && digitalRead(pinClose) == HIGH){
    estado = "";
    stopMotor();
    enterSleep();
  }
  
}

void ejecutar(String estado)
{
  if(estado.equals("open") && digitalRead(pinOpen) != HIGH)
  {
    enableMotor();
    abrirValvula();
  }
  else if(estado.equals("close") && digitalRead(pinClose) != HIGH)
  {
    enableMotor();
    cerrarValvula();
  }
  else
  {
    estado = "";
    stopMotor();
    enterSleep();
  }   
 }

 void abrirValvula(){
  servoMotor.write(posOpen);
  Serial.println("Abriendo valvula");}

 void cerrarValvula(){
  servoMotor.write(posClose);
  Serial.println("Cerrando valvula");}

 void stopMotor(){
  digitalWrite(pinEnable, LOW);
  servoMotor.detach();
  Serial.println("Motor detenido");}

 void enableMotor(){
  digitalWrite(pinEnable, HIGH);
  servoMotor.attach(pinPWM);
  Serial.println("Motor encendido");}
