#pragma once


#include "Buffer.h"
#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/select.h>

#define INVALID_SOCKET (~0)
#define SOCKET_ERROR (-1)
#endif


/*
* TCP Server handles tcp packets. YOLO
* reads packets from users who will:
* - send new files to the cloud
* - check and retrieve a list of existing file(s) in his directory
* -
*/

namespace OpenClouds
{

	typedef unsigned int Socket;


	class Client
	{
	public:
		Socket socket;
		struct sockaddr_in sockaddr;
		unsigned short port;
		Buffer* buffer;


		Client();
		~Client();
		

	};

	class TCPServer
	{
	public:
		static TCPServer& Inst();
		
		void Start();

		Buffer* sendBuffer;
		Buffer* recvBuffer;

	private:
		TCPServer(){};// Private: can not be called
		void operator=(TCPServer const&); // override assignment operator 
	};

	// static instance of the TCPServer
	static TCPServer& Server = TCPServer::Inst();





}

