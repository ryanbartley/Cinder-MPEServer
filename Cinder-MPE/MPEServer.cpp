//
//  MPEServer.cpp
//  CinderTCPServer
//
//  Created by Ryan Bartley on 7/21/13.
//
//

#include "MPEServer.h"

namespace MPE {
    
MPEServer::MPEServer(const std::string& address, const std::string& port,
                     std::size_t threadPoolSize, int numClients )
: mServer( TCP::Server::create(address, port, threadPoolSize) ),
    expectedConnects(numClients),
    allClientsReady(false)
{
    mServer->connectAcceptHandler( &MPEServer::onAccept, this );
    mServer->connectTimerEvent( &MPEServer::onTimer, this );
    
}

void MPEServer::broadcast()
{
    // Create the 
    if ( allClientsReady ) {
        for( auto conns = mServer->getConnectedClients().begin(); conns != mServer->getConnectedClients().end(); ++conns)
            conns->second->send( );
    }
    
    //then broadcast again
}
    
void MPEServer::sendUnique(int clientId)
{
    auto uniqueConn = mServer->getConnectedClients().find(clientId);
    uniqueConn->second->send( );
}

void MPEServer::onAccept(const TCP::ConnectRef clientRef, int clientId)
{
    
}

}

