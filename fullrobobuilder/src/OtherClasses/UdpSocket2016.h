#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <arpa/inet.h> //for struct sockaddr_in
#include <string>
#include <memory.h>


const unsigned int UDP_BUFFER_SIZE = 2048;

class UdpSocket {

public:
  UdpSocket();
  ~UdpSocket();
  void initialize(int iPort, std::string strAddress="10.29.73.3");
  void send(unsigned char * pBuffer, unsigned int length);
  int receive(unsigned char* pBuffer);

private:
  int m_iPort;
  int m_iSocketId;
  std::string m_strOutAddress;
  struct sockaddr_in m_OutAddress;
};

 
#endif

