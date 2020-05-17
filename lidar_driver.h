/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   lidar_driver.h
 * Author: josh
 *
 * Created on March 19, 2020, 11:26 PM
 */

#ifndef LIDAR_DRIVER_H
#define LIDAR_DRIVER_H

#include "rplidar.h"
#include <memory>
#include "definitions.h"


#ifndef _countof
#define _countof(_Array) (int)(sizeof(_Array) / sizeof(_Array[0]))
#endif

#ifdef _WIN32
#include <Windows.h>
#define delay(x)   ::Sleep(x)
#else
#include <unistd.h>
static inline void delay(_word_size_t ms){
    while (ms>=1000){
        usleep(1000*1000);
        ms-=1000;
    };
    if (ms!=0)
        usleep(ms*1000);
}
#endif


class lidar_driver {
public:

    lidar_driver() {
        driver =  rp::standalone::rplidar::RPlidarDriver::CreateDriver(rp::standalone::rplidar::DRIVER_TYPE_SERIALPORT);
    };
    lidar_driver(const lidar_driver& orig);
    virtual ~lidar_driver();

    int init() {
        const char * port = LIDAR_PORT;
        _u32 baudrate = 115200;
        driver->connect(port, baudrate);
        rplidar_response_device_health_t healthinfo;
        rplidar_response_device_info_t devinfo;

        driver->getDeviceInfo(devinfo);
        driver->getHealth(healthinfo);
        driver->stop();
        driver->stopMotor();

    }

private:
    rp::standalone::rplidar::RPlidarDriver* driver;
};

#endif /* LIDAR_DRIVER_H */

