/* LED ETCH-A-SKETCH
 *  
 * Draws a line of lights in 3-D space. One potentiometer selects 
 * between the x, y, or z axis, while a second potentiometer causes
 * the line to travel in the forward or backward direction.
 *
 * ENGR 40M
 * May 2017
 */

// Arrays of pin numbers. Fill these in with the pins to which you connected
// your anode (+) wires and cathode (-) wires. Hint: if you order these
// intelligently, it will make your mapping getLEDState() function a lot
// simpler!
const byte ANODE_PINS[8] = {10, 11, 12, 13,    // Top
                            A2, A3, A4, A5};   // Bottom
const byte CATHODE_PINS[8] = {2, 3, 4, 5,      // Outside
                              6, 7, 8, 9};     // Inside

const byte AXIS_PIN = A0;
const byte VELOCITY_PIN = A1;

void setup()
{
  // Make all of the anode (+) wire and cathode (-) wire pins outputs.
  for (byte i = 0; i < 8; i++) {
    pinMode(ANODE_PINS[i], OUTPUT);
    pinMode(CATHODE_PINS[i], OUTPUT);
  }
  
  // Turn off everything.
  for (byte i = 0; i < 8; i++)
  {
    // No current can flow until anode pin(s)
    // set low, given PMOS transistors.
    digitalWrite(ANODE_PINS[i], HIGH);
    digitalWrite(CATHODE_PINS[i], HIGH);
  }

  pinMode(AXIS_PIN, INPUT);
  pinMode(VELOCITY_PIN, INPUT);

  // Initialize serial communication
  // (to be read by Serial Monitor on your computer).
  Serial.begin(115200);
  Serial.setTimeout(100);
}

/* Function: getLEDState
 * ---------------------
 * Returns the state of the LED in a 4x4x4 pattern array, each dimension
 * representing an axis of the LED cube, that corresponds to the given anode (+)
 * and cathode (-) wire number.
 *
 * This function is called by display(), in order to find whether an LED for a
 * particular anode (+) and cathode (-) wire should be switched on.
 * 
 * Coordinate space is defined such that, when facing the cube with
 * the anode connections on the left and the cathode connections in
 * the back:
 * - x values increase from left to right
 * - y values increase from from top to bottom
 * - z values increase from front to back
 */
inline byte getLEDState(byte pattern[4][4][4], byte aNum, byte cNum)
{
  byte x, y, z;
  
  if (aNum >= 4)             // Top anode:     A2 <= pin <= A5
  {
    if (cNum < 4)            // Outer cathode:  2 <= pin <= 5
    {
      x = 3 - cNum;
      y = 0;
      z = 7 - aNum;
    }
    else  // cNum >= 4       // Inner cathode:  6 <= pin <= 9
    {
      x = 7 - cNum;
      y = 1;
      z = 7 - aNum;
    }
  }
  else  // aNum < 4          // Bottom anode:  10 <= pin <= 13
  {
    if (cNum >= 4)           // Inner cathode:  6 <= pin <= 9
    {
      x = 7 - cNum;
      y = 2;
      z = 3 - aNum;
    }
    else  // cNum < 4        // Outer cathode:  2 <= pin <= 5
    {
      x = 3 - cNum;
      y = 3;
      z = 3 - aNum;
    }
  }

  // Cube indexing pattern.
  return pattern[z][y][x];
}

/* Function: display
 * -----------------
 * Runs through one multiplexing cycle of the LEDs, controlling which LEDs are
 * on.
 * 
 * Parameter `brightness` can have a value between 1 and 16 inclusive.
 *
 * During this function, LEDs that should be on will be turned on momentarily,
 * one row at a time. When this function returns, all the LEDs will be off
 * again, so it needs to be called continuously for LEDs to be on.
 */
void display(byte pattern[4][4][4], byte brightness)
{
  if (brightness > 16 || brightness < 1) return;

  // Determinte number of microseconds out of the 1000 microsecond 
  // (1 millisecond) time division period for which to keep light
  // turned on.
  int timeOn = 1000 / 16 * brightness;
  
  for (byte aNum = 0; aNum < 8; aNum++) // iterate through anode (+) wires
  {
    // Set up all the cathode (-) wires first.
    for (byte cNum = 0; cNum < 8; cNum++) // iterate through cathode (-) wires
    {
      byte value = getLEDState(pattern, aNum, cNum); // look up the value

      // Activate the cathode (-) wire if `value` is > 0, otherwise deactivate it.
      digitalWrite(CATHODE_PINS[cNum], value > 0 ? LOW : HIGH);
    }

    // Activate the anode (+) wire (without condition).
    digitalWrite(ANODE_PINS[aNum], LOW);

    delayMicroseconds(timeOn);

    // We're now done with this row, so deactivate the anode (+) wire.
    digitalWrite(ANODE_PINS[aNum], HIGH);

    // Wait remainder of one second.
    delayMicroseconds(1000 - timeOn);
  }
}

void loop()
{
  static byte ledPattern[4][4][4]; // 1 for on, 0 for off

  // byte x = 0;
  // byte y = 0;
  // byte z = 0;

  // Toggle the LED state.
  ledPattern[z][y][x] = !ledPattern[z][y][x];

  // This function gets called every loop.
  display(ledPattern, 16);

  Serial.print("AXIS PIN READING: ");
  Serial.println(analogRead(AXIS_PIN));
  Serial.print("VEL PIN READING: ");
  Serial.println(analogRead(VELOCITY_PIN));
}

