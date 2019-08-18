#include <wiringPiI2C.h>
#include <stdio.h>

#define word    unsigned short

#define ADAFRUIT_MOTORHAT       0x60

#define PWM_M1_PWM      8
#define PWM_M1_IN2      9
#define PWM_M1_IN1      10
#define PWM_M2_PWM      13
#define PWM_M2_IN2      12
#define PWM_M2_IN1      11
#define PWM_M3_PWM      2
#define PWM_M3_IN2      3
#define PWM_M3_IN1      4
#define PWM_M4_PWM      7
#define PWM_M4_IN2      6
#define PWM_M4_IN1      5

#define PWM_FREQUENCY   1600.0
#define PWM_PRESCALE    0xFE

#define PWM_MODE1       0x00
#define PWM_MODE2       0x01
#define PWM_LED0_ON_L   0x06
#define PWM_LED0_ON_H   0x07
#define PWM_LED0_OFF_L  0x08
#define PWM_LED0_OFF_H  0x09

#define PWM_RESTART     0x80
#define PWM_SLEEP       0x10
#define PWM_ALLCALL     0x01
#define PWM_INVRT       0x10
#define PWM_OUTDRV      0x04

#define PWM_ALL_LED_ON_L        0xFA
#define PWM_ALL_LED_ON_H        0xFB
#define PWM_ALL_LED_OFF_L       0xFC
#define PWM_ALL_LED_OFF_H       0xFD

#define MOTOR_FORWARD   1
#define MOTOR_BACK      2
#define MOTOR_BRAKE     3
#define MOTOR_RELEASE   4

void setAllPWM(word i2c, word on, word off){
        wiringPiI2CWriteReg8(i2c, PWM_ALL_LED_ON_L, on & 0xFF);
        wiringPiI2CWriteReg8(i2c, PWM_ALL_LED_ON_H, on >> 8);
        wiringPiI2CWriteReg8(i2c, PWM_ALL_LED_OFF_L, off & 0xFF);
        wiringPiI2CWriteReg8(i2c, PWM_ALL_LED_OFF_H, off >> 8);
}

void setPWM(word i2c, word pin, word on, word off){
        wiringPiI2CWriteReg8(i2c, PWM_LED0_ON_L + 4 * pin, on & 0xFF);
        wiringPiI2CWriteReg8(i2c, PWM_LED0_ON_H + 4 * pin, on >> 8);
        wiringPiI2CWriteReg8(i2c, PWM_LED0_OFF_L + 4 * pin, off & 0xFF);
        wiringPiI2CWriteReg8(i2c, PWM_LED0_OFF_H + 4 * pin, off >> 8);
}

void setPin(word i2c, word pin, word value){
        if(pin < 0 || pin > 15){
                printf("PWM pin must be between 0 and 15 inclusive.  Received '%d'\n", pin);
                return;
        }

        switch(value){
                case 0:
                        setPWM(i2c, pin, 0, 4096);
                        break;
                case 1:
                        setPWM(i2c, pin, 4096, 0);
                        break;
                default:
                        printf("PWM pin value must be 0 or 1.  Received '%d'\n", pin);
                        return;
        }
}

void runMotor(word i2c, word motor, word command){
        word in1, in2;

        switch(motor){
                case 1:
                        in1 = PWM_M1_IN1;
                        in2 = PWM_M1_IN2;
                        break;
                case 2:
                        in1 = PWM_M2_IN1;
                        in2 = PWM_M2_IN2;
                        break;
                case 3:
                        in1 = PWM_M3_IN1;
                        in2 = PWM_M3_IN2;
                        break;
                case 4:
                        in1 = PWM_M4_IN1;
                        in2 = PWM_M4_IN2;
                        break;
                default:
                        printf("Invalid motor number '%d'\n", motor);
                        return;
        }

        switch(command){
                case MOTOR_FORWARD:
                        setPin(i2c, in2, 0);
                        setPin(i2c, in1, 1);
                        break;
                case MOTOR_BACK:
                        setPin(i2c, in1, 0);
                        setPin(i2c, in2, 1);
                        break;
                case MOTOR_RELEASE:
                        setPin(i2c, in1, 0);
                        setPin(i2c, in2, 0);
                        break;
                default:
                        printf("Unsupported command '%d'\n", command);
                        return;
        }
}

void setSpeed(word i2c, word motor, word speed){
        if(speed < 0 || speed > 255){
                printf("Speed must be between 0 and 255 inclusive.  Received '%d'\n", speed);
                return;
        }

        word pwm;
        switch(motor){
                case 1:
                        pwm = PWM_M1_PWM;
                        break;
                case 2:
                        pwm = PWM_M2_PWM;
                        break;
                case 3:
                        pwm = PWM_M3_PWM;
                        break;
                case 4:
                        pwm = PWM_M4_PWM;
                        break;
                default:
                        printf("Unsupported motor '%s'\n", motor);
                        break;
        }
        setPWM(i2c, pwm, 0, speed * 16);
}

word init(){
        //Setup I2C
        word i2c = wiringPiI2CSetup(ADAFRUIT_MOTORHAT);

        //Setup PWM
        setAllPWM(i2c, 0, 0);
        wiringPiI2CWriteReg8(i2c, PWM_MODE2, PWM_OUTDRV);
        wiringPiI2CWriteReg8(i2c, PWM_MODE1, PWM_ALLCALL);
        delay(5);
        word mode1 = wiringPiI2CReadReg8(i2c, PWM_MODE1) & ~PWM_SLEEP;
        wiringPiI2CWriteReg8(i2c, PWM_MODE1, mode1);
        delay(5);

        //Set PWM frequency
        word prescale = (int)(25000000.0 / 4096.0 / PWM_FREQUENCY - 1.0);
        word oldmode = wiringPiI2CReadReg8(i2c, PWM_MODE1);
        word newmode = oldmode & 0x7F | 0x10;
        wiringPiI2CWriteReg8(i2c, PWM_MODE1, newmode);
        wiringPiI2CWriteReg8(i2c, PWM_PRESCALE, prescale);
        wiringPiI2CWriteReg8(i2c, PWM_MODE1, oldmode);
        delay(5);
        wiringPiI2CWriteReg8(i2c, PWM_MODE1, oldmode | 0x80);

        return i2c;
}

void initMotor(word i2c, word motor){
        runMotor(i2c, motor, MOTOR_RELEASE);
        setSpeed(i2c, motor, 150);
        runMotor(i2c, motor, MOTOR_FORWARD);
        runMotor(i2c, motor, MOTOR_RELEASE);
}

void main(){
        word i2c = init();
        word motor = 3;

        initMotor(i2c, motor);
        runMotor(i2c, motor, MOTOR_FORWARD);
        setSpeed(i2c, motor, 255);
        delay(5000);

        //TURN OFF MOTOR
        runMotor(i2c, motor, MOTOR_RELEASE);
}
