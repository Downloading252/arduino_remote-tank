# arduino_remote-tank
This project was a school project of mine. this project utilizes the simple to work with Arduino family, Uno and Mega2560 to be exact together with RF communication using the HC-12 modules.
The cancept of the project was a tank capabale of auto brake when getting to close to an object, as to be an example of a breaking system capable of preventing accidents.
The tank was originaly designed to look as if it was made out of plates, with the vision being the finale product looking lie a steampunk machine.

The tank itself is made out of 3 parts:
1. The lower part - the wheels:  The tank has 6 wheels, out of them only the two midlle ones are motorized. The body uses two 28-BYJ stepper motors with their respective motor drivers, an Arduino Mega2560, an HC-SR04 ultrasonic sensor and an HC-12 module operating at   437.4MHz. The Arduino Mega was chosen because of it's additional GPIO pins, as each notor driver requires 4 pins to operate, together with the ultrasonic sensor and the HC-12 module the amount of GPIO pins in a regular arduino wasn't enough. The motors enabled the tank to move forward and backwards, together with turning left and right.
2. The upper part - the head: 
3. The controller: An Arduino Uno paired with two joysticks - one for the body and one for the head, a button and two HC-12 modules each communicating on a different frequency.

by Nik252
