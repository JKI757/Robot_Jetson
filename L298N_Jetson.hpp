/*
*  nMIT License
 * 
 *  */


/* 
 * File:   L298N_Jetson.h
 * Author: josh -- JKI757
 *
 * Created on May 23, 2020, 12:58 AM
 */

#pragma once 

#include <JetsonGPIO.h>
#include <memory>
#include <cmath>
#include "definitions.h"
#include <iostream>

class L298N_Jetson {
public:
    
    L298N_Jetson();
    
    ~L298N_Jetson();
  
   L298N_Jetson(const int EnablePin, const int IN1, const int IN2);
   L298N_Jetson(const int IN1, const int IN2);
   L298N_Jetson(std::shared_ptr<GPIO::PWM> drive, const int IN1, const int IN2, 
   const bool setup, const unsigned short minInput, const unsigned short maxInput);
   void setSpeed(const unsigned short pwmVal);
   const unsigned short getSpeed();
   void forward();
   void backward();
   void run();
   void stop();
   void reset();

private:
   int Enable;
   int IN1;
   int IN2;
   unsigned short pwmVal;
   
   const unsigned short maxSpeed = 100;
   const unsigned short minSpeed = 0;
   
   unsigned short minInput;
   unsigned short maxInput;
   std::shared_ptr<GPIO::PWM> Drive_PWM;
   
   bool setup; //controls whether or not we control the PWM object.  False if we don't.
   unsigned short map(const unsigned short val);

};


