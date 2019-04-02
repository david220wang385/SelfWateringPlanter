// EGN2020C Final Project: Self-Watering Planter 
// By:        David Wang
// Date:      4/2/19
// Version:   v1.0

// Define pins
const int soilOutput = A0; // For reading analog moisture values
const int soilPower = 7; // For powering sensor on/off
const int pumpPin = 9; // For powering pump on/off

// For determining if soil is wet/dry
const int lowerMoistThreshold = 250; 
const int upperMoistThreshold = 1000;

String soilStatus = ""; // Formatting output
int pumpSpeed = 0; // Controlling the speed of the pump

  
/* ====================================================
Soil sensor values higher = more dry (top threshold)
Soil sensor values lower = more wet (bottom threshold)
==================================================== */ 

void setup() {
  Serial.begin(9600); 
  pinMode(pumpPin, OUTPUT); // Set pump control pin to be output
  pinMode(soilPower, OUTPUT); // Set soil power pin as an output
  digitalWrite(soilPower, LOW); //Set pin to LOW so no power is flowing through the sensor
}

void loop() {
  int sensorValue = readSoil(); // Retrieve values from the soil moisture sensor

  // Print out raw soil moisture values
  Serial.print("Moisture:"); 
  Serial.print(sensorValue);
  Serial.println();

  // If value above upper threshold (too dry), turn on pump
  if(sensorValue > upperMoistThreshold) {
      soilStatus = "DRY";
      pumpSpeed += 10; // Gradually increases the feed rate of water
      analogWrite(pumpPin, pumpSpeed);
  }

  // Otherwise turn pump off
  else{
      soilStatus = "WET";
      pumpSpeed = 0;
      analogWrite(pumpPin, 0); // 0-255 range for pump
  }

  // Print out soil status
  Serial.print("Soil Status: " + soilStatus + "\n");
}

int readSoil(){
  
  digitalWrite(soilPower, HIGH); // Turn soil senors on
  delay(500); // 500 ms 
  int value = analogRead(soilOutput);// Read analog value from sensor
  digitalWrite(soilPower, LOW); // Turn sensor OFF
  return value;
  
}
