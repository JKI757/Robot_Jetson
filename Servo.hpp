/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Servo.hpp
 * Author: josh
 *
 * Created on May 1, 2020, 11:25 PM
 */

#ifndef SERVO_HPP
#define SERVO_HPP
#include "JetsonGPIO.h"

class Servo{
public:
    
    Servo(){};
    void init(unsigned char pin){
        	GPIO::setup(pin, GPIO::OUT, GPIO::HIGH);
	p = std::make_shared<GPIO::PWM>(pin, 50);
        minFreq=1000;
        maxFreq=2000;
    }
    void init(unsigned char pin, int minFreq, int maxFreq){
        GPIO::setup(pin, GPIO::OUT, GPIO::HIGH);
	p = std::make_shared<GPIO::PWM>(pin, 50);
        this->minFreq=minFreq;
        this->maxFreq=maxFreq;

    }
    void write(int microseconds);
    int read();
    
private:
    unsigned char pin;
    int minFreq;
    int maxFreq;
    int centerFreq;
    std::shared_ptr<GPIO::PWM> p;
};


#endif /* SERVO_HPP */

