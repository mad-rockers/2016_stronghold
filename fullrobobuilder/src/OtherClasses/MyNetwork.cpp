#include "MyNetwork.h"

MyNetwork::MyNetwork()
{
	PCD_front.initialize( 65005, "10.29.73.4" );
	PCD_back.initialize( 65006, "10.29.73.5" );

	/*inGoalNet.init(  PCD2RR_GOAL_PORT, PCD_GOAL_AND_LIGHTS_IP );
	outGoalNet.init( RR2PCD_GOAL_PORT, PCD_GOAL_AND_LIGHTS_IP );

	inLightsNet.init(  PCD2RR_LIGHTS_PORT, PCD_GOAL_AND_LIGHTS_IP );
	outLightsNet.init( RR2PCD_LIGHTS_PORT, PCD_GOAL_AND_LIGHTS_IP );

	inBallNet.init(  PCD2RR_BALL_PORT, PCD_BALL_IP );
	outBallNet.init( RR2PCD_BALL_PORT, PCD_BALL_IP );*/
}

void MyNetwork::HandleTrackingAiding()
{
	// read the joystick to see if the driver wants aiding
	//goal_aiding = Robot::oi->goalButton();
	//ball_aiding = Robot::oi->ballButton();
	// look for messages from the PCDuinos
	//ReadNetAndTrack();

	// send the PCD a hint if the operator is moving joystick
	//double vertical_stick = Robot::oi->fwdAxis();
	/*if( operator_joystick.getbutton(1) ) // pitch
	{
		if( abs( vertical_stick ) > 5 )
			SendPCDVerticalHints( MyNetwork::GOAL_VERTICAL_HINT_NEAR );
		else if( abs( vertical_stick ) < 5 )
			SendPCDVerticalHints( MyNetwork::GOAL_VERTICAL_HINT_FAR );
		else
			SendPCDVerticalHints( MyNetwork::GOAL_VERTICAL_HINT_MID );
	}*/
	// send a stop when the user removes his finger
	/*if( ( old_vertical_stick == 1 ) && ( vertical_stick == 0 ))
		SendPCDVerticalHints( MyNetwork::GOAL_VERTICAL_HINT_OFF );

	old_vertical_stick = vertical_stick;

	double horizontal_stick = operator_joystick.getAxis(3).value;
	if( operator_joystick.getbutton(2) ) // yaw
	{
		if( abs( horizontal_stick ) < 5 )
			SendPCDVerticalHints( MyNetwork::GOAL_HORIZONTAL_HINT_LEFT );
		else if( abs( horizontal_stick ) > 5 )
			SendPCDVerticalHints( MyNetwork::GOAL_HORIZONTAL_HINT_RIGHT );
		else
			SendPCDVerticalHints( MyNetwork::GOAL_HORIZONTAL_HINT_MID );
	}
	// send a stop when the user removes his finger
	if( ( old_horizontal_stick == 1 ) && ( horizontal_stick == 0 ))
		SendPCDVerticalHints( MyNetwork::GOAL_HORIZONTAL_HINT_OFF );

	old_horizontal_stick = horizontal_stick;
	*/
}


void MyNetwork::SendPCDVerticalHints( int hint )
{
	// send the tracker a hint whether the goal is hi, mid, low
	unsigned char buffer[5];
	buffer[0] = hint;
	PCD_front.send( buffer, buff_length );
}

void MyNetwork::ReadNetAndTrack()
{
	unsigned char buffer[32];

	if (oldBallButton != Robot::oi->ballButton()){
		if (Robot::oi->ballButton()==1){
			buffer[0] = TURN_ON_BALL_AIDING;
		}
		else {
			buffer[0] = TURN_OFF_BALL_AIDING;
		}
		PCD_back.send( buffer, buff_length );
	}
	if (oldGoalButton != Robot::oi->goalButton()){
		if (Robot::oi->goalButton()==1){
			buffer[0] = TURN_ON_GOAL_AIDING;
		}
		else {
			buffer[0] = TURN_OFF_GOAL_AIDING;
		}
		PCD_front.send( buffer, buff_length );
	}
	oldBallButton = Robot::oi->ballButton();
	oldGoalButton = Robot::oi->goalButton();

	SmartDashboard::PutBoolean("ball aid button",oldBallButton );
	SmartDashboard::PutBoolean("goal aid button",oldGoalButton );
	SmartDashboard::PutNumber("aid buffer",buffer[0] );

	// look for ball and goal commands for the chassis heading

	struct message_str incoming_data;
	int len_msg = PCD_front.receive( buffer );
	if (len_msg > 0 && oldGoalButton){
		memcpy( &header, &buffer[0], 1);
		memcpy( &x_track_error, &buffer[2], 2);//in pixels
		memcpy( &y_track_error, &buffer[4], 2);
		SmartDashboard::PutNumber("Front Message Length",len_msg );
		SmartDashboard::PutNumber("Front Header",header );
		SmartDashboard::PutNumber("Front X Error",x_track_error );
		if( header == GOAL_INCOMING_COMMAND){
			Robot::tankDriveTrain->CameraPID(x_track_error);
		}
	}
	else {
		SmartDashboard::PutNumber("Front Message Length",1000);
		SmartDashboard::PutNumber("Front Header",1000 );

	}

	len_msg = PCD_back.receive( buffer );
	if (len_msg > 0 && oldBallButton){
		memcpy( &header, &buffer[0], 1);
		memcpy( &x_track_error, &buffer[2], 2);//in pixels
		memcpy( &y_track_error, &buffer[4], 2);
		SmartDashboard::PutNumber("Back Message Length",len_msg );
		SmartDashboard::PutNumber("Back Header",header );
		SmartDashboard::PutNumber("Back X Error",x_track_error );
		if(header == BALL_INCOMING_COMMAND ){
			if (x_track_error > fabs(Robot::tankDriveTrain->INTEGRATED_TURN_THRESHOLD)){
				Robot::tankDriveTrain->CameraPID(x_track_error);
			}
		}
	}
	else {
		SmartDashboard::PutNumber("Back Message Length",1000);
		SmartDashboard::PutNumber("Back Header",1000 );
	}
}

void MyNetwork::InitTeleop()
{
	// tell the Goal PCD that we are done with the tracker commands
	unsigned char buffer[5];
	buffer[0] = TURN_OFF_GOAL_AIDING;

	PCD_front.send( buffer, buff_length );
}

void MyNetwork::SendPCDFront(unsigned char *buffer, unsigned int size){
	PCD_front.send( buffer, size );
}

void MyNetwork::SendPCDBack(unsigned char *buffer, unsigned int size){
	PCD_back.send( buffer, size );
}

