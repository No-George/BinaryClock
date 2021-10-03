void readButtons(){

  
if (digitalRead(SW1)==0){
  Serial.println("SW1 press detected");
  while (digitalRead(SW1)==0){
    if (digitalRead(SW2)==0){
      while (digitalRead(SW2)==0){}
      while (digitalRead(SW1)==0){}
      binaryMode +=1;
      hours-=1;
      Serial.println("SW2 press also detected");      
      }
    }
  hours+=1;
  if (hours > 23) {hours = 0;}
  faboRTC.setDate(years,months,days,hours,minutes,seconds);
}

if (digitalRead(SW2)==0){
  Serial.println("SW2 press detected");
  while (digitalRead(SW2)==0){
        if (digitalRead(SW1)==0){
      while (digitalRead(SW1)==0){}
      while (digitalRead(SW2)==0){}
      binaryMode +=1;
      minutes-=1;    
      Serial.println("SW1 press also detected");  
      }
    }
  minutes+=1;
  if (minutes > 59) {minutes = 0;}
  faboRTC.setDate(years,months,days,hours,minutes,seconds);
}

if (binaryMode>3){binaryMode=0;}
  
}
