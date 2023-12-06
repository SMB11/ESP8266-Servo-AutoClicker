#include <Arduino.h>

#ifdef ESP8266
#include <ESP8266WiFi.h> // Pins for board ESP8266 Wemos-NodeMCU
#else
#include <WiFi.h>
#include <SPIFFS.h>
#endif
#include <ArduinoJson.h>

#include <Servo.h>
#include <variables.h>
#include <functions.h>
#include <rtc.h>
#include <EEPROMAnything.h>
#include <StreamUtils.h>
#include <PubSubClient.h>



// // #include <WiFi.h>
// // #include <PubSubClient.h>
// // Date and time functions using a PCF8563 RTC connected via I2C and Wire lib
#include <task.h>
#include <mqtt_connect.h>
#include <mechanisms.h>
#include <watering.h>

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  tasks_init();

  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  // setup_wifi();
  // mqtt_init();
  rtc_init();
  // setTime();
  // default_taskInit();
  getTasks();
  Serial.println(tasks[0].task_number);
  Serial.println(tasks[1].task_number);
  checkTasks();
  mechanismsInit();
  Serial.println("Setup Finished");
  Serial.println(currentTask.task_number);
}

void loop()
{
  // mqtt_loop();
  // unsigned long now = millis();
  // if (now - lastTaskUpdateTime >= taskUpdateInterval)
  // {
  //   lastTaskUpdateTime = now;
  //   //  getSensorsData();
  //   // publish_sensorData();
  //   checkTasks();

  //   Serial.println(currentTask.task_number);
  //   Serial.println(timeInMinutesNow);
  //   Serial.println(tasksForTodayFinished);
  //   Serial.println(currentCycleNumber);
  //   Serial.println(lastWateringTime);
  // }
  // if (now - lastWateringCheckTime >= wateringCheckInterval)
  // {
  //   lastWateringCheckTime = now;
  //   checkWateringAllowed();
  // }


   testSerial();
   delay(1000);
}
