///////   press ctrl shift U for ICSP upload  ///////////////
///////   minicore bootloader set to ATmega328 @ 4MHz internal clock ////

//////LED Jazz////////
#include <FastLED.h>
#define LED_PIN     6
#define NUM_LEDS    17
#define COLOR_ORDER GRB
#define LED_TYPE    WS2813
CRGB leds[NUM_LEDS];
float multiplier = 5;
int binaryMode = 0;

/////RTC Jazz//////
#include <Wire.h>
#include <FaBoRTC_PCF2129.h>
FaBoRTC_PCF2129 faboRTC;
//initialize the time at noon. Date doesnt matter
uint8_t  years = 0; uint8_t months =0; uint8_t days =0;uint8_t hours =12; uint8_t minutes =0;uint8_t seconds=0;

  
////Button Jazz///////
const int SW1 = 3;
const int SW2 = 4;
const int LDR = A1;


void setup() {
  delay( 1500 ); // power-up safety delay.
  Serial.begin(9600);
  Serial.println("Hello World...");
  Serial.println("From George's business card / binary clock");
  Serial.print("for code visit: "); Serial.println("https://github.com/No-George/BinaryClock");
  Serial.print("for the schematic visit: "); Serial.println("https://oshwlab.com/mrmukukuchu/binary-business-card");

  Serial.println("SW1 indexes hours, SW2 indexes minutes");
  Serial.println("Both buttons together cycle through modes. Choose from ");
  Serial.println("0: red=hours,  green=minutes, blue=seconds");
  Serial.println("1: scrolling rainbow = hours, minutes, seconds");
  Serial.println("2: Brightness controlled red=hours,  green=minutes, blue=seconds");
  Serial.println("3: scrolling rainbow = daily epoch in seconds");

  

  ///Button ///
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);

  //LDR///
  pinMode(LDR, INPUT);

  //RTC ///
  Serial.println("Checking I2C device...");
  if (faboRTC.searchDevice()) {
    Serial.println("configuring RTC");
    faboRTC.configure();
  } else {
    Serial.println("device not found");
    while(1);
  }
  Serial.println("set date/time");
  faboRTC.setDate(years,months,days,hours,minutes,seconds);

  ///LED ///
   FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
 
}

void loop() {
DateTime now = faboRTC.now();

if (seconds != now.second()){
      years = now.year();
      months = now.month();
      days = now.day();
      hours = now.hour();
      minutes = now.minute();
      seconds = now.second();
      Serial.print(hours);Serial.print(":"); Serial.print(minutes);Serial.print(":"); Serial.println(seconds);
    }
    
updateLEDs();
readButtons();
   
}
