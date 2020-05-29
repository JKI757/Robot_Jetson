/*
 * MIT License
 */

/* 
 * File:   L298N_Jetson.cpp
 * Author: josh
 * 
 * Created on May 23, 2020, 12:58 AM
 */

#include "L298N_Jetson.hpp"

L298N_Jetson::L298N_Jetson() = default;

L298N_Jetson::~L298N_Jetson() {
    
    this->Drive_PWM->stop();
    if (this->setup){
        GPIO::cleanup();
    }
};

L298N_Jetson::L298N_Jetson(int EnablePin,
        int IN1, int IN2) {
    this->Enable = EnablePin;
    this->IN1 = IN1;
    this->IN2 = IN2;
    this->pwmVal = 0;
    GPIO::setmode(GPIO::BOARD);
    GPIO::setup(this->IN1, GPIO::OUT,GPIO::LOW);
    GPIO::setup(this->IN2, GPIO::OUT,GPIO::LOW);
    GPIO::setup(this->Enable, GPIO::OUT, GPIO::HIGH);
    this->Drive_PWM = std::make_shared<GPIO::PWM>(this->Enable, 50);
    this->setup = true;
    // approximately 50hz is the correct frequency for the L298N board
}

L298N_Jetson::L298N_Jetson(int pinIN1, int pinIN2) {
    this->IN1 = IN1;
    this->IN2 = IN2;
    this->pwmVal = 0;
    GPIO::setmode(GPIO::BOARD);
    GPIO::setup(this->IN1, GPIO::OUT,GPIO::LOW);
    GPIO::setup(this->IN2, GPIO::OUT,GPIO::LOW);
    this->setup = true;

}

L298N_Jetson::L298N_Jetson(std::shared_ptr<GPIO::PWM> drive, int IN1, int IN2, bool setup){
    this->Drive_PWM = drive;
    this->IN1 = IN1;
    this->IN2 = IN2;
    this->pwmVal = 0;
    GPIO::setup(this->IN1, GPIO::OUT,GPIO::LOW);
    GPIO::setup(this->IN2, GPIO::OUT,GPIO::LOW);
    this->setup = false; // this tells the object we didn't create the PWM object and thus can't destroy it or stop PWM
                        // The argument doesn't matter, we have to have another argument so the override doesn't collide with
                        // the other constructor
}

void L298N_Jetson::setSpeed(const unsigned char  pwmVal){
    this->pwmVal = pwmVal;
}
const unsigned char L298N_Jetson::getSpeed(){
    return pwmVal;
}
void L298N_Jetson::forward(){
        GPIO::output(this->IN1, GPIO::HIGH);
        GPIO::output(this->IN2, GPIO::LOW);
        run();
}
void L298N_Jetson::backward(){
        GPIO::output(this->IN1, GPIO::LOW);
        GPIO::output(this->IN2, GPIO::HIGH);
        run();
}
void L298N_Jetson::run(){
    //this->Drive_PWM->ChangeDutyCycle( (this->pwmVal) / 255.0 );
    this->Drive_PWM->start((this->pwmVal) );
    //important -- you need to send in values from [0, 100].  These are a percentage
    //a percentage for the GPIO library
}
void L298N_Jetson::stop(){
        GPIO::output(this->IN1, GPIO::LOW);
        GPIO::output(this->IN2, GPIO::LOW);
        this->Drive_PWM->stop();
}
