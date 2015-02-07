				/*
		Ultrasimple sketch to demonstrate the use of Arduino with 
		openFrameworks.
		
		This sketch is written to be used with the serialExample program 
		that comes with the openFrameworks library. It initializes a serial 
		port with a speed of 9600 baud, then waits for serialExample to send
		a character ('a' by default), then responds with three dollar signs.
		
		To use this sketch with oF, program your Arduino, make sure the 
		Arduino is the only vitual COM device in use, and then build and run
		the serialExample example
		in openFrameworks.
		
		Released under the Creative Commons ShareAlike License 10/2011
*/


const int LED1 = 5;     			// LED PIN 1
const int LED2 = 4;     			// LED PIN 2
const int LED3 = 3;     			// LED PIN 3
const int LED4 = 2;     			// LED PIN 4

const int LEDB =  13;      		// Builtin LED

const int BUTTON1 = 8;     		// BUTTON PIN 1
const int BUTTON2 = 9;     		// BUTTON PIN 2
const int BUTTON3 = 10;     	// BUTTON PIN 3
const int BUTTON4 = 11;     	// BUTTON PIN 4

	int BUTTONSTATE1 = 0;		// BUTTON PRESSED?
	int BUTTONSTATE2 = 0;		// BUTTON PRESSED?
	int BUTTONSTATE3 = 0;		// BUTTON PRESSED?
	int BUTTONSTATE4 = 0;		// BUTTON PRESSED?

	int BUTTONREADING1 = 0;		// BUTTON PRESSED?
	int BUTTONREADING2 = 0;		// BUTTON PRESSED?
	int BUTTONREADING3 = 0;		// BUTTON PRESSED?
	int BUTTONREADING4 = 0;		// BUTTON PRESSED?

	int PREVBUTTONSTATE1 = 0;		// LASTBUTTON PRESSED?
	int PREVBUTTONSTATE2 = 0;		// LASTBUTTON PRESSED?
	int PREVBUTTONSTATE3 = 0;		// LASTBUTTON PRESSED?
	int PREVBUTTONSTATE4 = 0;		// LASTBUTTON PRESSED?

	long time = 0;         // the last time the output pin was toggled
	long debounce = 200;   // the debounce time, increase if the output flickers


void setup() {
	
	// initialize the LED pin as an OUTPUT:
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(LED3, OUTPUT);
	pinMode(LED4, OUTPUT);

	// initialize digital pin 13 as an output.
	pinMode(LEDB, OUTPUT);
	
	// initialize the BUTTON pin as an INPUT:
	pinMode(BUTTON1, INPUT);
	pinMode(BUTTON2, INPUT);
	pinMode(BUTTON3, INPUT);
	pinMode(BUTTON4, INPUT);
	
	// initialize the BUTTON pin with PULLUP Resistor
	digitalWrite(BUTTON1, HIGH); 
	digitalWrite(BUTTON2, HIGH); 
	digitalWrite(BUTTON3, HIGH); 
	digitalWrite(BUTTON4, HIGH); 
	
	// start serial port at 9600 bps:
	Serial.begin(9600);


	// establishContact();
	
}

void loop() {
	 
	char inByte = 0;


	setLED();
	
	// if we get a valid byte, read analog ins:

	if (Serial.available() > 0) {
		// get incoming byte:
		inByte = Serial.read();

		if (inByte > 0) {
		
			digitalWrite(LEDB, HIGH);   // When we send a message, flash the internal LED for debugging
			// delay(100);              	 // Delay the program for awhile so people don't crash everything!!!	
			digitalWrite(LEDB, LOW);    // Resume

		}

	}

}

void setLED() {
	
	// read the state of the pushbutton value:
	BUTTONREADING1 = digitalRead(BUTTON1);
	BUTTONREADING2 = digitalRead(BUTTON2);
	BUTTONREADING3 = digitalRead(BUTTON3);
	BUTTONREADING4 = digitalRead(BUTTON4);

	// Check the BUTTON status
	// (BUTTONSTATE1 == HIGH) ? digitalWrite(LED1, HIGH) : digitalWrite(LED1, LOW);
	// (BUTTONSTATE2 == HIGH) ? digitalWrite(LED2, HIGH) : digitalWrite(LED2, LOW);
	// (BUTTONSTATE3 == LOW) ? digitalWrite(LED3, HIGH) : digitalWrite(LED3, LOW);
	// (BUTTONSTATE4 == LOW) ? digitalWrite(LED4, HIGH) : digitalWrite(LED4, LOW);

	if (BUTTONREADING1 == HIGH) {

		BUTTONSTATE1 = 1;
		BUTTONSTATE2 = 0;
		BUTTONSTATE3 = 0;
		BUTTONSTATE4 = 0;

		// Send message
		Serial.print("T");
		delay(200);
		// Serial.print("T");
		// Serial.print("T");

	}

	if (BUTTONREADING2 == HIGH) {

		BUTTONSTATE1 = 0;
		BUTTONSTATE2 = 1;
		BUTTONSTATE3 = 0;
		BUTTONSTATE4 = 0;

		// Send message
		Serial.print("J");
		delay(200);
		// Serial.print("J");
		// Serial.print("J");


	}

	if (BUTTONREADING3 == LOW) {

		BUTTONSTATE1 = 0;
		BUTTONSTATE2 = 0;
		BUTTONSTATE3 = 1;
		BUTTONSTATE4 = 0;

		// Send message
		Serial.print("M");
		delay(200);
		// Serial.print("M");
		// Serial.print("M");


	}

	if (BUTTONREADING4 == LOW) {

		BUTTONSTATE1 = 0;
		BUTTONSTATE2 = 0;
		BUTTONSTATE3 = 0;
		BUTTONSTATE4 = 1;

		// Send message
		Serial.print("W");
		delay(200);
		// Serial.print("W");
		// Serial.print("W");


	}

	// Turn on the LEDs
	digitalWrite(LED1, BUTTONSTATE1);
	digitalWrite(LED2, BUTTONSTATE2);
	digitalWrite(LED3, BUTTONSTATE3);
	digitalWrite(LED4, BUTTONSTATE4);

}

void establishContact() {
  while (Serial.available() <= 0) {
	Serial.print('A');   // send a capital A
	delay(300);
  }
}



