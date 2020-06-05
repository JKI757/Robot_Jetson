
/* 
 * File:   Motor.h
 * Author: josh
 *
 * Created on March 11, 2020, 9:30 PM
 */

#pragma once


#define DEBUG

#include "L298N_Jetson.hpp"
#include "Servo.hpp"
#include <memory>
#include <iostream>
#include <string>
#include "JetsonGPIO.h"

#include "definitions.h"


    typedef enum {FORWARD, BACKWARD, STOP} Direction;
    typedef enum {DRIVE, TURNLEFT, TURNRIGHT, CHANGEDIRECTION, BRAKE } Command;

class Motor {
public:
    Motor(
    int DrivePWMPin, 
    int DriveIn1Pin, 
    int DriveIn2Pin, 
    int SteeringPWMPin);
    
    Motor(
        int DrivePWMPin, 
        int DriveIn1Pin,
        int DriveIn2Pin, 
        int SteeringPWMPin,
        const unsigned short mapMin,
        const unsigned short mapMax);

    ~Motor();


    short setDriveSpeed(const unsigned short speed);
    void setDirection(Direction d);
    void run();
    void run(Direction d);
    void stop();
    void turnAbsolute(short angle);
    void turnRight(short angle);
    void turnLeft(short angle);

private:
    std::shared_ptr<GPIO::PWM> steer_pwm;
    std::shared_ptr<GPIO::PWM> drive_pwm;
    
    std::unique_ptr<Servo_Jetson> steer;
    std::unique_ptr<L298N_Jetson> drive;
    short currentSpeed;
    Direction currentDirection;
    unsigned short map(const unsigned short val, const unsigned short minInput, const unsigned short maxInput,
                                                    const unsigned short minOutput, const unsigned short maxOutput);


};