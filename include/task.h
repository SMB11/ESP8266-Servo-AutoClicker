

struct WateringTask
{
    int task_number;
    int start_time;
    int end_time;
    int numOfCycles;
    int durationOfCycles;
    int minimumWateringDelay;
}; 

WateringTask tasks[] = {
    {1, 540, 660, 2, 5, 40},
    {2, 660, 1080, 5, 3, 30},

};
WateringTask tasks[2];
WateringTask newTasks[2];
WateringTask currentTask;

void tasks_init()
{
    EEPROM.begin(512);
}
void default_taskInit(){

    EEPROM_writeAnything(0,tasks);
    EEPROM.commit();
}
void getTasks(){
     EEPROM_readAnything(0, tasks);
    

    //  if (/* condition */)
    //  {
    //      /* code */
    //  }
     
}
void updateTask(int task_number, int start_time, int end_time, int numOfCycles, int durationOfCycles, int minimumWateringDelay)
{
    if (currentTask.task_number != task_number)
    {
        lastTaskNumber = currentTask.task_number;
        currentTask.task_number = task_number;
        currentTask.start_time = start_time;
        currentTask.end_time = end_time;
        currentTask.numOfCycles = numOfCycles;
        currentTask.durationOfCycles = durationOfCycles;
        currentTask.minimumWateringDelay = minimumWateringDelay;
        currentCycleNumber = 0;
        tasksForTodayFinished = false;
         Serial.println(" Task Updated , Current Task Num: ");
        Serial.println(currentTask.task_number);
    }
}

void checkTasks()
{
   getTasks();
   getTime();
    for (int i = 0; i < (int)(sizeof(tasks) / sizeof(tasks[0])); i++)
    {
        if (timeInMinutesNow >= tasks[i].start_time && timeInMinutesNow < tasks[i].end_time)
        {
            updateTask(tasks[i].task_number, tasks[i].start_time, tasks[i].end_time, tasks[i].numOfCycles, tasks[i].durationOfCycles, tasks[i].minimumWateringDelay);
            Serial.print("In updateTask 1: ");
            // Serial.println(currentTask.task_number);
        }
        else if (tasks[i].start_time > tasks[i].end_time)
        {
            if ((timeInMinutesNow > tasks[i].start_time && timeInMinutesNow < (tasks[i].end_time + 1440)) || (timeInMinutesNow < tasks[i].end_time && timeInMinutesNow > tasks[i].start_time - 1440))
            {
                updateTask(tasks[i].task_number, tasks[i].start_time, tasks[i].end_time, tasks[i].numOfCycles, tasks[i].durationOfCycles, tasks[i].minimumWateringDelay);
                // Serial.print("Current Task Num: ");
                  Serial.print("In updateTask 2: ");
                // Serial.println(currentTask.task_number);
            }
        }
        // else
        // {
        //     tasksForTodayFinished = true;
        // }
        // TODO: ELSE current task = standart task
    }
}

// void update_task_EEPROM(WateringTask tasks[])
// {
//    EEPROM_writeAnything(0, tasks);
//     // EEPROM.put(0, task[0]);
//     EEPROM.commit();
// }

void parseTasks(byte *payload)
{
    StaticJsonDocument<768> doc;

    DeserializationError error = deserializeJson(doc, payload);

    if (error)
    {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
    }

    for (JsonObject item : doc.as<JsonArray>())
    {

        int task_number = item["task_number"];        
        const char *start_time = item["start_time"];  
        const char *end_time = item["end_time"];      
        int numOfCycles = item["numOfCycles"];          
        int durationOfCycles = item["durationOfCycles"];     
        int minimumWateringDelay = item["minimumWateringDelay"]; 

        newTasks[task_number - 1].task_number = task_number;
        newTasks[task_number - 1].start_time = convertToMinutes(start_time);
        newTasks[task_number - 1].end_time = convertToMinutes(end_time);
        newTasks[task_number - 1].numOfCycles = numOfCycles;
        newTasks[task_number - 1].durationOfCycles = durationOfCycles;
        newTasks[task_number - 1].minimumWateringDelay = minimumWateringDelay;
        Serial.println(task_number);
        Serial.println(convertToMinutes(start_time));
        Serial.println(convertToMinutes(end_time));
        Serial.println(numOfCycles );
        Serial.println(durationOfCycles);
        Serial.println(minimumWateringDelay);
        
        // Serial.println(tasks[task_number - 1].task_number);
    }
    // update_task_EEPROM(newTasks);
    EEPROM_writeAnything(0,newTasks);
    EEPROM.commit();
  checkTasks();
    Serial.println("New Tasks Updated");
}

