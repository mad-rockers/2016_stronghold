#ifndef TRACK_H
#define TRACK_H

//#define GOAL_IMAGE_HEADER 0x57
//#define BALL_IMAGE_HEADER 0x62

//#define GOAL_LAPTOP_PORT 65000
//#define BALL_LAPTOP_PORT 65001

/*
#define GOAL_ERROR_PORT 65005
#define GOAL_ERROR_HEADER  0x33
#define LIGHT_ERROR_PORT 65005
#define LIGHT_ERROR_HEADER  0x35
#define BALL_ERROR_PORT 65005
#define BALL_ERROR_HEADER  0x37
*/

#define PCD_GOAL_AND_LIGHTS_IP "10.29.73.255"
#define PCD_BALL_IP "10.29.73.255"
#define LAPTOP_DESTINATION_IP "10.29.73.255"

/*
#define GOAL_VERTICAL_HINT_NEAR 0x44
#define GOAL_VERTICAL_HINT_MID 0x44
#define GOAL_VERTICAL_HINT_FAR 0x44
#define GOAL_VERTICAL_HINT_OFF 0x44

#define GOAL_HORIZONTAL_HINT_LEFT 0x44
#define GOAL_HORIZONTAL_HINT_RIGHT 0x44
#define GOAL_HORIZONTAL_HINT_MID 0x44
#define GOAL_HORIZONTAL_HINT_OFF 0x44
*/

#define TURN_OFF_GOAL_AIDING 0x50
#define TURN_ON_GOAL_AIDING  0x55

#define TURN_ON_BALL_AIDING  0x25
#define TURN_OFF_BALL_AIDING 0x20

#define TURN_ON_VERT_LIGHTS_AIDING  0x45
#define TURN_OFF_VERT_LIGHTS_AIDING 0x40

#define PCD2RR_GOAL_PORT 65005
#define RR2PCD_GOAL_PORT 65005
#define PCD2RR_BALL_PORT 65005
#define RR2PCD_BALL_PORT 65005
#define PCD2RR_LIGHTS_PORT 65005
#define RR2PCD_LIGHTS_PORT 65005

#define GOAL_INCOMING_COMMAND 0x33
#define BALL_INCOMING_COMMAND 0x37
#define LIGHTS_INCOMING_COMMAND 0x35

/*
const int screen_width = 640;
const int screen_height = 480;
const int screen_widthO2 = screen_width/2;
const int screen_width2O3 = 2*screen_width/3;
const int screen_widthO3 = screen_width/3;
*/
#define COMMAND_MESSAGE_SIZE 6
//const double TURN_GAIN = .0002; // pixels per motor percent

struct message_str {
        char header;
        char pad;
        short error;
        unsigned short row;
};


//const unsigned int MAX_ROW_TO_SHOOT = 250; // row tells us distance
//const unsigned int MIN_ROW_TO_SHOOT = 300;
//const unsigned int CAMERA_HEIGHT = 480;
//const unsigned int CAMERA_WIDTH= 640;

#endif


