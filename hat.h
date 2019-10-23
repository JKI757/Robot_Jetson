/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hat.h
 * Author: josh
 *
 * Created on August 21, 2019, 11:42 PM
 */

#ifndef HAT_H
#define HAT_H
#include <i2c.h>
#include "i2cInterface.h"
#include "definitions.h"

#define word    unsigned short



class hat{
public:
    hat();
    ~hat();
    
    word init();
    void initMotor(word i2c, word motor);
    void setSpeed(word i2c, word motor, word speed);
    void runMotor(word i2c, word motor, word command);
    void setPin(word i2c, word pin, word value);
    void setPWM(word i2c, word pin, word on, word off);
    void setAllPWM(word i2c, word on, word off);


private:
    i2cInterface *i2c_connection;
    
};
#endif /* HAT_H */

