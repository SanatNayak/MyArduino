#include <thermistor.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

 
 int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {
pinMode(12,OUTPUT);
digitalWrite(12,HIGH);
delay(300);
digitalWrite(12,LOW);

lcd.init();
lcd.backlight();
lcd.setCursor(0,0);
lcd.print("Power On");
lcd.clear();


}

void loop() {

  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 + 32.0; 
  float C = (T-32)*5/9;

  lcd.setCursor(0, 0);
  lcd.print("Temp:=");
  lcd.print(T);
  lcd.print(" F");
  lcd.setCursor(0,1);
  lcd.print("Temp:=");
  lcd.print(C);
  lcd.print(" C");
  delay(1500);
if(T>100)
{
  digitalWrite(12,HIGH);
  delay(500);
  digitalWrite(12,LOW);
  
  }
  else
  {
    digitalWrite(12,LOW);
    }
 \\Create By Sanat
}
