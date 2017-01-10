#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <fcntl.h>

#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "UdpSocket2016.h"
#include "../Robot.h"

using namespace std;

UdpSocket::UdpSocket()
{
	m_iPort = 4062;
	m_strOutAddress = "127.0.0.1";
}

UdpSocket::~UdpSocket()
{
	close(m_iSocketId);
}

void UdpSocket::initialize(int iPort, string strOutAddress)
{
	//SmartDashboard::PutString("udp socket initialized", strOutAddress.c_str());

	m_iPort = iPort;
	m_strOutAddress = strOutAddress;

	// Create the UDP socket
	if ((m_iSocketId = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		perror("Failed to create socket");
		exit(0);
	}
	/* Linux */
      //int flags;
      //fcntl( m_iSocketId, F_SETFL, O_NONBLOCK );

    struct sockaddr_in PCDconnection;

      // Construct the server sockaddr_in structure
    memset(&PCDconnection, 0, sizeof(PCDconnection)); // Clear struct
    PCDconnection.sin_family = AF_INET; // Internet/IP
    PCDconnection.sin_addr.s_addr =  (INADDR_ANY); // Any IP address
    PCDconnection.sin_port = htons(m_iPort); // server port

    // Bind the socket */
    int serverlen = sizeof(PCDconnection);
    if (bind(m_iSocketId, (struct sockaddr *) &PCDconnection, serverlen) == 0) {
        SmartDashboard::PutBoolean("bind error",false); }
    else{
        SmartDashboard::PutBoolean("bind error",true); }

    // Construct the Out sockaddr_in structure
    memset(&m_OutAddress, 0, sizeof(m_OutAddress)); // Clear struct
    m_OutAddress.sin_family = AF_INET; // Internet/IP
    m_OutAddress.sin_port = htons(m_iPort); // Out port

    inet_aton(m_strOutAddress.c_str(), &m_OutAddress.sin_addr); // IP address

}

void UdpSocket::send(unsigned char* pBuffer, unsigned int uiLength)
{
     int iMessageSize;
     SmartDashboard::PutString("udp send", m_strOutAddress.c_str());

    // Send the message
    iMessageSize = sendto(m_iSocketId, pBuffer, uiLength, 0,
        (struct sockaddr *) &m_OutAddress, sizeof(sockaddr_in));

    if (iMessageSize == -1)
    {
    	perror("SOCKET ERROR: sentto() failure in UdpSocket::send()");
    	//exit(0);
    }
}

int UdpSocket::receive(unsigned char* pBuffer)
{
	int iReceivedBytes = 0;
	struct sockaddr_in m_InAddress; // local bc we already know how to send it back
	unsigned int uiInLength = sizeof(sockaddr_in);

	iReceivedBytes = recvfrom(m_iSocketId, pBuffer, UDP_BUFFER_SIZE, MSG_DONTWAIT,
			(struct sockaddr *) &m_InAddress, &uiInLength);

  //if (iReceivedBytes == -1)
  //{
  //  	perror("SOCKET ERROR: recvfrom() Failed to receive message in UdpSocket::receive()");
  //  	exit(0);
  //}

	return iReceivedBytes;
}

