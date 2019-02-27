#include <Servo.h>

Servo servoMotor;
int pinOpen = 2;
int pinClose = 3;
int pinEnable = 8;
int pinPWM = 9;
int posOpen = 0;
int posClose = 180;
String estado = "open";

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
  }

  if(estado.equals("close") && digitalRead(pinClose) == HIGH){
    estado = "";
    stopMotor();
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
