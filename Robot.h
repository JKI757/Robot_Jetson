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
#define ROBOT_H

class Robot {
public:
    Robot();
    Robot(const Robot& orig);
    virtual ~Robot();
    
    int rad_to_deg(float rad);
    float deg_to_rad(int deg);
    
    void drive(int speed, int turn_angle);
    int turn_right(int turn_angle);
    int turn_left(int turn_angle);
    int drive_forward(int speed);
    int drive_reverse(int speed);
    
    int change_speed(int speed);
    int turn(int angle);
    
private:
    
    int turn_angle;
    int heading;
    int speed;
    
};

#endif /* ROBOT_H */

