/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EventHandler.cpp
 * Author: josh
 * 
 * Created on August 6, 2019, 9:03 PM
 */

#include "EventHandler.h"

EventHandler::EventHandler() {
    kill = false;
}

EventHandler::EventHandler(const EventHandler& orig) {
}

EventHandler::~EventHandler() {
    
    rc = 0;
    libevdev_free(dev);

}

/*
 * Copyright © 2013 Red Hat, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */


void EventHandler::init(std::string device_name, std::shared_ptr<Robot>r_in){

    fd = open(device_name.c_str(), O_RDONLY);
    if (fd < 0) {
            perror("Failed to open device");
            exit(0);
    }

    rc = libevdev_new_from_fd(fd, &dev);
    if (rc < 0) {
            fprintf(stderr, "Failed to init libevdev (%s)\n", strerror(-rc));
            exit(0);
    }
    
    r = r_in;
    
    printf("Input device ID: bus %#x vendor %#x product %#x\n",
                    libevdev_get_id_bustype(dev),
                    libevdev_get_id_vendor(dev),
                    libevdev_get_id_product(dev));
    printf("Evdev version: %x\n", libevdev_get_driver_version(dev));
    printf("Input device name: \"%s\"\n", libevdev_get_name(dev));
    printf("Phys location: %s\n", libevdev_get_phys(dev));
    printf("Uniq identifier: %s\n", libevdev_get_uniq(dev));
    print_bits(dev);
    //print_props(dev);

}


void EventHandler::print_abs_bits(struct libevdev *dev, int axis)
{
	const struct input_absinfo *abs;

	if (!libevdev_has_event_code(dev, EV_ABS, axis))
		return;

	abs = libevdev_get_abs_info(dev, axis);

	printf("	Value	%6d\n", abs->value);
	printf("	Min	%6d\n", abs->minimum);
	printf("	Max	%6d\n", abs->maximum);
	if (abs->fuzz)
		printf("	Fuzz	%6d\n", abs->fuzz);
	if (abs->flat)
		printf("	Flat	%6d\n", abs->flat);
	if (abs->resolution)
		printf("	Resolution	%6d\n", abs->resolution);
}

void EventHandler::print_code_bits(struct libevdev *dev, unsigned int type, unsigned int max)
{
    unsigned int i;
    for (i = 0; i <= max; i++) {
        if (!libevdev_has_event_code(dev, type, i))
            continue;

        printf("    Event code %i (%s)\n", i, libevdev_event_code_get_name(type, i));
        if (type == EV_ABS)
            print_abs_bits(dev, i);
    }
}

void EventHandler::print_bits(struct libevdev *dev)
{
    unsigned int i;
    printf("Supported events:\n");

    for (i = 0; i <= EV_MAX; i++) {
        if (libevdev_has_event_type(dev, i))
            printf("  Event type %d (%s)\n", i, libevdev_event_type_get_name(i));
        switch(i) {
            case EV_KEY:
                    print_code_bits(dev, EV_KEY, KEY_MAX);
                    break;
            case EV_REL:
                    print_code_bits(dev, EV_REL, REL_MAX);
                    break;
            case EV_ABS:
                    print_code_bits(dev, EV_ABS, ABS_MAX);
                    break;
            case EV_LED:
                    print_code_bits(dev, EV_LED, LED_MAX);
                    break;
        }
    }
}

void EventHandler::print_props(struct libevdev *dev)
{
    unsigned int i;
    printf("Properties:\n");

    for (i = 0; i <= INPUT_PROP_MAX; i++) {
        if (libevdev_has_property(dev, i))
            printf("  Property type %d (%s)\n", i,
                            libevdev_property_get_name(i));
    }
}

