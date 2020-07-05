# Smart-Clock-Arduino-Project

## Problem Statement 
Most clocks only function as an alarm and are configured to only display time. 
To overcome this lack of information on display we have come up with a clock that displays not only the day and date but also the current temperature along with the percentage of humidity.

## Introduction
A weather clock is a simple modification to our much used clock which only gives us limited information. We have combined an RTC and DHT sensor with an LCD sheild to create our project which displays weather information along with the date and time. Even after the Arduino is powered off the time sensor keeps track of the time using it's built in battery.

## Required Components
* **Keypad Shield:** It Fixes on top of the Arduino Board and is used to display the information. The buttons attached to the shield is used for configure the clock.
  * **Pin Connections:** Mounted on top of the Arduino Board
* **DHT11 Module:** A Temperature and Humidity Module to provide info on the surrounding weather conditions. 
  * **Pin Connections:**
    * GND -> GND
    * VCC -> 3V
    * DATA -> D2

* **RTC DS3231:** It is a Real Time Clock which is used to maintain the time even when the power supply if off.
  * **Pin Connections:**
    * GND -> GND
    * VCC -> 5V
    * SDA -> A4
    * SCL -> A5

## Project Explanation
* This Project uses three components to work together collectively to provide useful information to the user.
* The RTC DS3231 it a Real Time Clock which has an battery attached to it so that it can keep track of the time even when the Arduino is powered off.
* The RTC module initially takes an input data to configure itself, and then it continues keeping time till its battery is drained.
* The DHT11 Module has a temperature and humidity sensor which measures the surrounding weather conditions and returns it in Real Time.
* The Keypad constantly reads the data passed back by the two modules and displays them on the LCD output screen.
* The Keypad has a few buttons which are used to configure the clock manually
  * **Left:** Change Date and Time
  * **Up:** Increase Counter
  * **Right:** Next Selection
* All these components working together makes a very useful weather clock.

## Application 
Everyone owns a smart device which they use for their daily activities, but it isn’t considered healthy to use your phone within an hour of waking up for the following reasons:
  * It increases stress and anxiety due to all messages, emails, etc.
Your time and attention is taken over by some unimportant things which cloud your thinking for the rest of the day.
  * It gets you prone to distraction for the rest of the day
Using the weather-clock can help you in going about your morning routine distraction free and won’t be a time and attention hog. It will provide only the necessary information required like time, weather conditions, and any other updates you wish to add. This is very versatile as you can add and remove features according to your need.

## Team Details
**Contributors:** 
* Afzal Mukhtar
* Hritika Rahul Mehta
