/*
* Name & Email: Valerie Wong
* Discussion Section: 021
* Assignment: Lab 4 Exercise 2
* Exercise Description: You will enhance the Light Cycle from Exercise #1 by adjusting the speed at which the lit LED changes

* When initialized, the system behaves exactly the same as in Exercise #1, but with a 500 ms period
* Use the potentiometer to adjust the speed at which the lit LED changes
* The fastest speed of the light cycle is to change the lit LED every 100 ms
* The slowest speed of the light cycle is to change the lit LED every 500 ms
* You get to determine the period of the system
* You will receive full credit as long as the system functions properly
* We will discuss trade-offs involving different system periods later in the quarter.

* I acknowledge all content contained herein, excluding template 
  or example code, is my own original work.

* Demo Link: https://youtu.be/bv5d_RQ6rWc
*/

// The following global variables are used to implement SynchSM
// functionality using the Arduino API. In contrast the zyBook,
// the Arduino API does not provide the programmer with direct
// access to Timer Interrupt functions. 
const unsigned long period = 500; 
unsigned long lastRan = 0;

const int b_size = 7;
const int b[b_size] = {2, 3, 4, 5, 9, 10, 11};

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

enum States{INIT, LIGHT_LEFT, LIGHT_RIGHT} state = INIT;

void Timer(int val) {
  unsigned char divisor = 1;
  
  if (val == 2) {
    divisor = 2;
  }
  else if (val == 3) {
    divisor = 5;
  }
  
  while ((millis() - lastRan) < (period / divisor)) {}
  lastRan = millis();
  
  Serial.println(period/divisor);
}

// Control speed of LEDs based on potentiometer reading
void readPotentiometer() {
  int val = analogRead(A0);
  
  // Map to 3 values because there are only 3 speeds
  val = map(val, 0, 1023, 1, 3);
  //Serial.println(val);
  Timer(val);
}

// The Tick() function is similar in principle to zyBooks
// If you find it confusing, draw the corresponding SynchSM
// diagram. 
void Tick(){


    // State Transitions
    switch(state){
      case INIT:    
        state = LIGHT_RIGHT;
        break;
      
      case LIGHT_RIGHT:
        state = LIGHT_LEFT;
        break;
      
      case LIGHT_LEFT:
        state = LIGHT_RIGHT;
        break;
      
      default: // should never get here
        break;
    }

    // State Actions
    switch(state){ 
      case INIT:
        break;
      
      case LIGHT_RIGHT:      
        for (int i = 0; i < 4; ++i) {
          if (i > 0) {
            readPotentiometer();
            digitalWrite(b[i-1], LOW);
          }
          digitalWrite(b[i], HIGH);
        }
      
        break;
            
      case LIGHT_LEFT:
        for (int i = 3; i >= 0; --i) { 
          if (i < 3) {
            readPotentiometer();
            digitalWrite(b[i+1], LOW); 
          }
          
          digitalWrite(b[i], HIGH);
        }
            
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
