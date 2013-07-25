//
//  MPEServer.h
//  CinderTCPServer
//
//  Created by Ryan Bartley on 7/21/13.
//
//

#pragma once

#include "TCPServer.h"
#include "MPEProtocol.hpp"

namespace MPE {
        
class MPEServer;
typedef std::shared_ptr< MPEServer > MPEServerRef;

class MPEServer : std::enable_shared_from_this< MPEServer >{
  public:
    
    explicit MPEServer( const std::string& address, const std::string& port,
                       std::size_t threadPoolSize, int numClients = 3 );
    
    static MPEServerRef create( const std::string& address, const std::string& port,
                               std::size_t threadPoolSize, int numClients = 3 )
    { return MPEServerRef( new MPEServer( address, port, threadPoolSize, numClients ) ); }
    
    void broadcast();
    void sendUnique( int clientId );
    
    void onAccept( const TCP::ConnectRef clientRef, int clientId );
    

  private:
    TCP::ServerRef  mServer;
    int             expectedConnects;
    bool            allClientsReady;
    bool            allClientsConnected;
    
};
    
}
