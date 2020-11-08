/*
   Sketch to just get the OLDE SSD1306 screen working but not in a demo.
    The commented out groups of includes were created when adding the libs

*/

// adding  the next one
//#include <Adafruit_SSD1306.h>
//#include <splash.h>

// adding the next one
//#include <Adafruit_GFX.h>
//#include <Adafruit_GrayOLED.h>
//#include <Adafruit_SPITFT.h>
//#include <Adafruit_SPITFT_Macros.h>
//#include <gfxfont.h>


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// SSD1306 display constants
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // means no reset pin

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define MAX_LINES 8
#define MAX_LINE_LENGTH 22 

char lines[MAX_LINES][MAX_LINE_LENGTH];

void setup() {
  // To talk to PC
  Serial.begin(115200);

  if (!initDisplay()) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  printLine(3, "End of setup()");
  printScreen();
}

void loop() {
  // put your main code here, to run repeatedly:
  printLine(0, "Start of loop()");
  delay(2000);
  printLine(6, "End of loop()");
  printScreen();
}

bool initDisplay()
{
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  // Address 0x#C or 0x3D for 128x64 -- Get from Look_at_i2c sketch
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    return false;
  }

  display.display();
  delay(2000);  // the init of display takes time

  // clear the buffer
  display.clearDisplay();
  return true;  
}

void printLine(int row, char * text)
{
  if (row >= 0 && row < MAX_LINES){
    for(int ich = 0; ich < MAX_LINE_LENGTH; ich++)
    {
      if (text[ich] != 0)
      {
        lines[row][ich] = text[ich];
      }
      else 
      {
        lines[row][ich] = 0;
      }
    }
    lines[row][MAX_LINE_LENGTH-1] = 0;
  }
}

void printScreen() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  for (int idx = 0, ycur = 0; idx < MAX_LINES; idx++, ycur += 8)
  {
    display.setCursor(0, ycur);
    display.println(&lines[idx][0]);
  }
  display.display();
}
