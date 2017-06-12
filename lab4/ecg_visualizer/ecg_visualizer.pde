/*
 * Processing code to take ASCII-encoded strings from the serial port at 9600
 * baud and graph them. It expects values in the range 0 to 1023, followed by
 * a newline, or newline and carriage return.
 *
 * Based on public domain code available at http://arduino.cc/en/Tutorial/Graph
 *
 * ENGR 40M, Spring 2015
 */

import processing.serial.*;
import java.util.*;

// TODO replace this with the appropriate serial port index. You can run this
// code with SERIAL_PORT = -1 to get a list of available serial ports.
static final int SERIAL_PORT = 6;

Serial myPort;        // The serial port
int xPos = 1;         // Horizontal position of the graph
float heightOld = 0;  // The old vertical position so I can draw a line
float outHeight;
boolean newVal = false;

void setup () {
  // Set the window size
  // TODO: Adjust this to fit your computer screen
  size(1000, 800);

  if (SERIAL_PORT == -1) {
    println("Please set SERIAL_PORT to an appropriate value in the code.");
    println("Remember that arrays are zero-indexed (so if you want the first item listed below, set SERIAL_PORT to 0).");
    println(Serial.list());
    return;
  }

  myPort = new Serial(this, Serial.list()[SERIAL_PORT], 9600);
  // Don't generate a serialEvent() unless you get a newline character
  myPort.bufferUntil('\n');
  // Set inital background
  background(0);
}

void draw () {
  if (newVal) {
    // Draw the line - the numbers specify the RGB color, pick one you like.
    // Remember that processing draws things upside down.  0 is the top of the window
    
    //erase the next position to be written
    stroke(0);
    line(xPos, (int) height, xPos, 0);
    
    stroke(255);
    line(xPos-1, (int) height-1 -heightOld, xPos, (int) height-1 -outHeight);
    heightOld = outHeight;
    
    // If at the edge of the screen, go back to the beginning
    if (xPos >= width) {
      xPos = 1;      // Not zero, since I the line starts at x-1
      background(0); // Clear the screen with black
    }
    else {
      xPos++;
    }
    newVal = false;
  }
}

void serialEvent (Serial myPort) {
  // Get the ASCII string
  String inString = myPort.readStringUntil('\n');

  if (inString != null) {
    // Trim off any whitespace
    inString = trim(inString);
    float inByte = float(inString);
    float output = filter(inByte);
    if (output == -1 || output != output) return;

    // Map to the screen height (map() performs a linear map, in this case
    // from 0-1023 to 0-height).
    outHeight = map(output, 0, 1024, 0, height);
    
    newVal = true;
  }
}

float filter(float input) {
  // TODO: do some actual filtering here
  // Every time this function is called, a new sample is provided, and this function
  // should return a smoothed value (or -1 if not enough samples exist yet).

  // You'll probably need to keep track of some of the old values.
  // Processing uses Java, so you can use arrays, queues, etc.

  // For now, don't do anything; just return the input
  return input;
}