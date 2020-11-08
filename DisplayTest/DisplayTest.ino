#include <Adafruit_SSD1306.h>
#include <splash.h>

#include <U8g2lib.h>
#include <U8x8lib.h>

#include <Servo.h>


// for the OLED display SSD1306

// create the display instance 
//U8GLIB_SSD1306_128X64 oled(U8G_I2C_OPT_NONE);
Adafruit_SSD1306 oled(11, 13, 9, 8, 10);

Servo myServo;
int pos;
void setup() {
  // put your setup code here, to run once:
  // have something blink so we know it is alive
  pinMode(LED_BUILTIN, OUTPUT);
  // Port back to PC Not WIFI!
  Serial.begin(9600);
  myServo.attach(9);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.println("Before draw!");
  oled.firstPage();
  do {
    draw();
  } while(oled.nextPage());
  Serial.println("After draw!");
  delay(1000); 
  Serial.println("Before servo!");  
  for (pos = 0; pos <= 180; pos++)
  {
    myServo.write(pos);
    delay(15);
  }

  for (pos = 180; pos >= 0; pos--)
  {
    myServo.write(pos);
    delay(15);
  }
}

void draw(void) 
{
  oled.drawPixel(11, 44);
  oled.drawPixel(13, 44);

  // draw lines
  oled.drawLine(12, 28, 12, 60);
  oled.drawLine(12, 60, 128, 60);
  oled.drawLine(12, 28, 128, 30);
}
