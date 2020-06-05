/*
 * MIT License
 */


/* 
 * File:   Servo.cpp
 * Author: josh  - JKI757
 * 
 * Created on May 24, 2020, 12:21 AM
 */

#include "Servo.hpp"
#define DEBUG

Servo_Jetson::Servo_Jetson() = default;

Servo_Jetson::~Servo_Jetson() {
    this->Steer_PWM->stop();
    if (this->setup){
        GPIO::cleanup();
    }

}
 Servo_Jetson::Servo_Jetson(int pin){
    GPIO::setmode(GPIO::BOARD);
    GPIO::setup(pin, GPIO::OUT, GPIO::HIGH);
    this->Steer_PWM = std::make_shared<GPIO::PWM>(pin, 1500);
    //1500 is centered for a normal steering servo for RC car
    this->minUs = 1000;
    this->maxUs = 2000;
    this->setup = true;
}
Servo_Jetson::Servo_Jetson(std::shared_ptr<GPIO::PWM> steer, bool setup){
    this->Steer_PWM = steer;
    this->minUs = 1000;
    this->maxUs = 2000;
    this->minInput = 0;
    this->maxInput = 255;
    this->setup = false;

}

 Servo_Jetson::Servo_Jetson(int pin, const unsigned short minUs, const unsigned short maxUs){
    GPIO::setmode(GPIO::BOARD);
    GPIO::setup(pin, GPIO::OUT, GPIO::HIGH);
    this->Steer_PWM = std::make_shared<GPIO::PWM>(pin, 1500);
    //1500 is centered for a normal steering servo for RC car
    this->minUs = minUs;
    this->maxUs = maxUs;
    this->setup = true;
    
}
Servo_Jetson::Servo_Jetson(int pin, const unsigned short minUs, const unsigned short maxUs, 
                                        const unsigned short minInput, const unsigned short maxInput){
    //mapMin and mapMax are the expected range of values coming in as commands 
    //if you use these values, use the writeMappedValue method with a value in the range (mapMin, mapMax)
    //and the value will be mapped to (minUs, maxUs)
    GPIO::setmode(GPIO::BOARD);
    GPIO::setup(pin, GPIO::OUT, GPIO::HIGH);
    this->Steer_PWM = std::make_shared<GPIO::PWM>(pin, 1500);
    //1500 is centered for a normal steering servo for RC car
    this->minUs = minUs;
    this->maxUs = maxUs;
    this->minInput = minInput;
    this->maxInput = maxInput;
    this->setup = true;

    
}

Servo_Jetson::Servo_Jetson(std::shared_ptr<GPIO::PWM> steer, const unsigned short minUs, const unsigned short maxUs, const unsigned short minInput, const unsigned short maxInput, bool setup){
    //mapMin and mapMax are the expected range of values coming in as commands 
    //if you use these values, use the writeMappedValue method with a value in the range (mapMin, mapMax)
    //and the value will be mapped to (minUs, maxUs)
    this->Steer_PWM = steer;
    //1500 is centered for a normal steering servo for RC car
    this->minUs = minUs;
    this->maxUs = maxUs;
    this->minInput = minInput;
    this->maxInput = maxInput;
    this->setup = false;
}


unsigned short Servo_Jetson::map(const unsigned short val){
        if ((val <= maxInput) && (val >= minInput) && (maxInput != minInput)) {
            return (float)((float)(val - minInput) * (float)(maxUs - minUs) / (float)(maxInput - minInput) + minUs);
        } else return 0;
    }
void Servo_Jetson::writeMappedValue(const short val){
#ifdef DEBUG
        std::cout << "value passed into write mapped value: " << val << std::endl;

#endif 
    //takes a value mapped between minRange and maxRange to minUs and maxUs and calculates a microsecond value from there
    unsigned short mappedVal = map(val);
#ifdef DEBUG
    std::cout << "mapped value: " << mappedVal << std::endl;
#endif 
//    this->Steer_PWM->ChangeFrequency(mappedVal);
    this->Steer_PWM->start(1000000.0/mappedVal, 20);
}
