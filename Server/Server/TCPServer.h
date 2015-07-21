#pragma once
#ifndef TCPSERVER_H
#define TCPSERVER_H

/*
 * TCP Server handles tcp packets. YOLO
 * reads packets from users who will:
 * - send new files to the cloud
 * - check and retrieve a list of existing file(s) in his directory
 * - 
*/

namespace OpenClouds
{
	class TCPServer
	{
	public:
		static TCPServer& Inst();

	private:
		TCPServer();// Private so that it can  not be called
		void operator=(TCPServer const&); // override assignment operator 
	};
	static TCPServer& Server = TCPServer::Inst();
}


#endif