# Smart-Wheelchair-Using-AI-powered-Eye-Tracking-for-Quadriplegic-People
Regain Independence, Blink by Blink. This project delivers a revolutionary AI-powered smart wheelchair that grants complete mobility back to individuals with quadriplegia. We replace joysticks with a hands-free, real-time eye-tracking interface, achieving a 95.4% command accuracy for movement control.

AI-powered smart wheelchair system to restore independent mobility for individuals with quadriplegia. It replaces traditional manual controls with a highly intuitive, hands-free interface powered entirely by the user's real-time eye movements.


The system integrates three core, synergistic functions: AI-driven navigation, ultrasonic safety protocols, and a continuous IoT health monitoring dashboard.


 Software Stack & AI System
The intelligence of the wheelchair is driven by a sophisticated computer vision pipeline and robust cloud services:

1. AI-Powered Navigation Control

Core Libraries: The system uses Python in conjunction with open-source software like OpenCV and Dlib for precise eyeball tracking and image processing.






Detection Algorithm: It leverages the Dlib facial landmarks detector to find the exact eye position coordinates. Techniques like 

Gaussian blurring and grayscale conversion preprocess the images for accurate pupil detection.


Command Interpretation: The Hough Circle Transform and Canny edge detection track pupil movements in real-time. Simple, sequential eye gestures (e.g., up, up, up) are converted into movement instructions (Forward, Backward, Left, Right, Stop).



2. IoT Cloud Implementation

Database: Firebase Realtime Database is used as the Internet of Things (IoT) platform for reliable and efficient data handling.






Data Logging: The database stores and logs continuous vital health metrics (heart rate, temperature), providing real-time access to medical staff and caregivers via a connected mobile application.



 Hardware Components & Safety Systems
1. Embedded Control & Communication

Main Microcontroller: The Arduino UNO acts as the primary processing component, translating the wireless input signals into actions.





Wireless Module: An ESP8266 Wi-Fi module handles time-sensitive wireless data transfer between the computer vision system and the Arduino microcontroller, providing reliable and uninterrupted control over the wheelchair.





Actuation: Motor drivers regulate the direction and speed of the stepper motors using Pulse Width Modulation (PWM) signals, executing the precise movement commands from the Arduino.




2. Sensory and Safety Modules

Obstacle Avoidance: Ultrasonic sensors are mounted on the wheelchair frame to continuously scan for nearby safety risks. If an object is detected within a 25cm range, the system automatically triggers a stop operation.






Health Monitoring: Dedicated health sensors, specifically DHT11 sensors (for temperature) and a heart rate detection sensor, perform continuous monitoring of vital signs.



Performance Highlights

Command Accuracy: 95.4% command recognition accuracy for eye gestures.


Response Time: A fast average command-to-action delay of 480 milliseconds.



Safety Reliability: An Obstacle Detection Success Rate of 98%.
