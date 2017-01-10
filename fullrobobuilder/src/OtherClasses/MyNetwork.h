
#ifndef MYNETWORK_H
#define MYNETWORK_H

#include "UdpSocket2016.h" // TEC
//#include <Joystick.h> // TEC
#include "Track.h"
#include "../Robot.h"


class MyNetwork
{
public:
	MyNetwork();
	void InitTeleop();
	void ReadNetAndTrack(); // from teleop
	void SendPCDVerticalHints( int hint );
	void HandleTrackingAiding();
	void SendPCDFront(unsigned char *buffer, unsigned int size);
	void SendPCDBack(unsigned char *buffer, unsigned int size);

	bool oldBallButton = 0;
	bool oldGoalButton = 0;

	class UdpSocket PCD_front;
	class UdpSocket PCD_back;
	int buff_length = 1;

	/*class UdpSocket  inBallNet, outBallNet;
	class UdpSocket  inGoalNet, outGoalNet;
	class UdpSocket  inLightsNet, outLightsNet;*/

	bool goal_aiding, ball_aiding;
	int old_vertical_stick;
	int old_horizontal_stick;

	signed short x_track_error;
	signed short y_track_error;
	int header;

};

#endif
