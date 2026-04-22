// include for servo motor control
#include <Servo.h>

const int _portBaud = 9600; // baud rate of the serial port
const float _fps = 10.0; // frame rate to send data
int _max_value = 1023;
int _min_value = 0;


// pin (PWM) where servo motor is connected to
const int _servoPinPWM = 9;

// create a servo object to control a servo motor
Servo servoMotor;

const int PIN = A0;
const float V_ref = 5.0;
const float V_zero = 2.500;       // V at 0 g (after potentiometer zeroing)
const float sensitivity = 0.001101; // V/g

void setup() {
  Serial.begin(9600);

  // attach servo motor to PWM pin
  servoMotor.attach(_servoPinPWM); 
}

void loop() {
	// initialzes the timer
	unsigned long startTime = micros();
  
  int raw = analogRead(PIN);
  float voltage = (float) (raw) * V_ref / 1023.0;
  float mass_g  = (voltage - V_zero) / sensitivity;
	float servoAngle = (V_ref-voltage) * 180.0/5.0;
  
  Serial.print("Voltage:");
  Serial.print(voltage);
  Serial.print(",mass:");
  Serial.print(mass_g);
  Serial.print(",servoAngle:");
  Serial.println(servoAngle);

  
	

  servoMotor.write(servoAngle);
	
        
	// estimates the loop duration and waits before starting a new loop
	unsigned long currentTime = micros(); // in microseconds
	unsigned long elapsedTime = currentTime - startTime; // in microseconds
	unsigned long waitingTime = 1000000/_fps - elapsedTime; // in microseconds

	if (waitingTime < 16384) //(see https://www.arduino.cc/reference/en/language/functions/time/delaymicroseconds/)
		delayMicroseconds(waitingTime); // in microseconds
	else
		delay(waitingTime / 1000); // in milliseconds 
}