/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   i2cInterface.h
 * Author: josh
 *
 * Created on August 17, 2019, 11:52 PM
 */

#ifndef I2CINTERFACE_H
#define I2CINTERFACE_H

#include "definitions.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

class i2cInterface {
public:
    i2cInterface();
    i2cInterface(const i2cInterface& orig);
    virtual ~i2cInterface();
    int init();
    int init(char* device_path);
    //int init(int bus, int bus_name, int addr, int iaddr_bytes, int page_bytes, int bus_num);
    int I2CWriteReg8();
    int I2CReadReg8();
    
private:
    I2CDevice device;
    int device_fd;
};

#endif /* I2CINTERFACE_H */

