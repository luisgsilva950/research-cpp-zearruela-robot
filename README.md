# Ze Arruela - Robot with DC Motors and Ultrasonic Sensor

![Ze Arruela](robot_image.png)

Welcome to the Ze Arruela repository! Ze Arruela is a robot equipped with DC motors and an ultrasonic sensor. This repository contains the code and documentation for controlling Ze Arruela's movements and interacting with the environment using the ultrasonic sensor.

## Features

- Control the movements of Ze Arruela using DC motors.
- Measure distances using the ultrasonic sensor.
- Perform various actions based on the detected distances.
- Customize and extend the functionality to suit your specific needs.

## Hardware Requirements

To use the code in this repository, you will need the following hardware components:

- Arduino board (e.g., Arduino Uno)
- DC motors (quantity and specifications may vary depending on your robot)
- HCSR04 ultrasonic sensor
- Motor driver circuitry (e.g., L298N or similar)

## Getting Started

1. Clone this repository to your local machine or download the code as a ZIP file.
2. Connect the hardware components according to your specific setup.
3. Open the Arduino IDE (Integrated Development Environment) on your computer.
4. Connect the Arduino board to your computer using a USB cable.
5. Open the main Arduino sketch file (`Ze_Arruela.ino`) from the downloaded repository in the Arduino IDE.
6. Verify and upload the sketch to the Arduino board.
7. Monitor the serial output for debug messages and sensor readings.

## Usage

Once you have uploaded the code to your Arduino board, you can interact with Ze Arruela as follows:

1. Power up the robot and ensure the Arduino is properly connected.
2. Observe the startup initialization in the serial monitor.
3. Ze Arruela will be in the "WAITING" state, ready for commands.
4. Use appropriate commands to control the robot's movements and interact with the ultrasonic sensor.
5. Monitor the serial output for feedback, sensor readings, and debug messages.
6. Modify the code to add custom behaviors and actions based on the sensor readings.

## Documentation

Detailed documentation and explanations of the code can be found in the following files:

- `Ze_Arruela.ino`: The main Arduino sketch file containing the robot control logic.
- `DCMotor.h` and `DCMotor.cpp`: Class definition and implementation for the DC motor control.
- `HCSR04.h` and `HCSR04.cpp`: Class definition and implementation for the ultrasonic sensor.

## Contributing

Contributions to enhance the functionality, fix issues, or add new features to Ze Arruela are welcome! If you find any bugs or have ideas for improvements, please open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).

