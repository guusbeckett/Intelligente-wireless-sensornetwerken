/*
* ********* generating 'a' ********
* requires pre-paired XBee Radios
* 11/2/2012-AJW
*/
#define VERSION "1.00"
char letter = 'b';

void setup() {
  Serial.begin(9600);
}
void loop() {
  // write a character every second
  Serial.write(letter);
  delay(1000);
}
