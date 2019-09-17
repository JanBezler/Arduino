#include <Arduino.h>
#include <TM1637Display.h>

#define CLK 2
#define DIO 3

#define TEST_DELAY   2000

TM1637Display display(CLK, DIO);

void setup()
{
}

void loop()
{
  int k;
  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00 };
  display.setBrightness(0x0f);

  // All segments on
  display.setSegments(data);
  delay(TEST_DELAY);

  // Selectively set different digits
 // data[0] = display.encodeDigit(0);
 // data[1] = display.encodeDigit(1);
 // data[2] = display.encodeDigit(2);
 // data[3] = display.encodeDigit(3);
 // display.setSegments(data);
 // delay(TEST_DELAY);
  


  // Show decimal numbers with/without leading zeros
  display.showNumberDec(6985,false);
  delay(TEST_DELAY);

  while(1);
}
