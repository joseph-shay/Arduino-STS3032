#include <INST.h>      // Include library for control instructions
#include <SCS.h>        // Include library for servo controller support
#include <SCSCL.h>      // Include library for SCS communication layer
#include <SCSerial.h>   // Include library for serial communication with the servo
#include <SCServo.h>    // Include library for servo control functions
#include <SMS_STS.h>    // Include library for STS series servo control

// Define the Servo ID to identify the target servo motor
#define ServoID 1 

// Define the speed variable to control the servo's rotation speed
int speed = 2000; 

// Create an instance of the SMS_STS class to control the STS3032 servo
SMS_STS sts3032; 

void setup() {
  // Initialize serial communication at 1,000,000 baud for faster communication with the servo
  Serial1.begin(1000000);

  // Assign the serial port to the STS3032 servo controller instance
  sts3032.pSerial = &Serial1;

  // Unlock the EEPROM memory of the servo to allow modifications
  sts3032.unLockEprom(ServoID);

  // Enable the torque on the servo (i.e., power it on)
  sts3032.EnableTorque(ServoID, 1);

  // Set the servo to wheel mode, allowing continuous rotation
  sts3032.WheelMode(ServoID);

  // Set the mode to 1 (wheel mode is typically controlled by this value)
  sts3032.writeByte(ServoID, SMS_STS_MODE, 1);

  // Lock the EEPROM memory of the servo to prevent further modifications
  sts3032.LockEprom(ServoID);
}

void loop() {
  // Set the servo to the defined speed (2000) to start rotating in one direction
  sts3032.WriteSpe(ServoID, speed);
  delay(5000);  // Wait for 5 seconds while the servo is rotating

  // Stop the servo by setting its speed to 0
  sts3032.WriteSpe(ServoID, 0);
  delay(2000);  // Wait for 2 seconds with the servo stopped

  // Set the servo to rotate in the opposite direction by using the negative speed value
  sts3032.WriteSpe(ServoID, speed * -1);
  delay(2000);  // Wait for 2 seconds while the servo rotates in the opposite direction

  // Stop the servo again by setting its speed to 0
  sts3032.WriteSpe(ServoID, 0);
  delay(2000);  // Wait for 2 seconds before the next cycle
}
