#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <ESP32-OLED-I2c.h>


// How many internal neopixels do we have? some boards have more than one!
#define NUMPIXELS        1

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);


//definitions for OLED display SSD1306
#define OLED_I2c_ADDRESS 0x3C
//register addresses
#define COMMAND_REG 0x80 // B1000 0000
#define DATA_REG 0x40 // B0100 0000
//commands
#define ON_CMD 0xAF
#define NORMAL_DISPLAY_CMD 0xA6
#define PAGE_ADDRESSING_MODE 0x02




// the setup routine runs once when you press reset:
void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);

#if defined(NEOPIXEL_POWER)
  // If this board has a power control pin, we must set it to output and high
  // in order to enable the NeoPixels. We put this in an #if defined so it can
  // be reused for other boards without compilation errors
  pinMode(NEOPIXEL_POWER, OUTPUT);
  digitalWrite(NEOPIXEL_POWER, HIGH);
#endif

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(20); // no


  oled_begin();
  setCursor(0, 0);
  writeData(B01010101);
  writeData(B10101010);
  writeData(B01010101);
  writeData(B10101010);
  writeData(B01010101);
  writeData(B10101010);
  writeData(B01010101);
  writeData(B10101010);
  

}

void loop() 
{
  // put your main code here, to run repeatedly:
 // say hi
  Serial.println("Hello!");
  
  // set color to red
  pixels.fill(0xFF0000);
  //pixels.show();
  delay(500); // wait half a second

  // turn off
  pixels.fill(0x000000);
  //pixels.show();
  delay(500); // wait half a second
}

void oled_begin()
{
  Wire.begin(); // join i2c bus (address optional for master)
  turnON();
  NormalDisplayMode();
  setPageMode();
  writeCommand(0x8d); //Charge Pump
  writeCommand(0x14);
  clearFullDisplay();
}


void writeCommand(byte command) {
  Wire.beginTransmission(OLED_I2c_ADDRESS); // begin transmitting  (OLED_I2c_ADDRESS=0x3C)
  Wire.write(COMMAND_REG);                  // Command Reg Address (COMMAND_REG     =0x80 )
  Wire.write(command);                      // Command to be excuted
  Wire.endTransmission();                   // stop transmitting
}

void writeData(byte data) {
  Wire.beginTransmission(OLED_I2c_ADDRESS); // begin transmitting   (OLED_I2c_ADDRESS=0x3C)
  Wire.write(DATA_REG);                     //Data Reg Address      (DATA_REG        =0x40)
  Wire.write(data);                         //Write data
  Wire.endTransmission();                   // stop transmitting
}

void turnON() {
  writeCommand(ON_CMD);
}

void NormalDisplayMode() {

  writeCommand(NORMAL_DISPLAY_CMD);

}

void setPageMode() {
  byte addressingMode = PAGE_ADDRESSING_MODE;
  writeCommand(0x20);        //set addressing mode
  writeCommand(PAGE_ADDRESSING_MODE);   //set page addressing mode
}

//clearFullDisplay()
// In this function we are setting X,Y=0
// then write data on 128 column and
// then change page and do same till 7th page
void clearFullDisplay() {
  for (byte page = 0; page < 8; page++) {

    setCursor(0, page);
    for (byte column = 0; column < 128; column++) { //clear all columns
      writeData(0x00);
    }

  }
  setCursor(0, 0);
}

void setCursor(byte X, byte Y) {
  writeCommand(0x00 + (X & 0x0F));        //set column lower address
  writeCommand(0x10 + ((X >> 4) & 0x0F)); //set column higher address
  writeCommand(0xB0 + Y);                 //set page address

}



