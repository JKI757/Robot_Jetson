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


/*
 * 
 */
int main(int argc, char** argv) {
    
    EventHandler *evh = new EventHandler();
    
    evh->init("/dev/input/event2");
   
    evh->event_loop();
    
    return 0;
}

