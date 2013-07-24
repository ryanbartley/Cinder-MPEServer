//
//  MPEServer.cpp
//  CinderTCPServer
//
//  Created by Ryan Bartley on 7/21/13.
//
//

#include "MPEServer.h"

namespace mpe {
    
MPEServer::MPEServer(const std::string& address, const std::string& port,
                     std::size_t threadPoolSize, int numClients )
: TCP::Server( address, port, threadPoolSize),
    expectedConnects(numClients)
{
}

void MPEServer::broadcast()
{
    // Create the 
    if ( allClientsReady ) {
        for( auto conns = ConnectedClients.begin(); conns != ConnectedClients.end(); ++conns)
            conns->second->write();
    }
    
    //then broadcast again
}


}

