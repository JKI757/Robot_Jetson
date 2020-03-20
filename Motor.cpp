
/* 
 * File:   Motor.cpp
 * Author: josh
 * 
 * Created on March 11, 2020, 9:30 PM
 */

#include "Motor.h"



int Motor::init(std::string port) {
    this->port = open(port.c_str(), O_RDWR | O_NOCTTY);
    if (this->port < 0) {
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
    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);
    if (tcsetattr(this->port, TCSANOW, &tty) != 0) {
        return -1;
    }
    return 0;
}

int Motor::run(driving_direction d) {
    if (d != currentDirection){
        currentDirection = d;
        if (currentDirection == FORWARD){
            send_command(DIRECTION, 0);
        }else{
            send_command(DIRECTION, 1);
            
        }
    }
    send_command(DRIVE, current_drive_speed);
}

int Motor::stop() {
    send_command(BRAKE, NULLDATA);
    return 0;
}

int Motor::send_command(command b, int data) {
    unsigned char char_data[2]={0x00,0x00};
    if (data <= 255){
        char_data[1] = (unsigned char)data;
    }
    else{
        char_data[1] = (unsigned char) data;
        char_data[0] = (unsigned char) (data >> 8);
    }
    
    switch (b) {
        case TURN:
        {
            write(Motor::port, Motor::TURNCOMMAND, sizeof (Motor::TURNCOMMAND));
            write(Motor::port, char_data, 2);
        };
            break;
        case BRAKE:
        {
            write(Motor::port, Motor::BRAKECOMMAND, sizeof (Motor::BRAKECOMMAND));
            write(Motor::port, char_data, 2);
        };
            break;
        case DRIVE:
        {
            write(Motor::port, Motor::DRIVECOMMAND, sizeof (Motor::DRIVECOMMAND));
            write(Motor::port, char_data, 2);
        };
            break;
        case TURNLEFT:
        {
            write(Motor::port, Motor::TURNLEFTCOMMAND, sizeof (Motor::TURNLEFTCOMMAND));
            write(Motor::port, char_data,2);
        };
            break;
        case TURNRIGHT:
        {
            write(Motor::port, Motor::TURNRIGHTCOMMAND, sizeof (Motor::TURNRIGHTCOMMAND));
            write(Motor::port, char_data, 2);
        };
            break;
        case DIRECTION:
        {
            write(Motor::port, Motor::DIRECTIONCOMMAND, sizeof (Motor::DIRECTIONCOMMAND));
            write(Motor::port, char_data,2);
        };
            break;
        default:
        {
            return -1;
        };
    };
    return 0;
}

int Motor::turnAbsolute(unsigned char angle) {    
    send_command(TURN, NULLDATA);
}
