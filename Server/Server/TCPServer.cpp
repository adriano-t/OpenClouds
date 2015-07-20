#include "TCPServer.h"
namespace OpenClouds
{
	TCPServer& TCPServer::Inst(){
		static TCPServer instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	}
}