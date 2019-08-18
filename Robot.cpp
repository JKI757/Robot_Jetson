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
    turn_angle=0;
    heading = 0;
    speed = 0;
    
}

Robot::Robot(const Robot& orig) {
    
}

Robot::~Robot() {
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
void Robot::drive(int speed, int turn_angle) {

}

int Robot::turn_right(int turn_angle) {
    int new_angle = 0;
    std::cout << "turning right angle: " << turn_angle << std::endl;

    return new_angle;
}

int Robot::turn_left(int turn_angle) {
    int new_angle = 0;
    std::cout << "turning left angle: " << turn_angle << std::endl;

    return new_angle;

}

int Robot::drive_forward(int speed) {
    int new_angle = 0;
    std::cout << "driving forward speed: " << speed << std::endl;
    return new_angle;

}

int Robot::drive_reverse(int speed) {
    int new_angle = 0;
    std::cout << "driving reverse speed: " << speed << std::endl;

    return new_angle;

}

int Robot::change_speed(int speed){
    int new_speed = 0;
    
    return new_speed;
}
int Robot::turn(int angle){
    m_turn_angle = angle_trunc(m_turn_angle + angle);
    return m_turn_angle;
}

    mode Robot::get_mode(){
        return m_current_mode;
    }
