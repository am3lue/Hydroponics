#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

#define sensor A0
#define valve 8

RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Adjust the I2C address if necessary

void setup() {
  pinMode(sensor, INPUT);
  pinMode(valve, OUTPUT);
  Serial.begin(9600);
  Wire.begin();
  
  rtc.begin();
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set RTC to compile time if power was lost
  }

  lcd.init();
  lcd.backlight();
  lcd.print("System Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  DateTime muda = rtc.now();
  int sensorValue = analogRead(sensor);  // Read sensor value

  // Print sensor value to Serial Monitor
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  // Morning watering from 6:00 AM to 10:00 AM
  bool asubuhi = (muda.hour() >= 6 && muda.hour() < 10);

  // Evening watering from 4:00 PM to 6:00 PM
  bool jioni = (muda.hour() >= 16 && muda.hour() < 18);

  // Control watering
  if ((asubuhi || jioni) && (sensorValue <= 600)) {
    digitalWrite(valve, HIGH);
    Serial.println("Watering now!");
    lcd.setCursor(0, 0);
    lcd.print("Watering Plants   ");
  } else {
    digitalWrite(valve, LOW);
    Serial.println("Watering stopped!");
    lcd.setCursor(0, 0);
    lcd.print("Watering Stopped  ");
  }

  // Display current time on LCD
  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  lcd.print(muda.hour());
  lcd.print(":");
 // Adds leading zero to minutes
  lcd.print(muda.minute());

  lcd.print(":");
  lcd.print(muda.second());
  delay(1000); // Update every second
}
