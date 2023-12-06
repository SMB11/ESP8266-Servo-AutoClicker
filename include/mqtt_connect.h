

WiFiClient espClient;
PubSubClient client(espClient);
// #include <task.h>
// #include <mechanisms.h>

void setup_wifi()
{
    delay(10);
    Serial.print("\nConnecting to ");
    Serial.println(ssid);

    // WiFi.mode(WIFI_STA);
    // WiFi.begin(ssid,password);

    // WiFi.mode(WIFI_STA); //Optional
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    randomSeed(micros());
    Serial.println("\nWiFi connected\nIP address: ");
    Serial.println(WiFi.localIP());
}

void wifi_reconnect()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        WiFi.begin(ssid, password);
    }
}

void pubslishError(const char *errType, const char *error)
{
    errorDoc["time"] = timeInMinutesNow;
    errorDoc["controller"] = "WateringClicker";
    errorDoc["type"] = errType;
    errorDoc["error"] = error;

    client.beginPublish(errorTopic, measureJson(errorDoc), true);
    BufferingPrint bufferedClient(client, 32);
    serializeJson(errorDoc, bufferedClient);
    bufferedClient.flush();
    client.endPublish();
}


//=====================================
boolean reconnect()
{
    // // Loop until we're reconnected
    // while (!client.connected())
    // {
    Serial.print("Attempting MQTT connection...");
    String clientId = "wateringClicker";

    if (client.connect(clientId.c_str()))
    {
        const char *type = "mqtt";
        const char *status = "reconnected";
        Serial.println(status);
        pubslishError(type, status);
        client.subscribe(tasksUpdateTopic); // subscribe the topics here
        client.subscribe(longDelayClickTopic); // subscribe the topics here
        client.subscribe(oneClickTopic); // subscribe the topics here
        Serial.print("Subscribed to ");
        Serial.println(tasksUpdateTopic);
        Serial.println(longDelayClickTopic);
        Serial.println(oneClickTopic);

        // client.subscribe(setTime_topic); // subscribe the topics here
    }
    else
    {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds"); // Wait 5 seconds before retrying
        delay(500);
    }
    // }
    delay(1000);
    return client.connected();
}


// void reconnect()
// {
//     // Loop until we're reconnected
//     while (!client.connected())
//     {
//         Serial.print("Attempting MQTT connection...");
//         String clientId = "wateringClicker";

//         if (client.connect(clientId.c_str()))
//         {
//             const char *type = "mqtt";
//             const char *status = "reconnected";
//             Serial.println(status);
//             pubslishError(type,status);
//             client.subscribe(tasksUpdateTopic); // subscribe the topics here
//             Serial.print("Subscribed to ");
//             Serial.println(tasksUpdateTopic);
//             client.subscribe(longDelayClickTopic); // subscribe the topics here
//             client.subscribe(oneClickTopic); // subscribe the topics here

//             // client.subscribe(setTime_topic); // subscribe the topics here
//         }
//         else
//         {
//             Serial.print("failed, rc=");
//             Serial.print(client.state());
//             Serial.println(" try again in 5 seconds"); // Wait 5 seconds before retrying
//             delay(5000);
//         }
//     }
// }

//=======================================
// This void is called every time we have a message from the broker

void callback(char *topic, byte *payload, unsigned int length)
{
    String incommingMessage = "";
    for (int i = 0; i < length; i++)
        incommingMessage += (char)payload[i];

    Serial.println("Message arrived [" + String(topic) + "]" + incommingMessage);

    //--- check the incomming message
    if (strcmp(topic, tasksUpdateTopic) == 0)
    {
        // Serial.println("Message received watering_tasks ");
        parseTasks(payload);
        client.publish(tasksReceivedTopic, "1");
    }

      if (strcmp(topic, oneClickTopic) == 0)
    {
        Serial.println("Message received oneClick ");
         servo1.write(servo1bPointAngle);
        delay(300);
        servo1.write(servo1aPointAngle);
    }
      if (strcmp(topic, longDelayClickTopic) == 0)
    {
        Serial.println("Message received longDelayClick ");
        servo2.write(servo2bPointAngle);
        delay(300);
        servo2.write(servo2aPointAngle);
    }
}

void mqtt_loop()
{

    if (!client.connected())
    {
        long now = millis();
        if (now - lastReconnectAttempt > 5000)
        {
            lastReconnectAttempt = now;
            // Attempt to reconnect
            if (reconnect())
            {
                lastReconnectAttempt = 0;
            }
        }
    }
    else
    {
        // Client connected

        client.loop();
    }
}
// void mqtt_loop()
// {
//      client.loop();
//     if (!client.connected())
//         reconnect(); // TODO: change reconnect function
         
// }
void publish_Clicklog(bool longClick)
{

    // doc["time"] = timeClient.getEpochTime();
    // doc["time"] = 123;
    doc["time"] = timeInMinutesNow;
    doc["task_number"] = currentTask.task_number;
    doc["cycle_number"] = currentCycleNumber;
    doc["lastWateringTime"] = lastWateringTime;
    doc["click"] = 1;
    doc['longclick'] = longClick;
    delay(1);
    client.beginPublish(publishClickLogTopic, measureJson(doc), true);
    BufferingPrint bufferedClient(client, 32);
    serializeJson(doc, bufferedClient);
    bufferedClient.flush();
    client.endPublish();
}



void mqtt_init()
{
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
    client.setBufferSize(1000);

    lastReconnectAttempt = 0;
}