int EventHandler::print_event(struct input_event *ev)
{
    if (ev->type == EV_SYN)
        printf("Event: time %ld.%06ld, ++++++++++++++++++++ %s +++++++++++++++\n",
#ifndef JETSON
            ev->input_event_sec,
            ev->input_event_usec,
#else
            ev->time.tv_sec,
            ev->time.tv_usec,

#endif
            libevdev_event_type_get_name(ev->type));
    else
        printf("Event: time %ld.%06ld, type %d (%s), code %d (%s), value %d\n",
#ifndef JETSON
            ev->input_event_sec,
            ev->input_event_usec,
    #else
            ev->time.tv_sec,
            ev->time.tv_usec,
    #endif

            ev->type,
            libevdev_event_type_get_name(ev->type),
            ev->code,
            libevdev_event_code_get_name(ev->type, ev->code),
            ev->value);
    return 0;
}

int EventHandler::print_sync_event(struct input_event *ev)
{
    printf("SYNC: ");
    print_event(ev);
    return 0;
}

int EventHandler::event_loop()
{
    do {
        struct input_event ev;
        rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL|LIBEVDEV_READ_FLAG_BLOCKING, &ev);
        if (rc == LIBEVDEV_READ_STATUS_SYNC) {
            //printf("::::::::::::::::::::: dropped ::::::::::::::::::::::\n");
            while (rc == LIBEVDEV_READ_STATUS_SYNC) {
                    print_sync_event(&ev);
                    rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_SYNC, &ev);
            }
           // printf("::::::::::::::::::::: re-synced ::::::::::::::::::::::\n");
        } else if (rc == LIBEVDEV_READ_STATUS_SUCCESS)
            print_event(&ev);
        std::cout << "current robot mode: " <<  r->get_text_mode() << std::endl;
        switch (ev.code){
            case BTN_WEST:{
                if (ev.value == 1){
                    r->toggle_mode();
                }
                r->set_driving_direction(AdafruitDCMotor::kBrake);
            };break;
//            case BTN_START: {
//                if (ev.value == 1)
//                    set_kill(true);
//            }; break;
            case BTN_SELECT:{ //"Back" Button -- used as a reset, kills everything and starts over
                r->init();
            } break;
            case BTN_EAST:{ //"B" Button -- used to shift from forward to reverse
                r->toggle_driving_direction();
            };break;
        }
        switch (r->get_mode()) {
            case MANUAL: {
                switch (ev.code) {
                    case ABS_RX:
                    {
                        if (ev.value < -150) {
                            //calculate the angle based on value
                            r->turn_left(abs(ev.value));
                        } else if (ev.value > 150) {
                            r->turn_right(abs(ev.value));
                        }
                        else{
                            r->turn_zero();
                        }
                    };break;
                    case ABS_RY:
                    {
                        if (ev.value < -150) {
                            //calculate the angle based on value
//                            r->drive_forward(abs(ev.value));
                            r->set_driving_direction(AdafruitDCMotor::kForward);
                            if (r->get_driving()){
                                r->change_speed(ev.value);
                            }
                            else{
                                r->change_speed(abs(ev.value));
                                r->drive();
                            }
                            
                        } else if (ev.value > 150) {
                            r->set_driving_direction(AdafruitDCMotor::kBackward);
                            if (r->get_driving()){
                                r->change_speed(ev.value);
                            }
                            else{
                                r->change_speed(abs(ev.value));
                                r->drive();
                            }
//                            r->drive_reverse(abs(ev.value));
                        } else if (ev.value >-150 && ev.value < 150){
                            r->drive_brake();
                            r->set_driving(false);
                        }
                    };break;
                }
                //run here??
            }; break; //case manual
            case AUTOMATIC:{
                
                
                
            };break;
            case GPS:{
                
            };break;
            case LIDAR_AUTOMATIC:{
                
            };break;
            default:{}
                break;
        }

        
        
        
    } while ((rc == LIBEVDEV_READ_STATUS_SYNC || rc == LIBEVDEV_READ_STATUS_SUCCESS || rc == -EAGAIN) && kill == false);

    if (rc != LIBEVDEV_READ_STATUS_SUCCESS && rc != -EAGAIN)
        fprintf(stderr, "Failed to handle events: %s\n", strerror(-rc));


    return rc;
}
