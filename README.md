# arduino_remote-tank
This project was a school project of mine. this project utilizes the simple to work with Arduino family, Uno and Mega2560 to be exact together with RF communication using the HC-12 modules.   
The concept of the project was a tank capabale of auto brake when getting to close to an object, as to be an example of a breaking system capable of preventing accidents.   
The tank was originaly designed to look as if it was made out of plates, with the vision being the finale product looking lie a steampunk machine.

The tank itself is made out of 3 parts:
1. The lower part - the wheels:
   * **Movement**: 6 plastic wheels, out of them only the two middle ones are motorized by 2 28BYJ-48 stepper motors with a ULM2003 motor driver each.
   * **Auto braking**: An HC-SR04 ultrasonic sensor.
   * **Communication**: An HC-12 RF transreceiver module communicating at 437.4MHz.
   * **Microcontroller**: Arduino Mega2560.
   
   The Arduino Mega was chosen because of it's additional GPIO pins, as each notor driver requires 4 pins to operate, together with the ultrasonic sensor and the HC-12 module the amount of GPIO pins in a regular arduino wasn't enough. 
   
  
3. The upper part - the turret: The head of the tank is made of an HC-12 module communicating on 433.4MHz, one 28BYJ-48 stepper motor with it's corresponding driver, one MG90S servo motor and four regular 5V DC motors togther with adequate power regulation and supply which I will explain more on later. The stepper motor is used to rotate the intire head on its axis while the servo aim the turret itself up and down. When the HC-12 module receives a certain signal, the four DC motors start to spin in sequence letting the two farther motors (relative to the middle of the tank) to build up rotational speed before the two closer motors push the ammo (a plastic cylinder) to them. At this point the friction between the farther motor's wheels and the ammo send the ammo flying forward.
4. The controller: An Arduino Uno paired with two joysticks - one for the body and one for the head, a button and two HC-12 modules each communicating on a different frequency.

by Nik252
