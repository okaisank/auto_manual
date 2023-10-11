#include <DHT.h>

#define DHTPIN 2 // Digital pin where the DHT sensor is connected
#define DHTTYPE DHT22 // Type of the DHT sensor

DHT dht(DHTPIN, DHTTYPE);
int relayPin = 4; // Digital pin connected to the relay
int buttonPin = 5; // Digital pin connected to the push-button switch
int mode = 1; // 1 for auto mode, 0 for manual mode

void setup() {
  dht.begin();
  pinMode(relayPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Enable internal pull-up resistor for the button
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if the button is pressed to toggle between auto and manual modes
  if (digitalRead(buttonPin) == LOW) {
    mode = 1 - mode; // Toggle between 0 and 1
    delay(500); // Debounce delay
  }

  if (mode == 1) { // Auto mode
    if (temperature > 27 && humidity > 80) {
      digitalWrite(relayPin, LOW); // Turn off the pump
    } else {
      digitalWrite(relayPin, HIGH); // Turn on the pump
    }
  } else { // Manual mode
    // Add manual control logic here if needed
  }
}
