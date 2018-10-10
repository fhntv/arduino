#include "TemperatureSensors.h"
#include <OneWire.h>
#include <DallasTemperature.h>

TemperatureSensors sensors;

int PTCMainSwitch = 11;
int PTC1 = 3;
int PTC2 = 5;
int PTC3 = 6;

int v1pin = A0;
int v2pin = A1;

int Beeper = 10;

int CurrentPTC=3;
int ActivePTC=1;
float InputVoltage = 0;
bool PTCEnabled=false;

float coolant = 0;
float inside = 0;
float board = 0;
  
void setup() {
  // put your setup code here, to run once:
  pinMode(PTCMainSwitch, OUTPUT); 
  pinMode(PTC1, OUTPUT);
  pinMode(PTC2, OUTPUT); 
  pinMode(PTC3, OUTPUT); 
 
  pinMode(Beeper, OUTPUT);

  digitalWrite(Beeper, LOW);

  Serial.begin(9600);           
  sensors.initialize();

while ((coolant==0)&&(inside==0)&&(board==0)){
  sensors.refreshSensorValues(); 
  coolant = sensors.getCoolantTemp();
  inside = sensors.getInsideTemp();
  board = sensors.getBoardTemp();
  
  }
if ((coolant < 10)&&(coolant != -127)){
  digitalWrite(PTCMainSwitch, HIGH); 
    PTCEnabled=true;
  }
}

long lastMillis = millis();
//---------------------------------------

void loop() {

  sensors.refreshSensorValues();
  coolant = sensors.getCoolantTemp();
  inside = sensors.getInsideTemp();
  board = sensors.getBoardTemp();
  InputVoltage=analogRead(v1pin)/69.1; 
  
  if(board>60){
    digitalWrite(PTCMainSwitch, LOW);
    PTCEnabled = false;
    }

  
  if((coolant>55)&&(PTCEnabled)){
    SlowShutdownPTC();
    } 
  
  if (millis()-lastMillis >= 1000){
    if (PTCEnabled){
      coerceInputVoltage();
    }
    
    WriteLogToCom();
    lastMillis = millis(); 
    }
    
  
}
//---------------------------------------
void SlowShutdownPTC(){
  while(DecreacePower()){
    delay(5000);
    }
  PTCEnabled = false;
  digitalWrite(PTCMainSwitch, LOW);          

  }

//--------------------------------------- 
void coerceInputVoltage(){

  if (InputVoltage>13.8) {
    IncreasePower();
    }
        
  if (InputVoltage<13.5) {
    DecreacePower();
    }
  }
//---------------------------------------
bool NextPTC(){
  switch (CurrentPTC) {
      case 3:
        CurrentPTC = 5;
        ActivePTC++;
        return true;
     case 5:
        ActivePTC++;
        CurrentPTC = 6;
        return true;
    }
  return false;
}
//---------------------------------------
bool PreviousPTC(){
  switch (CurrentPTC) {
      case 6:
        CurrentPTC = 5;
        ActivePTC--;
        return true;
     case 5:
        CurrentPTC = 3;
        ActivePTC--;
        return true;
    }  
  return false;
}
//---------------------------------------
void IncreasePower(){
 digitalWrite(PTCMainSwitch, HIGH); 
 digitalWrite(CurrentPTC, HIGH);
 
 NextPTC(); 
}
//---------------------------------------
bool DecreacePower(){
  digitalWrite(CurrentPTC, LOW); 
      if (PreviousPTC()==false) { 
        return false;
      }    
  return true;
}
//---------------------------------------
void WriteLogToCom(){
  
  Serial.print("V: ");
  Serial.print(InputVoltage);     

  Serial.print(" CurrentPTC: ");
  Serial.print(CurrentPTC);   
  Serial.print(" ActivePTC: ");
  Serial.print(ActivePTC);   

  Serial.print(" coolant: ");
  Serial.print(coolant);
  Serial.print(" vcc: ");
  Serial.print(getVoltage());
  Serial.print(" BRD: ");
  Serial.println(board); 
}
float getVoltage(){
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(1);
  ADCSRA |= _BV(ADSC); // начало преобразований
  while (bit_is_set(ADCSRA, ADSC)); // измерение
  uint8_t low = ADCL; // сначала нужно прочесть ADCL - это запирает ADCH
  uint8_t high = ADCH; // разлочить оба
  float result = (high<<8) | low;
  //result = 1360/ result; // Результат Vcc 
  result = 20 * analogRead(v1pin)/result;
  //result =  analogRead(v1pin);
  return result;
}


