#include "RTClib.h"
#include <SPI.h>
RTC_PCF8563 rtc;
DateTime timeNow;


void setTime(){
   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void rtc_init(){
    if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }
     rtc.start();
}
void getTime(){
  timeNow = rtc.now();
  
 timeInMinutesNow = timeNow.hour() * 60 + timeNow.minute();
}

