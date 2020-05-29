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
    this->mapMin = 0;
    this->mapMax = 255;
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
                                        const unsigned short mapMin, const unsigned short mapMax){
    //mapMin and mapMax are the expected range of values coming in as commands 
    //if you use these values, use the writeMappedValue method with a value in the range (mapMin, mapMax)
    //and the value will be mapped to (minUs, maxUs)
    GPIO::setmode(GPIO::BOARD);
    GPIO::setup(pin, GPIO::OUT, GPIO::HIGH);
    this->Steer_PWM = std::make_shared<GPIO::PWM>(pin, 1500);
    //1500 is centered for a normal steering servo for RC car
    this->minUs = minUs;
    this->maxUs = maxUs;
    this->mapMin = mapMin;
    this->mapMax = mapMax;
    this->setup = true;

    
}

Servo_Jetson::Servo_Jetson(std::shared_ptr<GPIO::PWM> steer, const unsigned short minUs, const unsigned short maxUs, const unsigned short mapMin, const unsigned short mapMax, bool setup){
    //mapMin and mapMax are the expected range of values coming in as commands 
    //if you use these values, use the writeMappedValue method with a value in the range (mapMin, mapMax)
    //and the value will be mapped to (minUs, maxUs)
    this->Steer_PWM = steer;
    //1500 is centered for a normal steering servo for RC car
    this->minUs = minUs;
    this->maxUs = maxUs;
    this->mapMin = mapMin;
    this->mapMax = mapMax;
    this->setup = false;
}


void Servo_Jetson::writeAngle(const unsigned short angle){\
    const unsigned char mappedVal = mapAngle(angle);
    this->Steer_PWM->ChangeFrequency(1.0/mappedVal);
    this->Steer_PWM->start(.5);
}
void Servo_Jetson::writeUs(const unsigned short microseconds){
     this->Steer_PWM->ChangeFrequency(1.0/microseconds);
     this->Steer_PWM->start(.5);
     
}

unsigned short Servo_Jetson::map(const short val){
        if ((val <= mapMax) && (val >= mapMin) && (mapMax != mapMin)) {
            return round( (float)minUs + ((float)(maxUs - minUs) / (float)(mapMax - mapMin)) * (float)(val - mapMin) );
//            return round(((float) val - (float) mapMin) / ((float) mapMax - (float) mapMin) * ((float) minUs - (float) maxUs) + (float) mapMin);
        } else return -1;
    }
unsigned short Servo_Jetson::mapAngle(const short val){
        if ((val <= 360) && (val >= 0)) {\
            return round(((float) val - (float) 0) / ((float) 360 - (float) 0) * ((float) minUs - (float) maxUs) + (float) minUs);
        } else return -1;
    }
void Servo_Jetson::writeMappedValue(const short val){
    std::cout << "value passed into write mapped value: " << val << std::endl;
    //takes a value mapped between minRange and maxRange to minUs and maxUs and calculates a microsecond value from there
    unsigned short mappedVal = map(val);
    std::cout << "mapped value: " << mappedVal << std::endl;
    this->Steer_PWM->ChangeFrequency(mappedVal);
    this->Steer_PWM->start(.5);
}
