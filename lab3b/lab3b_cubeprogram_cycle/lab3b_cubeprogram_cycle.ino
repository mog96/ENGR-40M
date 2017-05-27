/* 
 * Blink every LED using the simplest possible iteration
 * through anode and cathode pins.
 */

const byte ANODE_PINS[8] = {10, 11, 12, 13,    // Top
                            A2, A3, A4, A5};   // Bottom
const byte CATHODE_PINS[8] = {2, 3, 4, 5,      // Outside
                              6, 7, 8, 9};     // Inside

void setup()
{
  // Make all of the anode (+) and cathode (-) wire pins outputs
  for (byte i = 0; i < 8; i++)
  {
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
}

void loop()
{
  for (byte aNum = 0; aNum < 8; aNum++)
  {
    // Turn "on" the anode (+) wire.
    digitalWrite(ANODE_PINS[aNum], LOW);
    
    for (byte cNum = 0; cNum < 8; cNum++)
    {
      // Turn "on" the cathode (-) wire.
      digitalWrite(CATHODE_PINS[cNum], LOW);
     
      // Wait one second.
      delay(1000);
      
      // Turn "off" the cathode (-) wire
      digitalWrite(CATHODE_PINS[cNum], HIGH);
    }
    
    // Turn "off" the anode (+) wire
    digitalWrite(ANODE_PINS[aNum], HIGH);
  }
}
