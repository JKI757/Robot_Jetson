

#include <Servo.h>
#include <L298N.h>

#define DEBUG

Servo steeringServo; 

int steeringPin = 15;  

int in1pin=4;
int in2pin=3;
int dcmotorpwmpin=5;
L298N driveMotor(dcmotorpwmpin, in1pin, in2pin );

bool serialDataReady=false;
int pos = 0;    // variable to store the servo position
int currentSpeed = 0;
int currentSteeringAngle = 0;

int max_steering_input = 32768;
int max_right_steering_angle = 60;
int max_left_steering_angle = 150;
int max_right_steering_microseconds = 1100;
int max_left_steering_microseconds = 1900;

int center_steer = (max_left_steering_angle - max_right_steering_angle)/2 + max_right_steering_angle;

int max_speed = 35;
int min_speed = 20;

uint8_t incomingByte = 0x0;
bool commandReceived = false;

enum command_t{DRIVE, TURNLEFT, TURNRIGHT, DIRECTION, BRAKE, TURN};

command_t commandType;
uint8_t commandData = 0x0;

L298N::Direction current_driving_direction = L298N::FORWARD;

void setup() {
  Serial1.begin(9600);

  TCCR0B = TCCR0B & B11111000 | B00000101;
  steeringServo.attach(steeringPin);//, 900, 2100);  // attaches the servo on pin 9 to the servo object

  steeringServo.write(center_steer); //center steering -- 1000-2000 nominal, 1000 is right, 2000 left
//  steeringServo.writeMicroseconds(1000);
  driveMotor.setSpeed(0);
};
#ifdef DEBUG
  void dprint(uint8_t d){
    Serial1.print(d);
    Serial1.flush();
  }
  void dprintln(uint8_t d){
    Serial1.println(d);
    Serial1.flush();
  }
  void dprintln(char x[]){
    Serial1.println(x);
    Serial1.flush();
  }  
  void dprint(char x[]){
    Serial1.print(x);
    Serial1.flush();
  }
#endif


void serialEvent(){
  while (Serial1.available()){
    incomingByte = Serial1.read();
    #ifdef DEBUG
      dprint("serial data received: ");
      dprintln(incomingByte);
    #endif
    if (!commandReceived){
      switch (incomingByte){
      
        case 0x0A:{
          commandType=BRAKE;
          commandReceived=true;
          //Serial1.flush();
          #ifdef DEBUG
            dprintln("Brake command received");
          #endif
        };break;
        case 0x0B:{
          commandType=DRIVE;
          commandReceived=true;
          //Serial1.flush();
          #ifdef DEBUG
            dprintln("Drive command received");
          #endif          
        };break;
        case 0x0C:{
          commandType=TURNLEFT;
          commandReceived=true;
          //Serial1.flush();
          #ifdef DEBUG
            dprintln("Turn Left Command Received");
          #endif          
        };break;
        case 0x0E:{
          commandType=TURNRIGHT;
          commandReceived=true;
          //Serial1.flush();
          #ifdef DEBUG
            dprintln("Turn right command received");
          #endif          
        };break;
        case 0x0F:{
          commandType=DIRECTION;
          commandReceived=true;
          //Serial1.flush();
          #ifdef DEBUG
            dprintln("direction command received");
          #endif          
        };break;
        default:{
          ;
        };break;
      };
    }
    else{
      commandData=incomingByte;
          #ifdef DEBUG
            dprint("data received: ");
            dprintln(incomingByte);
          #endif      
      serialDataReady=true;
      commandReceived=false;
    }
  }
}

int map_steering_angle(int val){
  int microseconds = 0;

  microseconds = map(val, -max_steering_input, max_steering_input, max_left_steering_angle, max_right_steering_angle);
  //the way this is physically installed, the servo is centered 50 -150 is close to what it needs to do.
  
  return microseconds;
}
void turn_left(int angle){

 steeringServo.writeMicroseconds(map(angle, 60,150 , 1150,2000));

}

void turn_right(int angle){

 steeringServo.writeMicroseconds(map(angle, 60,150 , 1150,2000));

};

void drive(uint8_t speed){
    driveMotor.setSpeed(speed);
    driveMotor.run(current_driving_direction);
}
void apply_brakes(){
  driveMotor.stop();
}
void set_drive_direction(L298N::Direction driveDirection){
  if (driveDirection != current_driving_direction){
    apply_brakes();
    current_driving_direction = driveDirection;
  }
}



void turn_center(){
  steeringServo.write(center_steer);
}

void turn(int angle){
  if (angle == 0){
    turn_center();
  }
  else{

  steeringServo.write(angle);
  #ifdef DEBUG
          dprint("Turning: ");
      dprintln(angle);

  #endif
  }
}


void loop() {

  if (serialDataReady){
    
    switch (commandType){
      case BRAKE:{
        apply_brakes();
      };break;
      case DRIVE:{
        drive(commandData);
      };break;
      case TURN:{
        turn(commandData);
      }
      case TURNLEFT:{
        turn_left(commandData);
      };break;
      case TURNRIGHT:{
        turn_right(commandData);
      };break;
      case DIRECTION:{
        if (commandData == 0){
          set_drive_direction(L298N::FORWARD);
        }
        else{
          set_drive_direction(L298N::BACKWARD);
        }
      };break;
      
    };

    serialDataReady=false;
    commandData=0x0;
    commandReceived=false;
  }


  #ifdef DEBUG
    dprintln("tick");
   #endif

}