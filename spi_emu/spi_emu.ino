#include <SPI.h>

void setup() {
  // put your setup code here, to run once:
  digitalWrite(SS, HIGH);  // ensure SS stays high
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  SPI.begin ();

}

void loop() {
  // put your main code here, to run repeatedly:

  byte c;

  // enable Slave Select
  digitalWrite(SS, LOW);    // SS is pin 10

  // send test string
  for (const char * p = "Fab1212121212121" ; c = *p; p++)
    SPI.transfer (c);

  // disable Slave Select
  digitalWrite(SS, HIGH);

  delay (1);


}


