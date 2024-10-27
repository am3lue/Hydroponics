#define sensor A0
#define  sensord 3
#define valve 13

#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;


void setup() {
  pinMode(sensor , INPUT);
  pinMode(sensord, OUTPUT);
  pinMode(valve , OUTPUT);

  Serial.begin(9600);

  Wire.begin();
  rtc.begin();
  while (!rtc.begin()){
    Serial.println("Couldn't find RTC module in the connection! ...");
  }
  Serial.println("Am Awake!");
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

}

void loop() {

  DateTime muda = rtc.now();

  int value = analogRead(A0);

 // bool kufungua_maji = ((muda.hour() == 6 && muda.minute() == 0) || (muda.hour() == 16 && muda.minute() == 0));
 // bool kufunga_maji = ((muda.hour() ==10 && muda.minute() == 0) || (muda.hour() == 18 && muda.minute() == 0));

  bool kufungua_maji = ((muda.minute() == 40) || (muda.minute() == 45));
  bool kufunga_maji = ((muda.minute() == 41) || (muda.minute() == 46));

  if (kufungua_maji){
    Serial.println("Watering now!");
    digitalWrite(valve, 1);
  }

  if (kufunga_maji){
    Serial.println("Resting now!");
    digitalWrite(valve, 0);
  }

  Serial.print("Time: ");
  Serial.print(muda.hour());
  Serial.print(":");
  Serial.println(muda.minute());
  delay(1000);
  // put your main code here, to run repeatedly:

}
