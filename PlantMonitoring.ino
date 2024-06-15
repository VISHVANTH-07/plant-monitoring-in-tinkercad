#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22
#define SOILMOISTUREPIN AO
#define PUMPPIN 3

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0*27, 16, 2);
void setup(){
  Serial.begin(9600);
  dht.begin();
  lcd.begin();
  lcd.backlight();
  pinMode(PUMPPIN, OUTPUT);
  digitalWrite(PUMPPIN, LOW);
}
void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int soilMoistureValue = analogRead(SOILMOISTUREPIN);
  float soilMoisturePercentage = map(soilMoistureValue, 0, 1023, 0, 100);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Soil Moisture: ");
  Serial.print(soilMoisturePercentage);
  Serial.println(" % ");

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print(" % ");

  delay(2000);
  lcd.setCursor(0, 1);
  lcd.print("Soil: ");
  lcd.print(soilMoisturePercentage);
  lcd.print(" % ");

  if(soilMoisturePercentage < 30){
    digitalWrite(PUMPPIN, HIGH);
  }
  else{
    digitalWrite(PUMPPIN, LOW);
  }
  delay(2000);
}

