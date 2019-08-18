/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EventHandler.h
 * Author: josh
 *
 * Created on August 6, 2019, 9:03 PM
 */

#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#define JETSON
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <linux/input.h>
#include <string>


#include </usr/local/include/libevdev-1.0/libevdev/libevdev.h>

#include "Robot.h"

class EventHandler {
public:
    EventHandler();
    EventHandler(const EventHandler& orig);
    virtual ~EventHandler();
    
    void init(std::string device_name, Robot *r_in);
    
    void print_abs_bits(struct libevdev *dev, int axis);
    void print_code_bits(struct libevdev *dev, unsigned int type, unsigned int max);
    void print_bits(struct libevdev *dev);
    void print_props(struct libevdev *dev);
    int print_event(struct input_event *ev);
    int print_sync_event(struct input_event *ev);
    int event_loop();

private:
	struct libevdev *dev = NULL;
	const char *file = NULL;
	int fd=0;
	int rc = 1;
        Robot *r;

};

#endif /* EVENTHANDLER_H */

