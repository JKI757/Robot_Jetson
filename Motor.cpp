
/* 
 * File:   Motor.cpp
 * Author: josh
 * 
 * Created on March 11, 2020, 9:30 PM
 */

#include "Motor.h"

#define DEBUG
#include <iostream>

int Motor::serialInit(std::string port) {
    this->port = open(port.c_str(), O_RDWR | O_NOCTTY);
    if (this->port < 0) {
#ifdef DEBUG
        std::cout << "serial port is: " << port << " " << this->port << std::endl;
#endif
        return -1;
    }
    struct termios tty;
    memset(&tty, 0, sizeof (tty));
    if (tcgetattr(this->port, &tty) != 0) {
        return -1;
    }
    tty.c_cflag |= CS8; //8bits
    tty.c_cflag &= ~PARENB; //no parity
    tty.c_cflag &= ~CSTOPB; //1 stop bit

    tty.c_cflag &= ~CRTSCTS; //no flow control
    tty.c_cflag |= CREAD | CLOCAL; //disable carrier detect & sighup
    tty.c_lflag &= ~ICANON; // don't wait for newline
    tty.c_lflag &= ~ECHO;
    tty.c_lflag &= ~ECHOE;
    tty.c_lflag &= ~ECHONL; //disable echos
    tty.c_lflag &= ~ISIG; //turn off intr/quit/susp
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); //turn off software flow control
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL); //no special handling of bytes
    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
    tty.c_cc[VTIME] = 10; // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty.c_cc[VMIN] = 0;
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);
    if (tcsetattr(this->port, TCSANOW, &tty) != 0) {
        return -1;
    }
    return 0;
}

int Motor::i2cInit(unsigned char bus, char *adx){
    i2cBus = bus;
    strncpy(i2cadx, adx, 12);
    i2c_fd = open((const char *)&i2cadx, O_RDWR);
    int r = ioctl(i2c_fd, I2C_SLAVE, i2cadx);
    
}
int Motor::run(driving_direction d) {
    if (d != currentDirection) {
        currentDirection = d;
        if (currentDirection == FORWARD) {
            send_command(DIRECTION, 0);
        } else {
            send_command(DIRECTION, 1);
        }

    }
    send_command(DRIVE, current_drive_speed);
}

int Motor::stop() {
    send_command(BRAKE, NULLDATA);
    return 0;
}

int Motor::turnRight(int angle) {
    unsigned char turn_val = (unsigned char) map(angle, MIN_TURN, MAX_TURN, CENTER_STEER, MAX_RIGHT_STEERING_ANGLE);
    send_command(TURNLEFT, turn_val);

#ifdef DEBUG
    printf(" Turning value: %i \n", turn_val);
#endif
    return 0;
}

int Motor::turnLeft(int angle) {
    unsigned char turn_val = (unsigned char) map(angle, MIN_TURN, MAX_TURN, CENTER_STEER, MAX_LEFT_STEERING_ANGLE);
    send_command(TURNRIGHT, turn_val);

#ifdef DEBUG
    printf(" Turning value: %i \n", turn_val);
#endif
    return 0;



}

int Motor::send_command(command b, int data) {
    unsigned char char_data = (unsigned char) data;
    unsigned char read_buf [256];
#ifdef DEBUG
    printf("Command is: %i Data is: %02hhx", b, char_data);
#endif
    switch (b) {
        case BRAKE:
        {
            i2c_smbus_write_byte(i2c_fd, Motor::BRAKECOMMAND);
            
            write(Motor::port, &(Motor::BRAKECOMMAND), 1);
            write(Motor::port, &char_data, 1);
        };
            break;
        case DRIVE:
        {
            write(Motor::port, &(Motor::DRIVECOMMAND), 1);
            write(Motor::port, &char_data, 1);
        };
            break;
        case TURNLEFT:
        {
            write(Motor::port, &(Motor::TURNLEFTCOMMAND), 1);
            write(Motor::port, &char_data, 1);
        };
            break;
        case TURNRIGHT:
        {
            write(Motor::port, &(Motor::TURNRIGHTCOMMAND), 1);
            write(Motor::port, &char_data, 1);
        };
            break;
        case DIRECTION:
        {
            write(Motor::port, &(Motor::DIRECTIONCOMMAND), 1);
            write(Motor::port, &char_data, 1);
        };
            break;
        default:
        {
            return -1;
        };
    };


    usleep (1000);
    return 0;
}

int Motor::turnAbsolute(unsigned char angle) {
    send_command(TURN, NULLDATA);
}
