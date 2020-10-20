
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>
#include "WiFiEsp.h"

/*
  Blink

  Got the WIFI connectiona nd trying to get the 
*/


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET    -1  // from script 4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

SoftwareSerial Serial1(6, 7);
char ssid[] = "OWNIT-9510";
char pass[] = "S5JD7Y4CHAN4TU";

int status = WL_IDLE_STATUS;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // This goes back to the PC
  Serial.begin(115200);

  // this is the WiFi com port
  Serial1.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds to let it init
  
  // Clear the buffer
  display.clearDisplay();

  // Initialize the ESP module
  WiFi.init(&Serial1);

  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println("Wifi shield not present");
    // block running
    while (true);
  }

  // attempt to connect
  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);

    // Connect
    status = WiFi.begin(ssid, pass);
  }
  //Serial.println("You're connected to the network.");
  printWiFiStatus();
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second

  Serial.println("Hello from Arduino!");
  printWiFiStatus();
  displayWiFiStatus();
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}

void printWiFiStatus()
{
  Serial.print("SSID: ");
  Serial.println(ssid);

  IPAddress ip = WiFi.localIP();
  Serial.print("IP address: ");
  Serial.println(ip);
}


void displayWiFiStatus()
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.print("SSID: ");
  display.println(ssid);

  IPAddress ip = WiFi.localIP();
  display.print("IP address: ");
  display.println(ip);
  display.display();
}
