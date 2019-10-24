/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Robot.h
 * Author: josh
 *
 * Created on August 6, 2019, 11:22 PM
 */

#ifndef ROBOT_H
#include <iostream>
#include "definitions.h"
#include "adafruitmotorhat.h"
#include "adafruitdcmotor.h"
#include <memory>

#define ROBOT_H

enum mode {
    MANUAL, AUTOMATIC, TANK, GPS, LIDAR_AUTOMATIC
};


class Robot {
public:


    Robot();
    Robot(const Robot& orig);
    virtual ~Robot();
    
    int init();
    int rad_to_deg(float rad);
    float deg_to_rad(int deg);
    
    void drive();
    int turn_right(int speed);
    int turn_left(int speed);
    int drive_forward(int speed);
    int drive_reverse(int speed);
    int drive_left_motor();
    int drive_right_motor();
    
    int set_left_motor_speed(int speed);
    int set_right_motor_speed(int speed);
    int change_speed(int speed);
    int turn(int angle);
    
    mode get_mode();
    std::string get_text_mode();
    mode set_mode(mode m);

    mode toggle_mode();
    mode increment_mode(mode current_mode);
    AdafruitDCMotor::Command set_driving_direction(AdafruitDCMotor::Command m);
    AdafruitDCMotor::Command toggle_driving_direction();

private:
    
    std::shared_ptr<AdafruitMotorHAT> mh;
    std::shared_ptr<AdafruitDCMotor> left_motor;
    std::shared_ptr<AdafruitDCMotor> right_motor;
    
    int m_turn_angle;
    int m_heading;
    int m_speed;
    int m_max_speed;
    int m_left_motor_speed;
    int m_right_motor_speed;
    bool m_driving;
    AdafruitDCMotor::Command m_driving_direction;
    bool m_lidar_on;
   
    bool m_left_motor_on;
    bool m_right_motor_on;
    
    
    mode m_current_mode;
    
};

#endif /* ROBOT_H */

