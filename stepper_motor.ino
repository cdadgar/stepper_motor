/*
 *  DVR8825 stepper motor driver 
 *  see https://www.makerguides.com/drv8825-stepper-motor-driver-arduino-tutorial/
 *  
 *  pinout: (top view, ic at bottom)
 *  ENABLE                  VMOT - motor VCC (8.2 - 45 VDC)
 *  M0                      GND - motor ground
 *  M1                      B2 - stepper winding B
 *  M2                      B1
 *  RESET - cpu VCC         A1 - stepper winding A
 *  SLEEP - cpu VCC         A2
 *  STEP - step             FAULT
 *  DIR - direction         GND - cpu ground
 *  
 *  M0, M1, and M2 are used to set the microstep resolution
 *  if disconnected, it defaults to full step
 *  
 *  FAULT is an output that is set high when the driver detected over current or thermal shutdown
 *  
 *  ENABLE must be low (or disconnected) for the driver to work
 *    if set high, the motor is allowed to spin freely.  (the windings aren't energized)
 *  RESET and SLEEP must be set high for the driver to work
 *  
 *  note: connect a 100 uF capacitor across vmot and gnd
 *  
 *  
 *  IMPORTANT
 *  current limit pot is on the board.  see the above guide on setting it.
 *  current limit = Vref * 2
 *  max current for the stepper motor below is 0.4A
 *  so Vref = 0.4 / 2 = 0.2 V
 *  if the current is set too high, the motor will get hot while it is idle.
 *  if set too low, the motor will miss steps.
 *  set set Vref, hook up motor power, cpu power, but disconnect stepper motor
 *  measure from gnd to the metal part of the pot itself
 *  turn clockwise to lower the voltage.
 *  use T5 red screwdriver with a aligator clip attahced to it so a multimeter
 *  can measure the voltage while turning the pot.
 *  
 *  note: the 4 drivers I have have been adjusted to 0.2 V
 *  
 *  
 *  if the motor speed is set too high, the motor won't move.
 * 
 *  
 *  
 *  stepper motor:
 *  Model: 42HB40F04AB
 *  Flange: NEMA17 (42mm x 42mm) 
 *  0.4 Amps 
 *  Color:Black 
 *  Depth: 39mm
 *  
 *  Nema 17 
 *  Bipolar 
 *  1.8deg 
 *  40Ncm (56.6oz.in) 
 *  0.4A 
 *  12V 
 *  42x42x39mm 
 *  4 Wires
 *  
 * Manufacturer Part Number: 17HS15-0404S
 * Motor Type: Bipolar Stepper
 * Step Angle: 1.8 deg.
 * Holding Torque: 40Ncm(56.6oz.in)
 * Rated Current/phase: 0.4A
 * Phase Resistance: 30.0ohms
 * Inductance: 58mH+/-20%(1KHz)
 * 
 * 4 wires
 * red - green = 35 ohms 
 * yellow - blue = 35 ohms
 */


// Continuous rotation
#include <AccelStepper.h>

// Define stepper motor connections and motor interface type.
// Motor interface type must be set to 1 when using a driver:
#define dirPin             D6
#define stepPin            D5
#define motorInterfaceType 1

// M2 is high, so microstep resolution is 1/16 step
#define microSteps        16

AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);


void setup() {
  Serial.begin(115200);
  Serial.print(F("\n\n stepper motor test\n\n"));

  // Set the maximum speed in steps per second:
  stepper.setMaxSpeed(1000 * microSteps);
}


void loop() {
  // Set the speed in steps per second:
  stepper.setSpeed(400 * microSteps);
  
  // Step the motor with a constant speed as set by setSpeed():
  stepper.runSpeed();
}



/*
// control number of steps or revolutions
#include <AccelStepper.h>

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin             D6
#define stepPin            D5
#define motorInterfaceType 1

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
  // Set the maximum speed in steps per second:
  stepper.setMaxSpeed(1000);
}

void loop() { 
  // Set the current position to 0:
  stepper.setCurrentPosition(0);

  // Run the motor forward at 200 steps/second until the motor reaches 400 steps (2 revolutions):
  while(stepper.currentPosition() != 400)
  {
    stepper.setSpeed(200);
    stepper.runSpeed();
  }

  delay(1000);

  // Reset the position to 0:
  stepper.setCurrentPosition(0);

  // Run the motor backwards at 600 steps/second until the motor reaches -200 steps (1 revolution):
  while(stepper.currentPosition() != -200) 
  {
    stepper.setSpeed(-600);
    stepper.runSpeed();
  }

  delay(1000);

  // Reset the position to 0:
  stepper.setCurrentPosition(0);

  // Run the motor forward at 400 steps/second until the motor reaches 600 steps (3 revolutions):
  while(stepper.currentPosition() != 600)
  {
    stepper.setSpeed(400);
    stepper.runSpeed();
  }

  delay(3000);
}
*/


/*
// Acceleration and deceleration
#include <AccelStepper.h>

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin             D6
#define stepPin            D5
#define motorInterfaceType 1

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
  // Set the maximum speed and acceleration:
  stepper.setMaxSpeed(200);
  stepper.setAcceleration(30);
}

void loop() {
  // Set the target position:
  stepper.moveTo(600);
  // Run to target position with set speed and acceleration/deceleration:
  stepper.runToPosition();

  delay(1000);

  // Move back to zero:
  stepper.moveTo(0);
  stepper.runToPosition();

  delay(1000);
}
*/
