/*
 * MIT License
 */

/* 
 * File:   Servo.hpp
 * Author: josh - JKI757
 *
 * Created on May 24, 2020, 12:21 AM
 */

#pragma once 

#include <JetsonGPIO.h>
#include <memory>
#include <cmath>
#include <iostream>
#include <string>
class Servo_Jetson {
public:
    Servo_Jetson();
    Servo_Jetson(const Servo_Jetson& orig);
    virtual ~Servo_Jetson();
    
    Servo_Jetson(int pin);
    Servo_Jetson(std::shared_ptr<GPIO::PWM> steer, bool setup);
    Servo_Jetson(int pin, const unsigned short minUs, const unsigned short maxUs);
    Servo_Jetson(int pin, const unsigned short minUs, const unsigned short maxUs, const unsigned short mapMin, const unsigned short mapMax);
    Servo_Jetson(std::shared_ptr<GPIO::PWM> steer, const unsigned short minUs, const unsigned short maxUs, const unsigned short mapMin, const unsigned short mapMax, bool setup);
    unsigned short mapAngle(const short val);
    void writeAngle(const unsigned short angle);
    void writeUs(const unsigned short microseconds);
    void writeMappedValue(const short val);


private:
    int pin; 
    unsigned short angle;
    unsigned short microseconds;
    unsigned short minUs;
    unsigned short maxUs;
    short mapMin;
    short mapMax;
    std::shared_ptr<GPIO::PWM> Steer_PWM;
    unsigned short map(const short val);
    bool setup;

};


