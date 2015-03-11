#include  <EEPROM.h>
int readingPin = A5;
int sensorValue = 0;
int idMac = 0;
int address = 100;

void setup() {  
  Serial.begin(9600);
  idMac += EEPROM.read(address++)*1000;
  idMac += EEPROM.read(address++)*100;
  idMac += EEPROM.read(address++)*10;
  idMac += EEPROM.read(address);
}

void loop() {
  sensorValue = analogRead(readingPin);
  sensorValue = (5.0 * sensorValue * 50.0) / 1024;
  Serial.print(idMac);
  Serial.print(":");
  Serial.print(sensorValue);
  Serial.print("\n");
  delay(10000);
}

