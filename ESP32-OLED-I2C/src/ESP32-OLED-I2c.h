
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>

void oled_begin();
void writeCommand(byte command);
void writeData(byte data);
void turnON();
void NormalDisplayMode();
void setPageMode();
void clearFullDisplay() ;
void setCursor(byte X, byte Y);
