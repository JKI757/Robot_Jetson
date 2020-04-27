
/* 
 * File:   Motor.h
 * Author: josh
 *
 * Created on March 11, 2020, 9:30 PM
 */

#ifndef MOTOR_H
#define MOTOR_H
#define DEBUG

#include <stdio.h>
#include <string.h>
#include <fcntl.h> 
#include <errno.h> 
#include <termios.h> 
#include <unistd.h> 
#include <cmath>
#include <string>
#include <iostream>

#include "definitions.h"
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
#include <sys/ioctl.h>
#include <sys/file.h>

enum command {
    DRIVE, TURNLEFT, TURNRIGHT, DIRECTION, BRAKE
};\

//direction: 0=forward, 1=reverse

enum driving_direction {
    FORWARD, BACKWARD
};

class Motor {
public:

    Motor() {
    };
    //    Motor(const Motor& orig); //copy
    //    Motor(Motor&& other); //move
    //    Motor& operator=(const Motor& other); //copy assign
    //    Motor& operator=(Motor&& other); //move assign

    ~Motor() {
    };


    int serialInit(std::string port);

    int setDriveSpeed(int speed) {
        current_drive_speed = map(speed, MIN_THROTTLE, MAX_THROTTLE, MIN_SPEED_LIMIT, MAX_SPEED_LIMIT);
#ifdef DEBUG
        std::cout << "setting speed to: " << current_drive_speed << std::endl;
#endif
    };
    int run(driving_direction d);
    int stop();
    int turnAbsolute(unsigned char angle);
    int turnRight(int angle);
    int turnLeft(int angle);


private:
    int send_command(command b, unsigned char data);

    int port;

    driving_direction currentDirection = FORWARD;
    int current_drive_speed = 0;


    const unsigned char BRAKECOMMAND = 0x0A;
    const unsigned char DRIVECOMMAND = 0x0B;
    const unsigned char TURNLEFTCOMMAND = 0x0C;
    const unsigned char TURNRIGHTCOMMAND = 0x0E;
    const unsigned char DIRECTIONCOMMAND = 0x0F;
    int NULLDATA = 0x00;

    int map(int val, int a, int b, int c, int d) {

        if ((val <= b) && (val >= a) && (b != a)) {\
            return round(((float) val - (float) a) / ((float) b - (float) a) * ((float) d - (float) c) + (float) c);
        } else return -1;
    }

};

#endif /* MOTOR_H */