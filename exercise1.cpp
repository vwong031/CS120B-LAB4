/*
* Name & Email: Valerie Wong
* Discussion Section: 021
* Assignment: Lab 4 Exercise 1
* Exercise Description: Create a system that lights up the four LEDs as follows:

                        The system has a 1 second (1000 ms) period
						            Exactly one LED will be lit at all times
						            The leftmost LED is lit initially
						            After each Tick(), the lit LED moves one position to the right
						            When the rightmost LED is lit, the system changes direction
						            After each Tick(), the lit LED moves one position to the left
						            The cycle repeats indefinitely.

* I acknowledge all content contained herein, excluding template 
  or example code, is my own original work.

* Demo Link: https://youtu.be/-757vtCzmSw 
*/

// The following global variables are used to implement SynchSM
// functionality using the Arduino API. In contrast the zyBook,
// the Arduino API does not provide the programmer with direct
// access to Timer Interrupt functions. 
const unsigned long period = 1000; 
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

void Timer() {
  while ((millis() - lastRan) < period) {}
  lastRan = millis();
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
            Timer();
            digitalWrite(b[i-1], LOW);
          }
          digitalWrite(b[i], HIGH);
        }
      
        break;
            
      case LIGHT_LEFT:
        for (int i = 3; i >= 0; --i) {
          if (i < 3) {
            Timer();
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
