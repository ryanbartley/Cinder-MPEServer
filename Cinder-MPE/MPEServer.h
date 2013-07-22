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

namespace cinder {
    namespace mpe {
        
        class MPEServer;
        typedef boost::shared_ptr< MPEServer > MPEServerRef;
        
        class MPEServer : public TCP::Server {
          public:
            
            explicit MPEServer( const std::string& address, const std::string& port,
                               std::size_t threadPoolSize, int numClients = 3 );
            
            static MPEServerRef create( const std::string& address, const std::string& port,
                                       std::size_t threadPoolSize, int numClients = 3 )
            { return MPEServerRef( new MPEServer( address, port, threadPoolSize, numClients ) ); }
            
            void broadcast();
            void sendUnique( int clientId );
            

          private:
            TCP::ServerRef  mServer;
            int             expectedConnects;
            
        };
        
    }
}
