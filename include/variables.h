int currentServoAngle = 0;
  const char *ssid = "TechZone";
 const char *password = "Aaaa1111";

//   const char *ssid = "ZTE_73B506";
//  const char *password = "53108898";

//   const char *ssid = "Smbat`s iPhone";
//  const char *password = "smb111111";

//  const char *mqtt_server = "192.168.0.101"; //  your broker url

 const char *mqtt_server = "192.168.0.105";


 unsigned long lastReconnectAttempt;

// const char *currentServoAngleTopic = "currentServoAngle";
const char *wateringClickerTopic = "wateringClickerTopic";

const char *tasksUpdateTopic = "/watering_tasks";
const char *tasksReceivedTopic = "watering_tasks_received";
const char *publishClickLogTopic = "watering_click";
const char *errorTopic = "Errors";
const char *longDelayClickTopic = "longDelayClick";
const char *oneClickTopic = "oneClick";


const int mqtt_port = 1883;

static const int servoPin = 13;

StaticJsonDocument<96> doc;
StaticJsonDocument<96> errorDoc;


#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];



// unsigned long lastSensorsPublishTime;
int taskUpdateInterval = 15000;
int lastTaskNumber;
int currentCycleNumber = 0;
bool tasksForTodayFinished = true;
bool wateringOn= false;
bool wateringTaskReceived = false;
unsigned long lastTaskUpdateTime;
unsigned long lastWateringCheckTime;
int wateringCheckInterval = 60000;

int timeInMinutesNow;


bool wateringAllowed = false;
unsigned long lastWateringTime;
int delayForWakeUpClick = 180;//Minutes

long oneClickTime;
long longDelayClickTime;

/// Servo 

int servo1bPointAngle = 90;
int servo1aPointAngle = 0;

int servo2bPointAngle = 90;
int servo2aPointAngle = 0;
Servo servo1;
Servo servo2;

#define servo1Pin 14
#define servo2Pin 12



