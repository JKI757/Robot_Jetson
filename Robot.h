
/* 
 * File:   Robot.h
 * Author: josh
 *
 * Created on August 6, 2019, 11:22 PM
 */
#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <memory>
#include "Motor.h"
#include "definitions.h"
#include "lidar_driver.h"

#define DEBUG

enum mode {MANUAL, AUTOMATIC, TANK, GPS, LIDAR_AUTOMATIC};


class Robot {
    
public:

    Robot();
    Robot(const Robot& orig);
    virtual ~Robot();
    
    int init();
    int deinit();

    int rad_to_deg(float rad);
    float deg_to_rad(int deg);
    
    void drive();
    int turn_right(int speed);
    int turn_left(int speed);
    int turn_zero();
    int drive_forward(int speed);
    int drive_reverse(int speed);
    int drive_brake();

    int set_drive_motor_speed(int speed);
    int set_steering_motor_speed(int speed);
    int change_speed(int speed);
    int turn(int angle);
    const Direction get_driving_direction(){return m_driving_direction;};
    void set_driving_direction(Direction direction){m_driving_direction = direction;};
    void toggle_disconnected(){
        if (m_disconnected) m_disconnected=false; else m_disconnected=true; 
#ifdef DEBUG 
         std::cout << "Disconnected is: " << m_disconnected << std::endl; 
#endif 
    };
    const bool get_driving(){return m_driving;};
    void set_driving(bool d){m_driving = d;};
    mode get_mode();
    std::string get_text_mode();
    mode set_mode(mode m);

    mode toggle_mode();
    mode increment_mode(mode current_mode);
    Direction toggle_driving_direction();

private:
    
    std::shared_ptr<Motor> motor;
    
#ifdef LIDAR
    std::shared_ptr<lidar_driver> lidar = std::make_shared<lidar_driver>();
#endif


    int m_turn_angle;
    int m_heading;
    int m_speed;
    int m_max_speed;
    int m_drive_motor_speed;
    bool m_driving;
    Direction m_driving_direction;
    Command m_command;
    bool m_lidar_on;
   
    mode m_current_mode;
    bool m_disconnected;
    
    
    
};

#endif /* ROBOT_H */


