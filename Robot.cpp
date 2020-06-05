
/* 
 * File:   Robot.cpp
 * Author: josh
 * 
 * Created on August 6, 2019, 11:22 PM
 */

#include "Robot.h"
#define DEBUG
Robot::Robot() {
    init();
}

Robot::Robot(const Robot& orig) {

}

Robot::~Robot() {


}

int Robot::init() {
    m_turn_angle = 0;
    m_heading = 0;
    m_speed = 0;
    m_max_speed = 100;
    m_drive_motor_speed = 0;
    m_driving = false;
    m_lidar_on = false;
    m_current_mode = MANUAL;
    m_driving_direction = FORWARD;
    m_command = BRAKE;
    m_disconnected = true;
    motor = std::make_shared<Motor> ( 
       JETSON_DRIVE_PIN, 
       JETSON_IN1_PIN, 
       JETSON_IN2_PIN, 
       JETSON_STEER_PIN,
       0,
       255);
#ifdef LIDAR
    lidar->init();
#endif
    //motor->run(m_driving_direction);

    return 0;
}

int Robot::deinit() {
    m_turn_angle = 0;
    m_heading = 0;
    m_speed = 0;
    m_max_speed = 0;
    m_drive_motor_speed = 0;
    m_driving = false;
    m_lidar_on = false;
    m_current_mode = MANUAL;
    m_driving_direction = FORWARD;
    motor->stop();

    if (!m_disconnected) {
        motor->stop();
    }
    return 0;
}


void Robot::drive() {
    m_driving = true;
    if (!m_disconnected) {
        motor->setDriveSpeed(m_drive_motor_speed);
        motor->run(m_driving_direction);
    }
#ifdef DEBUG
    std::cout << "Robot Driving " << m_driving_direction << " speed: " << m_drive_motor_speed << std::endl;
#endif
}

void Robot::turn_right(int amount) {

    //
#ifdef DEBUG
    std::cout << "Robot turning right: " << amount << std::endl;
#endif
    if (!m_disconnected) {
        motor->turnRight(amount);
    }
}

void Robot::turn_left(int amount) {
#ifdef DEBUG
    std::cout << "Robot turning left : " << amount << std::endl;
#endif
    if (!m_disconnected) {

        motor->turnLeft(amount);
    }
}

void Robot::turn_zero() {
#ifdef DEBUG
    std::cout << "Robot center steering : " << std::endl;
#endif

    if (!m_disconnected) {
        motor->turnAbsolute(CENTER_STEER);
    }
}

void Robot::drive_forward(int speed) {
#ifdef DEBUG
    std::cout << "Robot driving forward speed: " << speed << std::endl;
#endif
    set_driving_direction(FORWARD);

    if (!m_disconnected) {
        motor->setDriveSpeed(speed);
        motor->run(FORWARD);
    }
}

void Robot::drive_reverse(int speed) {
#ifdef DEBUG
    std::cout << "Robot driving reverse speed: " << speed << std::endl;
#endif
    set_driving_direction(BACKWARD);

    if (!m_disconnected) {
        motor->setDriveSpeed(speed);
        motor->run(BACKWARD);
    }
}

void Robot::drive_brake() {
#ifdef DEBUG
    std::cout << "braking" << std::endl;
#endif
    motor->stop();
}

void Robot::change_speed(int speed) {
    m_drive_motor_speed = speed;
    motor->setDriveSpeed(speed);
}

void Robot::set_drive_motor_speed(int speed) {
    m_drive_motor_speed = speed;
    motor->setDriveSpeed(speed);
}


mode Robot::get_mode() {
    return m_current_mode;
}

std::string Robot::get_text_mode() {
    switch (m_current_mode) {
        case MANUAL:
        {
            return "Manual";
        };
            break;
        case AUTOMATIC:
        {
            return "Automatic";
        };
            break;
        case TANK:
        {
            return "Tank";
        };
            break;
        case GPS:
        {
            return "GPS";
        };
            break;
        case LIDAR_AUTOMATIC:
        {
            return "Lidar Auto";
        };
            break;
        default:
        {
            return "";
        };
            break;
    }
}

void Robot::set_mode(mode m) {
    m_current_mode = m;
}

mode Robot::toggle_mode() {
    m_current_mode = increment_mode(m_current_mode);
#ifdef DEBUG
    std::cout << "Change Mode to: " << get_text_mode() << std::endl;
#endif

    return m_current_mode;
}

mode Robot::increment_mode(mode current_mode) {
    int i = static_cast<int> (current_mode);
    return (m_current_mode = (mode) (++i % NUMBER_OF_MODES));
}

Direction Robot::toggle_driving_direction() {
#ifdef DEBUG
    std::cout << "Change Driving Direction ";
#endif
    if (m_driving_direction == BACKWARD) {
        m_driving_direction = FORWARD;
#ifdef DEBUG
        std::cout << "New Direction is Forward" << std::endl;
#endif
    } else {
        m_driving_direction = BACKWARD;
#ifdef DEBUG
        std::cout << "New Direction is Backward" << std::endl;

#endif
    }
    return m_driving_direction;
}

