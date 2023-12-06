void mechanismsInit(){
    servo1.write(servo1aPointAngle);
    delay(100);
    servo2.write(servo2aPointAngle);

}

void oneClick(){
    servo1.write(servo1bPointAngle);
    delay(500);
    servo1.write(servo1aPointAngle);
    lastWateringTime = timeInMinutesNow;
     currentCycleNumber++;
     publish_Clicklog(false);


}
void secondClick(){
    servo2.write(servo2bPointAngle);
    delay(500);
    servo2.write(servo2aPointAngle);
}

void longDelayClick(){

    servo2.write(servo2bPointAngle);
    delay(300);
    servo2.write(servo2aPointAngle);
    longDelayClickTime = timeInMinutesNow;
    delay(1000);
     publish_Clicklog(true);
    oneClick();

}


void testSerial(){
  Serial.println("Choose option from menu:");
  Serial.println("1: OneClick");
  Serial.println("2: LongDelayClick");
  Serial.println("3: TimeInMinutesNow");
  
  
    
    while (Serial.available() == 0)
    {
    }
    int option = Serial.parseInt();
    switch(option){
      case 1: 
        oneClick();
        break;
       case 2:
         secondClick();
        break;
        case 3: 
        getTime();
        Serial.println(timeInMinutesNow);
       
    }
}
