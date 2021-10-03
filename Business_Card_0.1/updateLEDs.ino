void updateLEDs(){

  checkBrightness();
  byte r; byte g; byte b;
  byte offset = 0;
  uint8_t  hue=(millis()/16)%255; //create moving seed, colour will scroll. FastLED uses 0-255, not 0-255

  switch (binaryMode){
    case 0: //hours minutes seconds   ...RGB     
            ///Set Seconds
            for (int i = (0+offset); i < (6+offset); i++) {
              if (bitRead(seconds, (i-offset))) {
                  leds[i] = CHSV(160, 255, 150);
              } else {
                  leds[i] = CHSV(160, 255, 60);  
              }
            }
            
            ///Set Minutes
            offset = 6;
            for (int i = (0+offset); i < (6+offset); i++) {
              if (bitRead(minutes, (i-offset))) {
                  leds[i] = CHSV(95, 255, 150);
              } else {
                  leds[i] = CHSV(95, 255, 60);  
              }
            }
    
            ///Set Hours
            offset = 12;
            for (int i = (0+offset); i < (5+offset); i++) {
              if (bitRead(hours, (i-offset))) {
                  leds[i] = CHSV(0, 255, 150);
              } else {
                  leds[i] = CHSV(0, 255, 60);  
              }
            }
     
          break;

      case 1:
            ///Set Seconds
            for (int i = (0+offset); i < (6+offset); i++) {
              if (bitRead(seconds, (i-offset))) {
                  leds[i] = CHSV(hue, 255, 150);
              } else {
                  leds[i] = CHSV(hue, 255, 60);  
              }
            }
            hue+=85;
            if (hue>255){hue-=255;}
            
            ///Set Minutes
            offset = 6;
            for (int i = (0+offset); i < (6+offset); i++) {
              if (bitRead(minutes, (i-offset))) {
                  leds[i] = CHSV(hue, 255, 150);
              } else {
                  leds[i] = CHSV(hue, 255, 60);  
              }
            }
            hue+=85;
            if (hue>255){hue-=255;}
    
            ///Set Hours
            offset = 12;
            for (int i = (0+offset); i < (5+offset); i++) {
              if (bitRead(hours, (i-offset))) {
                  leds[i] = CHSV(hue, 255, 150);
              } else {
                  leds[i] = CHSV(hue, 255, 60);  
              }
            }
     
          break;

      case 2:
            ///Set Seconds
            for (int i = (0+offset); i < (6+offset); i++) {
              if (bitRead(seconds, (i-offset))) {
                  leds[i] = CHSV(0, 255, 10*multiplier);
              } else {
                  leds[i] = CHSV(0, 255, 5*multiplier);  
              }
            }
            
            ///Set Minutes
            offset = 6;
            for (int i = (0+offset); i < (6+offset); i++) {
              if (bitRead(minutes, (i-offset))) {
                  leds[i] = CHSV(95, 255, 10*multiplier);
              } else {
                  leds[i] = CHSV(95, 255, 5*multiplier);  
              }
            }
    
            ///Set Hours
            offset = 12;
            for (int i = (0+offset); i < (5+offset); i++) {
              if (bitRead(hours, (i-offset))) {
                  leds[i] = CHSV(160, 255, 10*multiplier);
              } else {
                  leds[i] = CHSV(160, 255, 5*multiplier);  
              }
            }
     
          break;
      break;

      //very binary mode...seconds so far in the day
      case 3: 
          long DailySeconds = seconds + 60*minutes + 60*60*hours;
          for (int i = 0; i<17; i++){
              if (bitRead(DailySeconds, i)) {
                  leds[i] = CHSV(hue, 255, 150);
              } else {
                  leds[i] = CHSV(hue, 255, 60);  
              }
              hue+=15;
              if (hue>255){hue-=255;}
          }
          break; 



/*
      //hours minutes seconds   ...RGB  with adaptive brightness            
      case 3: 
            ///Set Seconds
            for (int i = (0+offset); i < (6+offset); i++) {
              if (bitRead(seconds, (i-offset))) {
                  leds[i] = CHSV(0, 255, 10*multiplier);
              } else {
                  leds[i] = CHSV(0, 255, 5*multiplier);  
              }
            }
            
            ///Set Minutes
            offset = 6;
            for (int i = (0+offset); i < (6+offset); i++) {
              if (bitRead(minutes, (i-offset))) {
                  leds[i] = CHSV(95, 255, 10*multiplier);
              } else {
                  leds[i] = CHSV(95, 255, 5*multiplier);  
              }
            }
    
            ///Set Hours
            offset = 12;
            for (int i = (0+offset); i < (5+offset); i++) {
              if (bitRead(hours, (i-offset))) {
                  leds[i] = CHSV(160, 255, 10*multiplier);
              } else {
                  leds[i] = CHSV(160, 255, 5*multiplier);  
              }
            }
     
          break;
          */
          
  }
  
   FastLED.show(); // This sends the updated pixel color to the hardware.

}


int checkBrightness(){
  int sensorVal = analogRead(LDR);  
  float _multiplier = map(sensorVal,0,50,5,25);
  _multiplier = max(_multiplier, 5);               //ensures sensor reading is in range
  _multiplier = min(_multiplier, 20);
  multiplier = (99*multiplier + _multiplier)/100;   //smoothing
}
