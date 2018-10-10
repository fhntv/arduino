// подключаем неоходимую библиотеку
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "TemperatureSensors.h"
TemperatureSensors sensors;

float RoomIn = 0;
float RoomOut = 0;
float OtsideIn = 0;
float OtsideOUT = 0;


// указаем к каким пинам подключен дисплей
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
byte HomeUp[8] = {
  0b00100,
  0b01010,
  0b10001,
  0b00100,
  0b01110,
  0b11011,
  0b01110,
  0b01110
};

byte HomeDown[8] = {
  0b10001,
  0b01010,
  0b00100,
  0b00000,
  0b01110,
  0b11011,
  0b01110,
  0b01110
};
byte RoomeDown[8] = {
  0b10001,
  0b01010,
  0b00100,
  0b00000,
  0b11111,
  0b10001,
  0b10001,
  0b11111
};
byte ToiletUp[8] = {
  0b00100,
  0b01010,
  0b10001,
  0b00000,
  0b11000,
  0b11000,
  0b01111,
  0b00110
};

void setup() 
{
  lcd.begin(16, 2);
  lcd.createChar(0, HomeUp);
  lcd.createChar(1, HomeDown);
  lcd.createChar(2, ToiletUp);
  lcd.createChar(3, RoomeDown);

  lcd.setCursor(4, 0);
  lcd.print("Welcome");  

  sensors.initialize();
  while ((RoomIn==0)&&(RoomOut==0)&&(OtsideIn==0)&&(OtsideOUT==0)){
    sensors.refreshSensorValues(); 
    RoomIn = sensors.getRoomInTemp();
    RoomOut = sensors.getRoomOutTemp();
    OtsideIn = sensors.getOtsideInTemp();
    OtsideOUT = sensors.getOtsideOUTTemp();  
    }

   lcd.clear();
}

void loop() 
{
  float KPD=0;
  sensors.refreshSensorValues();
  RoomIn = sensors.getRoomInTemp();
  RoomOut = sensors.getRoomOutTemp();
  OtsideIn = sensors.getOtsideInTemp();
  OtsideOUT = sensors.getOtsideOUTTemp();
  KPD = (RoomIn-OtsideIn)/(RoomOut-OtsideIn)*100;


 lcd.setCursor(0, 0);
 lcd.write(byte(2));
 lcd.print(RoomOut,1);  
 lcd.print(" ");  

  lcd.setCursor(6, 0);  
  lcd.write(byte(0));
  lcd.print(OtsideOUT,1);  
  lcd.print(" ");  
  lcd.print(KPD,0);  

  
  lcd.setCursor(0, 1);  // сиавим курсор во вторую строку 
  lcd.write(byte(3));
  lcd.print(RoomIn,1); 
  lcd.setCursor(6, 1);  
  lcd.write(byte(1)); 
  lcd.print(OtsideIn,1);  

}
