/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   L298N.hpp
 * Author: josh
 *
 * Created on May 1, 2020, 11:25 PM
 */

#ifndef L298N_HPP
#define L298N_HPP
#include "JetsonGPIO.h"

class L298N{
public:
    typedef enum {FORWARD, BACKWARD, BRAKE} Direction;
    
    L298N()=default;
    
    void init(unsigned char pinEna, unsigned char pinIn1, unsigned char pinIn2){
        this->pinEna = pinEna;
        this->pinIn1 = pinIn1;
        this->pinIn2 = pinIn2;
        	GPIO::setmode(GPIO::BOARD);
	GPIO::setup(pinEna, GPIO::OUT, GPIO::HIGH);
	p = std::make_shared<GPIO::PWM>(pinEna, 100);
        GPIO::setup(pinIn1, GPIO::OUT,GPIO::LOW);
        GPIO::setup(pinIn2, GPIO::OUT,GPIO::LOW);
        
    }
    void run(){
        switch (currentDirection){
            case FORWARD:{
                GPIO::output(pinIn1, GPIO::HIGH);
                GPIO::output(pinIn2, GPIO::LOW);

                ;}break;
            case BACKWARD:{
                GPIO::output(pinIn1, GPIO::LOW);
                GPIO::output(pinIn2, GPIO::HIGH);

                ;}break;
            case BRAKE:{
                GPIO::output(pinIn1, GPIO::LOW);
                GPIO::output(pinIn2, GPIO::LOW);
            ;}break;
            default:;
        }
        p->ChangeDutyCycle(currentSpeed);
        p->start(currentSpeed);
    }
    void brake(){
        
    }
    void setDirection(Direction d){
        currentDirection=d;
    }
    void setSpeed(unsigned char s){
        currentSpeed = s;
    }
    
    ~L298N() {
        	p->stop();
	GPIO::cleanup();
    };
    
private:
    unsigned char pinEna;
    unsigned char pinIn1;
    unsigned char pinIn2;
    bool isMoving;
    Direction currentDirection;
    unsigned char currentSpeed;
    std::shared_ptr<GPIO::PWM> p;
};


#endif /* L298N_HPP */

