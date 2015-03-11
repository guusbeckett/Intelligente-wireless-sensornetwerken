#include  <EEPROM.h>
#include "XBee1.h"
int readingPin = A5;
int sensorValue = 0;
int idMac[4];
int address = 100;
XBee* bee;
XBeeAddress64 addr64 = XBeeAddress64(0x00000000, 0x00000000);


Tx16Request* request;

void setup() {  
  Serial.begin(9600);
  for (int i=0; i<4; i++) {
    idMac[i] = EEPROM.read(100+i);
  }
  bee = new XBee();
  bee->begin(9600);
}

void loop() {
  sensorValue = analogRead(readingPin);
  sensorValue = (5.0 * sensorValue * 50.0) / 1024;
  uint8_t payload[] = {idMac[0], idMac[1], idMac[2], idMac[3], ':', sensorValue, '\n'};
  ZBTxRequest zbtx = ZBTxRequest(addr64, payload, 7);
  bee->send(zbtx););
  Serial.print(*payload);
  delay(10000);
}

