/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: josh
 *
 * Created on August 6, 2019, 8:42 PM
 */

#include <cstdlib>
#include "EventHandler.h"
#include <memory>
#include "lidar_driver.h"
#include "definitions.h"

/*
 * 
 */
#define DEBUG

int main(int argc, char** argv) {
    
    std::shared_ptr<EventHandler> evh = std::make_shared<EventHandler>();
        
    std::shared_ptr<Robot> r = std::make_shared<Robot>();
    

    evh->init(INPUT_DEVICE, r);
    evh->event_loop();
    
    return 0;
}
