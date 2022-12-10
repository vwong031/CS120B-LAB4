# CS120B-LAB4

## Wiring Diagram
![image](https://user-images.githubusercontent.com/74090811/206831883-2e361a18-da89-4a68-ad6a-64de58eaa979.png)

## Exercise 1:
Create a system that lights up the four LEDs as follows:
* The system has a 1 second (1000 ms) period
* Exactly one LED will be lit at all times
* The leftmost LED is lit initially
* After each Tick(), the lit LED moves one position to the right
* When the rightmost LED is lit, the system changes direction
* After each Tick(), the lit LED moves one position to the left
* The cycle repeats indefinitely.

Demo Link: https://youtu.be/-757vtCzmSw

## Exercise 2:
You will enhance the Light Cycle from Exercise #1 by adjusting the speed at which the lit LED changes.

* When initialized, the system behaves exactly the same as in Exercise #1, but with a 500 ms period.
* Use the potentiometer to adjust the speed at which the lit LED changes.
* The fastest speed of the light cycle is to change the lit LED every 100 ms.
* The slowest speed of the light cycle is to change the lit LED every 500 ms.
* You get to determine the period of the system.

Demo Link: https://youtu.be/bv5d_RQ6rWc

## Exercise 3:
You will design a system that samples inputs from the potentiometer and photoresistor every 100 ms. 

After each sample, the system will display the photoresistor reading on the 4 LEDs and the potentiometer on the RGB LED

Photoresistor:
*  When the photoresistor is covered, none of the LEDs will be lit up
*  When you shine light on the photoresistor (e.g., daylight, a light in the room), more LEDs will light up
*  When you shine a very strong light on the photoresistor (e.g., the flashlight on a phone), all of the LEDs will light up to indicate maximum brightness.

Potentiometer:
*  When the potentiometer is turned all the way down, the RGB LED will be turned off
*  As you turn the potentiometer up, the RGB LED will change color, from red, to purple, to white

Demo Link: https://youtu.be/yznJKb_Kn6w
