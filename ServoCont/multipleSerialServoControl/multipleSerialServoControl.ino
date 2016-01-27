/*
 * ------------------------------
 *   MultipleSerialServoControl
 * ------------------------------
 *
 * Uses the Arduino Serial library
 *  (http://arduino.cc/en/Reference/Serial)
 * and the Arduino Servo library
 *  (http://arduino.cc/en/Reference/Servo)
 * to control multiple servos from a PC using a USB cable.
 *
 * Dependencies:
 *   Arduino 0017 or higher
 *     (http://www.arduino.cc/en/Main/Software)
 *   Python servo.py module
 *     (http://principialabs.com/arduino-python-4-axis-servo-control/)
 *
 * Created:  23 December 2009
 * Author:   Brian D. Wendt
 *   (http://principialabs.com/)
 * Version:  1.1
 * License:  GPLv3
 *   (http://www.fsf.org/licensing/)
 *
 */

// Import the Arduino Servo library
#include <Servo.h> 

// Create a Servo object for each servo
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

// TO ADD SERVOS:
//   Servo servo5;
//   etc...

// Common servo setup values
int minPulse = 600;   // minimum servo position, us (microseconds)
int maxPulse = 2400;  // maximum servo position, us

// User input for servo and position
int userInput[4];    // raw input from serial buffer, 4 bytes
int startbyte;       // start byte, begin reading input
int servo;           // which servo to pulse?
int pos;             // servo angle 0-180
int i;               // iterator

// LED on Pin 13 for digital on/off demo
int ledPin = 13;
int pinState = LOW;

void setup() 
{ 
  // Attach each Servo object to a digital pin
  servo1.attach(9, minPulse, maxPulse);
  servo2.attach(3, minPulse, maxPulse);
  servo3.attach(4, minPulse, maxPulse);
  servo4.attach(5, minPulse, maxPulse);
  servo5.attach(10, minPulse, maxPulse);
  servo6.attach(11, minPulse, maxPulse);
  // TO ADD SERVOS:
  //   servo5.attach(YOUR_PIN, minPulse, maxPulse);
  //   etc...

  // LED on Pin 13 for digital on/off demo
  pinMode(ledPin, OUTPUT);

  // Open the serial connection, 9600 baud
  Serial.begin(9600);
} 

void loop() 
// Serial input is of the format s<motor #>a<angle> e.g
//s1a45
//s2a180
{ 
  // Wait for serial input (min 3 bytes in buffer)
  if (Serial.available()>0) {
    // Read the first byte
    startbyte = Serial.read();
    if (startbyte == 's') {
      Serial.println("Received");
      servo = Serial.parseInt();
      Serial.print("Servo is: ");
      Serial.println(String(servo));
      Serial.read(); //separating character b/w servo and angle
      pos = Serial.parseInt();
      Serial.print("Angle is: ");
      Serial.println(String(pos));
      // Assign new position to appropriate servo
      
      switch (servo) {
        case 1:
          servo1.write(pos);    // move servo1 to 'pos'
          break;
        case 2:
          servo2.write(pos);
          break;
        case 3:
          servo3.write(pos);
          break;
        case 4:
          servo4.write(pos);
          break;
        case 5:
          servo5.write(pos);
          break;
        case 6:
          servo6.write(pos);
          break;
      }

   // TO ADD SERVOS:
   //     case 5:
   //       servo5.write(pos);
   //       break;
   // etc...
    }
    else if (startbyte == 'q') {
        Serial.println("Ending serial.");
        Serial.end();
    }
  }
}

