#include <EEPROM.h>
int addr = 100;
char vals[] = {2,3,2,6};

void setup()
{
  for (int i = 0; i < 4; ++i) {
    EEPROM.write(addr + i, vals[i]);
  }
}

void loop()
{

}
