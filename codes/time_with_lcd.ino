#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16-char, 2-line display
DS3231 rtc(SDA, SCL);
Time t;

int Relay = 5;  // Relay pin

const int OnHour = 11;  // SET TIME TO ON RELAY (24 HOUR FORMAT)
const int OnMin = 55;
const int OffHour = 11; // SET TIME TO OFF RELAY
const int OffMin = 56;

bool ledOn = false;  // Flag to track if the relay is already turned ON
bool ledOff = false; // Flag to track if the relay is already turned OFF

void setup() {
  Serial.begin(9600);
  rtc.begin();
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, LOW);  // Ensure the relay is initially off

  // Initialize the LCD
  lcd.init();
  lcd.backlight();    // Turn on the LCD backlight
}

void loop() {
  t = rtc.getTime();

  // Display time on LCD (first row)
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.print(t.hour);
  lcd.print(":");
  if (t.min < 10) lcd.print("0"); // Leading zero for minutes
  lcd.print(t.min);
  lcd.print(":");
  if (t.sec < 10) lcd.print("0"); // Leading zero for seconds
  lcd.print(t.sec);

  // Print time to Serial Monitor for debugging
  Serial.print(t.hour);
  Serial.print(" hour(s), ");
  Serial.print(t.min);
  Serial.print(" minute(s), ");
  Serial.print(t.sec);
  Serial.println(" second(s)");

  // Check if it's time to turn the relay ON
  if (t.hour == OnHour && t.min == OnMin && !ledOn) {
    digitalWrite(Relay, HIGH);  // Turn the relay ON
    digitalWrite(LED_BUILTIN, HIGH);  // Turn on the built-in LED
    Serial.println("LIGHT ON");

    // Update LCD display to show "LIGHT ON"
    lcd.setCursor(0, 1);  // Set cursor to the second row
    lcd.print("LIGHT ON       ");
    ledOn = true;  // Set flag to true to avoid repeating the message
    ledOff = false; // Reset the ledOff flag
  }

  // Check if it's time to turn the relay OFF
  if (t.hour == OffHour && t.min == OffMin && !ledOff) {
    digitalWrite(Relay, LOW);  // Turn the relay OFF
    digitalWrite(LED_BUILTIN, LOW);  // Turn off the built-in LED
    Serial.println("LIGHT OFF");

    // Update LCD display to show "LIGHT OFF"
    lcd.setCursor(0, 1);  // Set cursor to the second row
    lcd.print("LIGHT OFF      ");
    ledOff = true;  // Set flag to true to avoid repeating the message
    ledOn = false;  // Reset the ledOn flag

    // Wait for 2 seconds before clearing the message
    delay(2000);

    // Clear the LCD after 2 seconds
    lcd.clear();
  }

  // Reset flags at the start of the next cycle
  if (t.min != OnMin && t.min != OffMin) {
    ledOn = false;
    ledOff = false;
  }

  delay(1000);  // Wait for 1 second before checking again
}
