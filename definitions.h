/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   definitions.h
 * Author: josh
 *
 * Created on August 16, 2019, 10:22 PM
 */

#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include </usr/local/include/libevdev-1.0/libevdev/libevdev.h>

#define LIDAR_PORT "/dev/ttyUSB0"
#define MOTOR_PORT "/dev/ttyACM0"
#define LEFT_KEY ABS_RX
#define MAX_LEFT -32768
#define RIGHT_KEY ABS_RX
#define MAX_RIGHT 32768
#define MIN_LEFT 128
#define MIN_RIGHT -128

#define THROTTLE_KEY ABS_RY
#define MAX_THROTTLE_FORWARD -32768
#define MIN_THROTTLE_FORWARD -128
#define MAX_THROTTLE_BACKWARD 32768
#define MIN_THROTTLE_BACKWARD 128

#define LEFT_TRIGGER ABS_Z
#define RIGHT_TRIGGER ABS_RZ
#define TRIGGER_MIN 0
#define TRIGER_MAX 255

#define INPUT_DEVICE "/dev/input/js0"


#define MOTOR_FORWARD   1
#define MOTOR_BACK      2
#define MOTOR_BRAKE     3
#define MOTOR_RELEASE   4


#define NUMBER_OF_MODES 5


#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* DEFINITIONS_H */