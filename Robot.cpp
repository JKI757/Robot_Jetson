/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Robot.cpp
 * Author: josh
 * 
 * Created on August 6, 2019, 11:22 PM
 */

#include "Robot.h"

Robot::Robot() {
    init();
}

Robot::Robot(const Robot& orig) {
    
}

Robot::~Robot() {
}

int Robot::init(){
    m_turn_angle=0;
    m_heading = 0;
    m_speed = 0;
    m_max_speed=255;
    m_left_motor_speed = 0;
    m_right_motor_speed = 0;
    m_driving = false;
    m_lidar_on = false;
    m_left_motor_on = false;
    m_right_motor_on = false;
    m_current_mode = MANUAL;
    mh = std::make_shared<AdafruitMotorHAT>();
    left_motor = mh->getMotor(4);
    right_motor = mh->getMotor(1);
    m_driving_direction = AdafruitDCMotor::kBrake;
    return 0;   
}

int Robot::rad_to_deg(float rad){
    int deg = 0;

    return deg;
}

float Robot::deg_to_rad(int deg){
    float rad = 0.0;


    return rad;
}

int angle_trunc(int angle){
    return (angle%360);
}

void Robot::drive() {
    left_motor->setSpeed(m_left_motor_speed);
    right_motor->setSpeed(m_right_motor_speed);

    left_motor->run(m_driving_direction);
    right_motor->run(m_driving_direction);
}

int Robot::turn_right(int speed) {
    int new_angle = 0;
    std::cout << "turning right: "  << std::endl;
    left_motor->setSpeed(speed);
    right_motor->setSpeed(speed);

    left_motor->run(AdafruitDCMotor::kForward);
    right_motor->run(AdafruitDCMotor::kBackward);

    return new_angle;
}

int Robot::turn_left(int speed) {
    int new_angle = 0;
    std::cout << "turning left : " << std::endl;
    left_motor->setSpeed(speed);
    right_motor->setSpeed(speed);
    
    left_motor->run(AdafruitDCMotor::kBackward);
    right_motor->run(AdafruitDCMotor::kForward);

    return new_angle;

}

int Robot::drive_forward(int speed) {
    int new_angle = 0;
    std::cout << "driving forward speed: " << speed << std::endl;
    left_motor->setSpeed(speed);
    right_motor->setSpeed(speed);
    
    left_motor->run(AdafruitDCMotor::kForward);
    right_motor->run(AdafruitDCMotor::kForward);
    
    return new_angle;

}

int Robot::drive_reverse(int speed) {
    int new_angle = 0;
    std::cout << "driving reverse speed: " << speed << std::endl;
    left_motor->setSpeed(speed);
    right_motor->setSpeed(speed);
    
    left_motor->run(AdafruitDCMotor::kBackward);
    right_motor->run(AdafruitDCMotor::kBackward);

    return new_angle;

}

int Robot::drive_left_motor() {
    //m_left_motor_speed = speed % m_max_speed;
    std::cout<<  "Driving left motor: " << m_left_motor_speed << std::endl;
    left_motor->setSpeed(m_left_motor_speed*2);
    left_motor->run(m_driving_direction);
    return m_left_motor_speed;
}

int Robot::drive_right_motor() {
   // m_right_motor_speed = speed % m_max_speed;
    std::cout<<  "Driving right motor: " << m_right_motor_speed << std::endl;
    right_motor->setSpeed(m_right_motor_speed*2);
    right_motor->run(m_driving_direction);

    return m_right_motor_speed;
}

int Robot::change_speed(int speed){
    m_speed += speed;
    m_speed = m_speed % m_max_speed;
    return m_speed;
}

int Robot::set_left_motor_speed(int speed){
    m_left_motor_speed = speed % m_max_speed;
}
int Robot::set_right_motor_speed(int speed){
    m_right_motor_speed = speed % m_max_speed;
}

int Robot::turn(int angle){
    m_turn_angle = angle_trunc(m_turn_angle + angle);
    return m_turn_angle;
}

mode Robot::get_mode() {
    return m_current_mode;
}

std::string Robot::get_text_mode(){
    switch (m_current_mode){
        case MANUAL:{
            return "Manual";
        };break;
        case AUTOMATIC:{
            return "Automatic";
        };break;
        case TANK:{
            return "Tank";
        };break;
        case GPS:{
            return "GPS";
        };break;
        case LIDAR_AUTOMATIC:{
            return "Lidar Auto";
        };break;
        default:{
            return "";
        };break;
    }
}

mode Robot::set_mode(mode m){
    m_current_mode = m;
    return m_current_mode;
}

mode Robot::toggle_mode() {
    m_current_mode = increment_mode(m_current_mode);
    return m_current_mode;
}
mode Robot::increment_mode(mode current_mode){
    int i = static_cast<int> (current_mode);
    return (m_current_mode = (mode)(++i%NUMBER_OF_MODES));
}

AdafruitDCMotor::Command Robot::set_driving_direction(AdafruitDCMotor::Command m){
    m_driving_direction = m;
    return m_driving_direction;
}

AdafruitDCMotor::Command Robot::toggle_driving_direction() {
    if (m_driving_direction == AdafruitDCMotor::kBackward)
        m_driving_direction = AdafruitDCMotor::kForward;
    else 
        m_driving_direction = AdafruitDCMotor::kForward;
    return m_driving_direction;
}
