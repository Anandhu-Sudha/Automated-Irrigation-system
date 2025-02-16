#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

void setup() 
  {
  Serial.begin(9600);

  // Initialize the RTC module
  if (!rtc.begin()) 
  {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // Manually set the RTC to a specific time (you can remove this line later once the RTC is set)
  rtc.adjust(DateTime(2025, 1, 17, 11, 17, 0)); // Set to a time close to your target time for testing

  Serial.println("RTC initialized.");
  }

void loop() {
  DateTime now = rtc.now();

  // Print the current time every second to the Serial Monitor
  printCurrentTime();
  delay(1000);

}

void printCurrentTime() {
  DateTime now = rtc.now();
  
  // Print the current time in the format: YYYY/MM/DD HH:MM:SS
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
}
