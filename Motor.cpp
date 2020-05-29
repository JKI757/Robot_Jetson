
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
        const unsigned short minUs,
        const unsigned short maxUs,
        const unsigned short mapMin,
        const unsigned short mapMax) {
    
    drive = std::make_unique<L298N_Jetson> (DrivePWMPin, 
                                            DriveIn1Pin, 
                                            DriveIn2Pin);
    steer = std::make_unique<Servo_Jetson> (SteeringPWMPin,  
                                            minUs,  maxUs, 
                                            mapMin, mapMax);

    currentSpeed = 0;
    currentDirection = STOP;
    
    
}

Motor::~Motor() {
    this->steer_pwm->stop();
    this->drive_pwm->stop();
            GPIO::cleanup();

}
short Motor::setDriveSpeed(const unsigned short speed) {
    currentSpeed = speed;
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


void Motor::turnRight(short angle) {
    unsigned short turn_val = map(angle, MIN_TURN, MAX_TURN, CENTER_STEER, MAX_RIGHT_STEERING_ANGLE);
    steer->writeMappedValue(turn_val);

#ifdef DEBUG
    printf(" \nTurning value: %i \n", turn_val);
#endif
}

void Motor::turnLeft(short angle) {
    unsigned short turn_val =  map(angle, MIN_TURN, MAX_TURN, CENTER_STEER, MAX_LEFT_STEERING_ANGLE);
    steer->writeMappedValue(turn_val);

#ifdef DEBUG
    printf(" \nTurning value: %i \n", turn_val);
#endif
}
void Motor::turnAbsolute(short angle) {
#ifdef DEBUG
    std::cout << "steering value passed in: " << angle << std::endl;
#endif
    steer->writeMappedValue(angle);
}
