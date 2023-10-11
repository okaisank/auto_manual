#include <DHT.h>

#define DHTPIN 15 // Digital pin where the DHT sensor is connected
#define DHTTYPE DHT22 // Type of the DHT sensor

DHT dht(DHTPIN, DHTTYPE);
int relayPin = 32; // Digital pin connected to the relay
int buttonPin = 16; // Digital pin connected to the push-button switch
int mode = 1; // 1 for auto mode, 0 for manual mode
bool manualStop = false;

void setup() {

  Serial.begin(115200);
  dht.begin();
  pinMode(relayPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Enable internal pull-up resistor for the button
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
    if (isnan(temperature) || isnan(humidity)){ 
  Serial.println("Read from DHT Sensor Failed ");
  return;
  }
  Serial.print("\n"); 
  Serial.print("Temperature : "); 
  Serial.println(temperature); 
  
  Serial.print("Humidity : "); 
  Serial.println(humidity); 
  delay(1000);
  // Check if the button is pressed to toggle between auto and manual modes
  if (digitalRead(buttonPin) == HIGH) {
    mode = 1 - mode; // Toggle between 0 and 1
    delay(500); // Debounce delay
  }

  // Check for manual stop condition
  if (mode == 0 && digitalRead(buttonPin) == LOW) {
    manualStop = true;
    digitalWrite(relayPin, LOW); // Turn off the pump
    
  }

  if (!manualStop) {
    if (mode == 1) { // Auto mode
      if (temperature > 27 && humidity > 80) {
    //if (temperature > 35 && humidity > 90) {  
        digitalWrite(relayPin, HIGH); // Turn on the pump
        Serial.print(" Run Auto ");
      } else {
        digitalWrite(relayPin, LOW); // Turn off the pump
        Serial.print(" Mode Auto ");
      }
    } else { // Manual mode
      // Add manual control logic here if needed
      
      digitalWrite(relayPin, LOW); // Turn on the pump
      Serial.print(" Mode Manual");
   

  }
 }
}
