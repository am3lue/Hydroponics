//The components required
/*
1. LCD display
2. pump or valve 
3. Arduino MEGA or Arduino UNO or Arduino nano Or any other arduino compactible boards
4. Connectors, jumpers, bread boards or motherboards
5. Realy Switch
6. and other tools supporting wiring and advancing the project 
*/

//including the things

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define relay 8


void setup() {
  pinMode(relay , OUTPUT);
  //intialize the lcd.....

  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hydroponics");
  lcd.setCursor((16-7),1);
  lcd.print("By Blue");
  delay(4000);

}

//the function for printing in the lcd (the time part)
String print(int print){//introdusing my function as a string
  lcd.setCursor(0,1);//setting cursor of rem time tag
  lcd.print("Rem time: ");// telling the user the remaining time (as a tag)
  lcd.setCursor(10, 1);//seting cursor of the screen
  lcd.print(print);//print the input tapped
  lcd.print(" Secs");//printing the seconds SI unit
  
}

///the function for waiting before goes on
int wait(int time){
  Serial.println("The time to rest");// serial rpinting
  lcd.setCursor(0,0);//setting cursor 
  lcd.print("Time to rest!");//displaying in the lcd
  for (int i = time; i >= 1; i--){
    digitalWrite(relay , LOW);//turning off the relay switch
    print(i);//printing in the screen
    Serial.println(i);//printing in the serial
    delay(1000);//having a delaying time
  }
}

///the function for watring time
int water(int time){
  Serial.println("The time to water");// Serial printing 
  lcd.setCursor(0, 0);//lcd seting cursor
  lcd.print("Time to Water!");// lcd printing
  for (int i = time; i >= 1; i--){
    Serial.println(i);//serial printing the time
    print(i);// callin the function for printing the number
    digitalWrite(relay , HIGH); // making relay on
    delay(1000);//have a delaying time
  }
}

void loop() {// sometimes is refered to as the main function which runs the code repeatedly
  water(20);//WATERING TIME IN SECONDS
  lcd.clear();
  wait(30);// RESTING TIME IN SECONDS
  lcd.clear();
}
