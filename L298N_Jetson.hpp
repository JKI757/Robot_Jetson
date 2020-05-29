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

class L298N_Jetson {
public:
    
    L298N_Jetson();
    
    ~L298N_Jetson();
  
   L298N_Jetson(int EnablePin, 
   int IN1, int IN2);
   L298N_Jetson(int IN1, int IN2);
   L298N_Jetson(std::shared_ptr<GPIO::PWM> drive, int IN1, int IN2, bool setup);
   void setSpeed(const unsigned char pwmVal);
   const unsigned char getSpeed();
   void forward();
   void backward();
   void run();
   void stop();
   void reset();

private:
   int Enable;
   int IN1;
   int IN2;
   unsigned char pwmVal;

   std::shared_ptr<GPIO::PWM> Drive_PWM;
   
   bool setup; //controls whether or not we control the PWM object.  False if we don't.

};


