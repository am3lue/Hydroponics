#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

// Pin definitions
const int moistureSensor1Pin = A0;
//const int moistureSensor2Pin = A1;
const int valvePin = 13; // Connect relay or MOSFET to control valve here

// Moisture threshold for irrigation
const int moistureThreshold = 500; // Adjust based on calibration

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  pinMode(valvePin, OUTPUT);
  digitalWrite(valvePin, LOW); // Start with valve off
}

void loop() {
  DateTime now = rtc.now();
  
  // Read moisture levels
  int moistureLevel1 = analogRead(moistureSensor1Pin);
  //int moistureLevel2 = analogRead(moistureSensor2Pin);
  int averageMoisture = (moistureLevel1 + 0);//moistureLevel2) / 2;

  // Check for specific irrigation times and soil moisture
  bool morningTime = (now.hour() == 6 && now.minute() == 0); // 6:00 AM
  bool morningEndTime = (now.hour() == 10 && now.minute() == 0); // 10:00 AM
  bool eveningTime = (now.hour() == 16 && now.minute() == 0); // 4:00 PM
  bool eveningEndTime = (now.hour() == 19 && now.minute() == 0); // 7:00 PM

  // Open valve at start times if soil is dry
  if ((morningTime || eveningTime) && averageMoisture < moistureThreshold) {
    digitalWrite(valvePin, HIGH); // Open valve
    Serial.println("Irrigation ON");
  }

  // Close valve at end times
  if (morningEndTime || eveningEndTime && averageMoisture > moistureThreshold) {
    digitalWrite(valvePin, LOW); // Close valve
    Serial.println("Irrigation OFF");
  }

  // Print current time and moisture levels for monitoring
  Serial.print("Time: ");
  Serial.print(now.hour());
  Serial.print(":");
  Serial.println(now.minute());
  
  Serial.print("Moisture 1: ");
  Serial.println(moistureLevel1);
 /* Serial.print(" | Moisture 2: ");
  Serial.println(moistureLevel2);
*/
  delay(1000); // Check every minute
}
