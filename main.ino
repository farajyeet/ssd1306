#define USE_ARDUINO_INTERRUPTS true   
#include <PulseSensorPlayground.h> 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int nabiz;
const int PulseWire = 0;
const int LED13 = 13;
int Threshold = 510; 

PulseSensorPlayground pulseSensor; 

void setup() {

  Serial.begin(9600);  
  pulseSensor.analogInput(PulseWire); 
  pulseSensor.blinkOnPulse(LED13);    
  pulseSensor.setThreshold(Threshold);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Draw a single pixel in white

  display.drawPixel(10, 10, WHITE);
  display.display();
  delay(2000);
  display.clearDisplay();
  
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(17, 0);
  display.println(F("Nabziniz"));
  display.display();      // Show initial text
  delay(100);

 

  

  if (pulseSensor.begin()) {
    Serial.println("Pulse sensörü objesini yarattık."); 
  } 

}

void loop() {

  

  // put your main code here, to run repeatedly:

  if (pulseSensor.sawStartOfBeat()) { 

    nabiz = pulseSensor.getBeatsPerMinute(); 

    display.clearDisplay();
    display.setTextSize(2); // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(17, 0);
    display.println(F("Nabziniz"));
    display.setCursor(50, 30);
    display.println(nabiz);
    display.display();      // Show initial text
    delay(100);
    Serial.println("Nabız attı. ");
    Serial.print("BPM: ");                        
    Serial.println(nabiz); 

  }
  delay(20); 
}
