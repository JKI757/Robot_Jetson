
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
    m_max_speed = 255;
    m_drive_motor_speed = 0;
    m_driving = false;
    m_lidar_on = false;
    m_current_mode = MANUAL;
    m_driving_direction = FORWARD;
    m_command = BRAKE;
    m_disconnected = true;
    motor = std::make_shared<Motor> ();
    motor->init(MOTOR_PORT);
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

int Robot::rad_to_deg(float rad) {
    int deg = 0;

    return deg;
}

float Robot::deg_to_rad(int deg) {
    float rad = 0.0;


    return rad;
}

int angle_trunc(int angle) {
    return (angle % 360);
}

void Robot::drive() {
    m_driving = true;
    if (!m_disconnected) {
        motor->setDriveSpeed(m_drive_motor_speed);
        motor->run(m_driving_direction);
    }
#ifdef DEBUG
    std::cout << "Driving " << m_driving_direction << "speed: " << m_drive_motor_speed << std::endl;
#endif
}

int Robot::turn_right(int angle) {

    int new_angle = 0;
    //
    //    if (!m_disconnected) {
    //        steering_motor->run(FORWARD);
    //    }
#ifdef DEBUG
    std::cout << "turning right" << std::endl;
#endif
    return new_angle;
}

int Robot::turn_left(int angle) {
    int new_angle = 0;
#ifdef DEBUG
    std::cout << "turning left : " << std::endl;
#endif

    //    if (!m_disconnected) {
    //        steering_motor->run(AdafruitDCMotor::kBackward);
    //    }
    return new_angle;
}

int Robot::turn_zero() {
#ifdef DEBUG
    std::cout << "turning zero : " << std::endl;
#endif

    if (!m_disconnected) {
        motor->turnAbsolute(0);
    }
}

int Robot::drive_forward(int speed) {
#ifdef DEBUG
    std::cout << "driving forward speed: " << speed << std::endl;
#endif
    set_driving_direction(FORWARD);

    if (!m_disconnected) {
        motor->setDriveSpeed(speed % m_max_speed);
        motor->run(FORWARD);
    }
    return m_drive_motor_speed;

}

int Robot::drive_reverse(int speed) {
#ifdef DEBUG
    std::cout << "driving reverse speed: " << speed << std::endl;
#endif
    set_driving_direction(BACKWARD);

    if (!m_disconnected) {
        motor->setDriveSpeed(speed % m_max_speed);
        motor->run(BACKWARD);
    }
    return m_drive_motor_speed;

}

int Robot::drive_brake() {
#ifdef DEBUG
    std::cout << "braking" << std::endl;
#endif
    motor->stop();

}

int Robot::change_speed(int speed) {
    //    m_speed += speed;
    m_drive_motor_speed = speed % m_max_speed;
    return m_drive_motor_speed;
}

int Robot::set_drive_motor_speed(int speed) {
    m_drive_motor_speed = speed % m_max_speed;
}

int Robot::turn(int angle) {
    m_turn_angle = angle_trunc(m_turn_angle + angle);
    return m_turn_angle;
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

mode Robot::set_mode(mode m) {
    m_current_mode = m;
    return m_current_mode;
}

mode Robot::toggle_mode() {
    m_current_mode = increment_mode(m_current_mode);
    return m_current_mode;
}

mode Robot::increment_mode(mode current_mode) {
    int i = static_cast<int> (current_mode);
    return (m_current_mode = (mode) (++i % NUMBER_OF_MODES));
}

driving_direction Robot::toggle_driving_direction() {
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

