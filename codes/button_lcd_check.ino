#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin where the button is connected
const int buttonPin = 6;

// Create an LCD object with I2C address 0x27 (common address for 16x2 LCD)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // (I2C address, columns, rows)

void setup() {
  // Initialize the button pin as an input with internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);

  // Initialize the LCD
  lcd.init();
  lcd.backlight();  // Turn on the LCD backlight
  
  // Display initial message
  lcd.setCursor(0, 0);
  lcd.print("Button Status:");
}

void loop() {
  // Read the button state (LOW when pressed, HIGH when not pressed)
  int buttonState = digitalRead(buttonPin);

  // Clear the LCD screen and display appropriate message
  lcd.setCursor(0, 1);  // Move the cursor to the second line
  if (buttonState == LOW) {
    lcd.print("Button Pressed   ");
  } else {
    lcd.print("Button Released ");
  }

  // Small delay for better readability
  delay(200);
}
