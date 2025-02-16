#include <DS3231.h>

int Relay = 4;

DS3231 rtc(SDA, SCL);
Time t;

const int OnHour = 9;  // SET TIME TO ON RELAY (24 HOUR FORMAT)
const int OnMin = 51;
const int OffHour = 9; // SET TIME TO OFF RELAY
const int OffMin = 52;

bool ledOn = false;  // Flag to track if the relay is already turned ON
bool ledOff = false; // Flag to track if the relay is already turned OFF

void setup() {
  Serial.begin(9600);
  rtc.begin();
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, LOW);  // Ensure the relay is initially off
}

void loop() {
  t = rtc.getTime();
  Serial.print(t.hour);
  Serial.print(" hour(s), ");
  Serial.print(t.min);
  Serial.print(" minute(s)");
  Serial.print(" ");
  Serial.print(t.sec);
  Serial.print(" second(s)");
  Serial.println(" ");
  delay(1000);

  // Check if it's time to turn the relay ON
  if (t.hour == OnHour && t.min == OnMin && !ledOn) {
    digitalWrite(Relay, HIGH);  // Turn the relay ON
    digitalWrite(LED_BUILTIN, HIGH);  // Turn on the built-in LED
    Serial.println("LIGHT ON");
    ledOn = true;  // Set flag to true to avoid repeating the message
  }

  // Check if it's time to turn the relay OFF
  if (t.hour == OffHour && t.min == OffMin && !ledOff) {
    digitalWrite(Relay, LOW);  // Turn the relay OFF
    digitalWrite(LED_BUILTIN, LOW);  // Turn off the built-in LED
    Serial.println("LIGHT OFF");
    ledOff = true;  // Set flag to true to avoid repeating the message
  }
  
  // Reset flags at the start of the next cycle
  if (t.min != OnMin && t.min != OffMin) {
    ledOn = false;
    ledOff = false;
  }
}
