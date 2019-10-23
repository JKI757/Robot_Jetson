/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   i2cInterface.cpp
 * Author: josh
 * 
 * Created on August 17, 2019, 11:52 PM
 */

#include "i2cInterface.h"

i2cInterface::i2cInterface() {
};

i2cInterface::i2cInterface(const i2cInterface& orig) {
};

i2cInterface::~i2cInterface() {
    i2c_close(device_fd);
};


int i2cInterface::init(){
    
    return 0;
};

int i2cInterface::init(char* device_path){
    if ((device_fd = i2c_open(device_path)) == -1) {
        perror("Open i2c bus error");
        return -1;
    }
    else{
        device.bus = device_fd;
        device.addr = ADAFRUIT_MOTORHAT;
        device.tenbit = 0;
        device.delay = 10;
        device.flags = 0;
        device.page_bytes = 8;
        device.iaddr_bytes = 0; /* Set this to zero, and using i2c_ioctl_xxxx API will ignore chip internal address */

        return device_fd;
    }
}

    int i2cInterface::I2CWriteReg8(){
        
    }
    int i2cInterface::I2CReadReg8(){
        
    }

