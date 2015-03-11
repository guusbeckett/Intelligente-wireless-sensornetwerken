#include <EEPROM.h>
int address = 100;
byte value;

void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < 4; ++i){
    value = EEPROM.read(address + i);
  Serial.write(value+48);
  }
}

void loop()
{

}
