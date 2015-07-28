#include "TCPServer.h"
namespace OpenClouds
{
	TCPServer& TCPServer::Inst()
	{
		static TCPServer instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	}

	void TCPServer::Start()
	{
		sendBuffer = new Buffer(1024, 32);
		recvBuffer = new Buffer(1024, 32);
	}
}