/*
 * Arduino code to simply send the value of an analog input pin to the computer.
 *
 * Based on public domain code available at http://arduino.cc/en/Tutorial/Graph
 *
 * ENGR 40M, Fall 2014
 */

// Analog input pin to send to computer.
const uint8_t inputPin = A5;

void setup() {
  Serial.begin(9600);
   pinMode(inputPin, INPUT);
}

void loop() {
  // Send the value
  Serial.println(analogRead(inputPin));

  // Wait a little while
  // You can change this to control the sample rate
  delay(2);
}
