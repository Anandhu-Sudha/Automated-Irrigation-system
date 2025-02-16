#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16-char, 2-line display
DS3231 rtc(SDA, SCL);
Time t;

// Relay pins
int Relay1 = 4;  // Relay 1 pin
int Relay2 = 5;  // Relay 2 pin

// LED pins for Relay 1 and Relay 2
int LED_Relay1 = 7;  // LED for Relay 1
int LED_Relay2 = 8;  // LED for Relay 2


int buttonPin = 6;  

bool buttonPressed = false;  // To track if the button has been pressed

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  rtc.begin();         // Initialize RTC
  lcd.init();          // Initialize LCD
  lcd.backlight();     // Turn on the backlight
  
  pinMode(buttonPin, INPUT_PULLUP);  // Set the button pin as input with pull-up resistor
  pinMode(Relay1, OUTPUT);  // Set relay pin as output
  pinMode(Relay2, OUTPUT);  // Set relay pin as output
  pinMode(LED_Relay1, OUTPUT);  // Set LED pin for Relay 1 as output
  pinMode(LED_Relay2, OUTPUT);  // Set LED pin for Relay 2 as output
  
  digitalWrite(Relay1, LOW);  // Ensure Relay1 is OFF initially
  digitalWrite(Relay2, LOW);  // Ensure Relay2 is OFF initially
  digitalWrite(LED_Relay1, LOW);  // Ensure LED for Relay 1 is OFF initially
  digitalWrite(LED_Relay2, LOW);  // Ensure LED for Relay 2 is OFF initially

  // Startup sequence: Display "SMART" and "IRRIGATION S/M"
  lcd.setCursor(5, 0);
  lcd.print("SMART");
  lcd.setCursor(1, 1);
  lcd.print("IRRIGATION S/M");
  delay(2000);  // Wait for 2 seconds
  
  // Display "BY" and "ANANDHU"
  lcd.clear();
  lcd.setCursor(7, 0);
  lcd.print("BY");
  lcd.setCursor(1, 1);
  lcd.print("ANANDHU SUDHA");
  delay(2000);  // Wait for 2 seconds
  
  // Clear the screen and show the current time
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
}

void loop() {
  int buttonState = digitalRead(buttonPin);  // Read the button state
  
  
  Serial.print("Button State: ");
  Serial.println(buttonState);
  
  // Check if the button is pressed (LOW indicates the button is pressed)
  if (buttonState == LOW && !buttonPressed) {
    buttonPressed = true;
    Serial.println("Button pressed, triggering relay sequence");

    // Trigger Relay 1 for 5 minutes
    lcd.clear();  // Clear screen before printing new text
    lcd.print("SPRINKLER ON");
    digitalWrite(Relay1, HIGH);
    digitalWrite(LED_Relay1, HIGH);  // Turn on LED for Relay 1
    
    // Countdown for Relay 1 (5 minutes)
    for (int i = 300; i >= 0; i--) {  // 5 minutes = 300 seconds
      lcd.setCursor(0, 1);
      lcd.print("Countdown: ");
      lcd.print(i);
      lcd.print("s");
      delay(1000);  // Delay for 1 second
    }

    digitalWrite(Relay1, LOW);
    digitalWrite(LED_Relay1, LOW);  // Turn off LED for Relay 1
    lcd.clear();  // Clear screen before printing new text
    lcd.print("SPRINKLER OFF");
    delay(2000);  // Wait for 2 seconds

    // Trigger Relay 2 for 5 minutes
    lcd.clear();  // Clear screen before printing new text
    lcd.print("IRRIGATION ON");
    digitalWrite(Relay2, HIGH);
    digitalWrite(LED_Relay2, HIGH);  // Turn on LED for Relay 2
    
    // Countdown for Relay 2 (5 minutes)
    for (int i = 300; i >= 0; i--) {  // 5 minutes = 300 seconds
      lcd.setCursor(0, 1);
      lcd.print("Countdown: ");
      lcd.print(i);
      lcd.print("s");
      delay(1000);  // Delay for 1 second
    }

    digitalWrite(Relay2, LOW);
    digitalWrite(LED_Relay2, LOW);  // Turn off LED for Relay 2
    lcd.clear();  // Clear screen before printing new text
    lcd.print("IRRIGATION OFF");
    delay(2000);  // Wait for 2 seconds
    lcd.clear();  // Clear the screen before showing time
    lcd.setCursor(0, 0);  // Ensure "Time: " is printed on the first line
    lcd.print("Time: ");

    Serial.println("Irrigation sequence completed, waiting for next button press");
  }

  // Reset the buttonPressed flag when the button is released
  if (buttonState == HIGH) {
    buttonPressed = false;
  }

  // Regular relay control based on RTC time
  t = rtc.getTime();

  // Handle Relay 1 control based on specific hours (7:00 AM, 9:00 AM, 11:00 AM, etc.)
  if ((t.hour == 7 || t.hour == 9 || t.hour == 11 || t.hour == 13 || t.hour == 15 || t.hour == 17 || t.hour == 19) && t.min == 0) {
    digitalWrite(Relay1, HIGH);  // Turn Relay 1 ON
    digitalWrite(LED_Relay1, HIGH);  // Turn on LED for Relay 1
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SPRINKLER ON");

    // Countdown for Relay 1 (5 minutes)
    for (int i = 300; i >= 0; i--) {
      int mins = i / 60;
      int secs = i % 60;
      lcd.setCursor(0, 1);
      lcd.print("Countdown: ");
      lcd.print(mins);
      lcd.print(":");
      if (secs < 10) lcd.print("0");
      lcd.print(secs);
      delay(1000);
    }

    digitalWrite(Relay1, LOW);
    digitalWrite(LED_Relay1, LOW);
    lcd.setCursor(0, 1);
    lcd.print("SPRINKLER OFF");
  }

  // Handle Relay 2 control based on specific hours (8:00 AM, 10:00 AM, 12:00 PM, etc.)
  if ((t.hour == 8 || t.hour == 10 || t.hour == 12 || t.hour == 14 || t.hour == 16 || t.hour == 18) && t.min == 0) {
    digitalWrite(Relay2, HIGH);  // Turn Relay 2 ON
    digitalWrite(LED_Relay2, HIGH);  // Turn on LED for Relay 2
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("IRRIGATION ON");

    // Countdown for Relay 2 (5 minutes)
    for (int i = 300; i >= 0; i--) {
      int mins = i / 60;
      int secs = i % 60;
      lcd.setCursor(0, 1);
      lcd.print("Countdown: ");
      lcd.print(mins);
      lcd.print(":");
      if (secs < 10) lcd.print("0");
      lcd.print(secs);
      delay(1000);
    }

    digitalWrite(Relay2, LOW);
    digitalWrite(LED_Relay2, LOW);
    lcd.setCursor(0, 1);
    lcd.print("IRRIGATION OFF");
  }

  // Display the current time in the first line
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.setCursor(6, 0);
  lcd.print(t.hour);
  lcd.print(":");
  if (t.min < 10) lcd.print("0");
  lcd.print(t.min);
  lcd.print(":");
  if (t.sec < 10) lcd.print("0");
  lcd.print(t.sec);

  delay(100);  // Small delay to stabilize button reading
}
