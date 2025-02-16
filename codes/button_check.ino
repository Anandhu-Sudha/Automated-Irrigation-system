// Pin where the button is connected
const int buttonPin = 6;

void setup() {
  // Start the Serial Monitor communication
  Serial.begin(9600);

  // Initialize the button pin as an input with internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // Read the button state (LOW when pressed, HIGH when not pressed)
  int buttonState = digitalRead(buttonPin);

  // Print the status to the Serial Monitor
  if (buttonState == LOW) {
    Serial.println("Button Pressed");
  } else {
    Serial.println("Button Released");
  }

  // Small delay for better readability
  delay(200);
}
