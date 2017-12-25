#include <LowPower.h> // Lightweight low power library for Arduino.

/* Arduino UNO
 *  Project: Plant moisture checker
 *  Description: Uses a soil humidity sensor to indicate when a plan needs water.
 *               LED blinks to indicate soil humidity (Red below 30%, Yellow between 30% and 70%, Green above 70%): 
 *               
 *  Components:
 *              - Arudino UNO board
 *              - Soil Moisture Sensor
 *              - 9V Battery and connecter for arduino board
 *              - RGB LED 
 */

// Global Variables
int sensor_pin = A0;  // Soil Moisture sensor
int output_value ;    // Sensor Output Value - Used to calculate humidity %
int redpin = 8;       // pin for the red LED
int bluepin = 10;     // pin for the blue LED
int greenpin = 9 ;    // pin for the green LED

void setup() {
  // Initialize setup 
  pinMode (redpin, OUTPUT);
  pinMode (bluepin, OUTPUT);
  pinMode (greenpin, OUTPUT);
  pinMode (LED_BUILTIN, OUTPUT);
  digitalWrite (LED_BUILTIN, LOW);
  
  /*Uncomment for debug only*/
  /*
  Serial.begin(9600);
  Serial.println("Reading From the Sensor ...");
  delay(2000);
  */
  }

void loop() {
  output_value= analogRead(sensor_pin);             // read humidity sensor value
  output_value = map(output_value,1100,400,0,100);  // map humidity value to %

  /* uncomment for debug only
  Serial.print("Mositure : ");
  Serial.print(output_value);
  Serial.println("%");
  delay(1000);
  */
  if (output_value < 30) {
    analogWrite (redpin, 150);
    analogWrite (greenpin, 0);
    analogWrite (bluepin, 0);
  }
  if (output_value > 29 && output_value < 70) {
    analogWrite (redpin, 150);
    analogWrite (greenpin, 150);
    analogWrite (bluepin, 0);
  }
  if (output_value > 69) {
    analogWrite (redpin, 0);
    analogWrite (greenpin, 150);
    analogWrite (bluepin, 0);
  }
  delay(200); 
  
  // turn off LED
  analogWrite (redpin, 0);
  analogWrite (greenpin, 0);
  analogWrite (bluepin, 0); 

  // Sleep for 8s - ATmega328P, ATmega168
  LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);
    
}
