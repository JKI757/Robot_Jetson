
/* 
 * File:   Motor.cpp
 * Author: josh
 * 
 * Created on March 11, 2020, 9:30 PM
 */

#include "Motor.h"

#define DEBUG

Motor::Motor(
        int DrivePWMPin, 
        int DriveIn1Pin, 
        int DriveIn2Pin, 
        int SteeringPWMPin,
        const unsigned short minInput,
        const unsigned short maxInput) {
        GPIO::setmode(GPIO::BOARD);
    GPIO::setup(DrivePWMPin, GPIO::OUT, GPIO::HIGH);
    drive_pwm = std::make_shared<GPIO::PWM>(DrivePWMPin, 50);
    GPIO::setup(SteeringPWMPin, GPIO::OUT, GPIO::HIGH);
    steer_pwm = std::make_shared<GPIO::PWM>(SteeringPWMPin, 1500);

    drive = std::make_unique<L298N_Jetson> (drive_pwm, 
                                            DriveIn1Pin, 
                                            DriveIn2Pin,
                                            true,
                                            MIN_THROTTLE, 
                                            MAX_THROTTLE);
    steer = std::make_unique<Servo_Jetson> (steer_pwm,  
                                            1000,  2000, 
                                            minInput, maxInput, true);

    currentSpeed = 0;
    drive->setSpeed(currentSpeed);
    currentDirection = STOP;
    
    
}

Motor::~Motor() {
    this->steer_pwm->stop();
    this->drive_pwm->stop();
            GPIO::cleanup();

}
short Motor::setDriveSpeed(const unsigned short speed) {
//    currentSpeed = map(speed, MIN_TURN, MAX_TURN, CENTER_STEER, MAX_LEFT_STEERING_ANGLE);
    currentSpeed = speed;
#ifdef DEBUG
    std::cout << "Motor Driving Speed: " << speed << std::endl;
#endif
    drive->setSpeed(speed);
    drive->run();

}

void Motor::run(Direction d) {
    currentDirection = d;
    switch(currentDirection){
        case FORWARD:
            drive->forward();
            break;
        case BACKWARD:
            drive->backward();
            break;
        case STOP:
            drive->stop();
            break;
    };
    drive->run();
}

void Motor::run() {
    drive->run();
}
void Motor::stop() {
    drive->stop();
}
void Motor::setDirection(Direction d) {
    currentDirection = d;
    switch(currentDirection){
        case FORWARD:{
            drive->forward();
        }
            break;
        case BACKWARD:{
            drive->backward();
        }
            break;
        case STOP:{
            drive->stop();
        }
            break;
    };
    drive->run();
}


void Motor::turnRight(short angle) {
    unsigned short turn_val = map(angle, MIN_TURN, MAX_TURN, CENTER_STEER, MAX_RIGHT_STEERING_ANGLE);
    steer->writeMappedValue(turn_val);

#ifdef DEBUG
    std::cout << "Turning value commanded: " <<  angle << " mapped value: " << turn_val << std::endl;
#endif
}

void Motor::turnLeft(short angle) {
     unsigned short turn_val =  map(angle, MIN_TURN, MAX_TURN, CENTER_STEER, MAX_LEFT_STEERING_ANGLE);
    steer->writeMappedValue(turn_val);

#ifdef DEBUG
    std::cout << "Turning value commanded: " <<  angle << " mapped value: " << turn_val << std::endl;
#endif
}
void Motor::turnAbsolute(short angle) {
#ifdef DEBUG
    std::cout << "Turning value commanded: " <<  angle  << std::endl;
#endif
    steer->writeMappedValue(angle);
}

unsigned short Motor::map(const unsigned short val, const unsigned short in_min, const unsigned short in_max,
        const unsigned short out_min, const unsigned short out_max) {
    if ((val <= in_max) && (val >= in_min)) {
        {
            return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
        }
    } else return 0;
}
