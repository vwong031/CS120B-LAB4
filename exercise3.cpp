/*
* Name & Email: Valerie Wong
* Discussion Section: 021
* Assignment: Lab 4 Exercise 3
* Exercise Description: You will design a system that samples inputs from the potentiometer and photoresistor every 100 ms. 
*                       After each sample, the system will display the photoresistor reading on the 4 LEDs and the potentiometer on the RGB LED
* 
*                       Photoresistor:
*                       * When the photoresistor is covered, none of the LEDs will be lit up
*                       * When you shine light on the photoresistor (e.g., daylight, a light in the room), more LEDs will light up
*                       * When you shine a very strong light on the photoresistor (e.g., the flashlight on a phone), all of the LEDs will light up to indicate maximum brightness.
* 
*                       Potentiometer:
*                       * When the potentiometer is turned all the way down, the RGB LED will be turned off
*                       * As you turn the potentiometer up, the RGB LED will change color, from red, to purple, to white 

* I acknowledge all content contained herein, excluding template 
  or example code, is my own original work.

* Demo Link: https://youtu.be/yznJKb_Kn6w
*/

// The following global variables are used to implement SynchSM
// functionality using the Arduino API. In contrast the zyBook,
// the Arduino API does not provide the programmer with direct
// access to Timer Interrupt functions. 
const unsigned long period = 50; 
unsigned long lastRan = 0;
unsigned int val_photoresistor;
unsigned int val_potentiometer;
unsigned int cpy_potentiometer;

const int b_size = 7;
const int b[b_size] = {2, 3, 4, 5, 9, 10, 11};
unsigned char cnt;

void setup(){

  // Default Arduino Function

    // Initialize LEDs
    for(int i = 0; i < b_size; i++)
    {
        pinMode(b[i], OUTPUT);
    }
    Serial.begin(9600);
    lastRan = 0;
}

enum States{INIT, SAMPLE, UPDATE_DISPLAY} state = INIT;

void lightLEDs(int val) {
  for (int i = 3; i >= val; --i) {
    digitalWrite(b[i], HIGH);
  }
}

// Turn off LEDs based on potentiometer reading
void turnOFF(int val) {
  for (int i = 0; i < val; ++i) {
    digitalWrite(b[i], LOW);
  }
}

void rgb_on(int val, int cpy) {
  if (val == 0) {
    rgb_off(); 
  }
  
  if (val > 0 && val <= 254) {
    analogWrite(b[4], cpy);
    analogWrite(b[5], 0);
    analogWrite(b[6], 0);
  }
  else if (val >= 255 && val <= 509) {
    analogWrite(b[4], (cpy-255));
    analogWrite(b[5], 0);
    analogWrite(b[6], (cpy-255));
  }
  else {
    analogWrite(b[4], (cpy - (255*2)));
    analogWrite(b[5], (cpy - (255*2)));
    analogWrite(b[6], (cpy - (255*2)));
  }
}

void rgb_off() {
  analogWrite(b[5], 0);
  analogWrite(b[6], 0);
  analogWrite(b[7], 0);
}

void readPotentiometer() {
  val_potentiometer = analogRead(A0);
  
  /*
  RANGES
  0-254
  255-509
  510-764
  */
  
  val_potentiometer = map(val_potentiometer, 0, 1023, 0, 764);
  cpy_potentiometer = val_potentiometer;
}

void readPhotoresistor() {
  // Photoresistor range: 1 - 310
  val_photoresistor = analogRead(A1);
  
  val_photoresistor = map(val_photoresistor, 1, 310, 4, 0);
}

// The Tick() function is similar in principle to zyBooks
// If you find it confusing, draw the corresponding SynchSM
// diagram. 
void Tick(){


    // State Transitions
    switch(state){
      case INIT:    
        state = SAMPLE;
        cnt = 0;
        break;
      
      case SAMPLE:
        state = UPDATE_DISPLAY;
        cnt = 0;
        break;
      
      case UPDATE_DISPLAY:
        if (cnt >= 2) {
          state = SAMPLE;
        }
      
        break;
      
      default: // should never get here
        break;
    }

    // State Actions
    switch(state){ 
      case INIT:
        break;
      
      case SAMPLE:      
        readPhotoresistor();
        readPotentiometer();
        break;
            
      case UPDATE_DISPLAY:
        lightLEDs(val_photoresistor);
        turnOFF(val_photoresistor);
        rgb_on(val_potentiometer, cpy_potentiometer);
      
        ++cnt;
        break;
      
     default: // should never get here
        break;
    }
}

void loop(){ 

   // Default Arduino function
  
  // We track time explicitly in the loop() function,
  // which is different that the Timer Interrupt
  // mechanism introduced in the zyBook
  Tick(); 
}
