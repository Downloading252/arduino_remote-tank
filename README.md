# arduino_remote-tank
This project was a school project of mine. this project utilizes the simple to work with Arduino family, Uno and Mega2560 to be exact together with RF communication using the HC-12 modules.   
The concept of the project was a tank capabale of auto brake when getting to close to an object, as to be an example of a breaking system capable of preventing accidents.   
The tank was originaly designed to look as if it was made out of plates, with the vision being the finale product looking lie a steampunk machine.

The tank itself is made out of 3 parts:
1. The lower part - **The Wheels**:
   * **Movement**: 6 plastic wheels, out of them only the two middle ones are motorized by 2 28BYJ-48 stepper motors with a ULM2003 motor driver each.
   * **Auto braking**: An HC-SR04 ultrasonic sensor.
   * **Communication**: An HC-12 RF transreceiver module communicating at 437.4MHz.
   * **Microcontroller**: Arduino Mega2560.
   * **Power Supple**: A 9v battery connected directly to the Arduino.
     
    The Arduino Mega was chosen because of it's additional GPIO pins, as each notor driver requires 4 pins to operate, together with the ultrasonic sensor and the HC-12 module the amount of GPIO pins in a regular arduino wasn't enough.  
    The 9v Battery powers the Arduino which power the motos and the drivers.
   
   
3. The Upper Part - **The Turret**:
   * **Rotation**: A 28BYJ-48 stepper motor with a ULM2003 driver for 360 degrees rotational movement.
   * **Elevation**: Am MG90S servo motor fot vertical aiminig.
   * **Shooting**: Flywheel system using 4x DC motors to launch plastic cylinders.
   * **Communication**: An HC-12 RF transreceiver module communicating at 433.4MHz.
   * **Microcontroller**: Arduino Uno.
   * **Power Supply**: 3 3.7v Li-Ion 18650 Batteries for a total of 11.1v.
   * **Power Regulation**: 2 12v to 5V DC-DC buck down converters each capable of withstanding up to 3Amp.
     
    The Arduino requires 7-12v, therefore it was connected directly to the battery house providing 11.1v.   
    The DC motor are built for up to 5v and under maximum load can comsume up to 1.5Amp, as a safety measure I used the two DC-DC converters in parallel so together they could provide 6A, enough for all the motors at all times.
  

4. The controller: An Arduino Uno paired with two joysticks - one for the body and one for the head, a button and two HC-12 modules each communicating on a different frequency.

by Nik252
