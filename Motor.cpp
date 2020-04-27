
/* 
 * File:   Motor.cpp
 * Author: josh
 * 
 * Created on March 11, 2020, 9:30 PM
 */

#include "Motor.h"

#define DEBUG

int Motor::serialInit(std::string port) {
#ifdef DEBUG
    printf("serial port is: %s %i \n", port.c_str(), this->port);
    
#endif
    this->port = open(port.c_str(), O_RDWR );

    if (flock(this->port, LOCK_EX | LOCK_NB) == -1) {
        throw std::runtime_error("Serial port with file descriptor " +
                std::to_string(this->port) + " is already locked by another process.");
    }

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
    printf(" \nTurning value: %i \n", turn_val);
#endif
    return 0;
}

int Motor::turnLeft(int angle) {
    unsigned char turn_val = (unsigned char) map(angle, MIN_TURN, MAX_TURN, CENTER_STEER, MAX_LEFT_STEERING_ANGLE);
    send_command(TURNRIGHT, turn_val);

#ifdef DEBUG
    printf(" \nTurning value: %i \n", turn_val);
#endif
    return 0;



}

int Motor::send_command(command b, unsigned char data) {
    char read_buf [256] = {0x00};
    int n = 0;
    int o = 0;
    int read_bytes = 0;
#ifdef DEBUG
    printf("\nCommand is: %i Data is: %02hhx\n", b, data);
#endif
    switch (b) {
        case BRAKE:
        {

            n = write(this->port, &(Motor::BRAKECOMMAND), 1);
            o = write(this->port, &data, 1);
            
#ifdef DEBUG
            tcdrain(this->port);
            read_bytes = read(this->port, read_buf, sizeof(read_buf));
            if (read_bytes > 0){
                read_buf[read_bytes] = 0;
                printf("Read %d: \"%s\"\n", read_bytes, read_buf);
            }
#endif
        };
            break;
        case DRIVE:
        {
            n = write(this->port, &(Motor::DRIVECOMMAND), 1);
            o = write(this->port, &data, 1);
#ifdef DEBUG
            tcdrain(this->port);
            read_bytes = read(this->port, read_buf, sizeof(read_buf));
            if (read_bytes > 0){
                read_buf[read_bytes] = 0;
                printf("Read %d: \"%s\"\n", read_bytes, read_buf);
            }
#endif

        };
            break;
        case TURNLEFT:
        {
            n = write(this->port, &(Motor::TURNLEFTCOMMAND), 1);
            o = write(this->port, &data, 1);
#ifdef DEBUG
            tcdrain(this->port);
            read_bytes = read(this->port, read_buf, sizeof(read_buf));
            if (read_bytes > 0){
                read_buf[read_bytes] = 0;
                printf("Read %d: \"%s\"\n", read_bytes, read_buf);
            }
#endif

        };
            break;
        case TURNRIGHT:
        {
            n = write(this->port, &(Motor::TURNRIGHTCOMMAND), 1);
            o = write(this->port, &data, 1);
#ifdef DEBUG
            tcdrain(this->port);
            read_bytes = read(this->port, read_buf, sizeof(read_buf));
            if (read_bytes > 0){
                read_buf[read_bytes] = 0;
                printf("Read %d: \"%s\"\n", read_bytes, read_buf);
            }
#endif

        };
            break;
        case DIRECTION:
        {
            n = write(this->port, &(Motor::DIRECTIONCOMMAND), 1);
            o = write(this->port, &data, 1);
#ifdef DEBUG
            tcdrain(this->port);
            read_bytes = read(this->port, read_buf, sizeof(read_buf));
            if (read_bytes > 0){
                read_buf[read_bytes] = 0;
                printf("Read %d: \"%s\"\n", read_bytes, read_buf);
            }
#endif

        };
            break;
        default:
        {
            return -1;
        };

    };
#ifdef DEBUG
    printf("\nnumber of command bytes sent: %i\n", n);
    printf("\nnumber of data bytes sent: %i\n", o);
    printf("\nnumber of bytes read: %i\n", read_bytes);
    n = 0;
    o = 0;
    read_bytes = 0;
    memset(read_buf, 0, sizeof(read_buf));
#endif

    //usleep (100);
    ioctl(this->port, TCFLSH, 2);

    return 0;
}
