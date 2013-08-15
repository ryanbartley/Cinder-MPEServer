//
//  MPEMessage.h
//  CinderTCPServer
//
//  Created by Ryan Bartley on 7/25/13.
//
//

#pragma once

#include "Message.h"
#include <vector>

namespace MPE {
    
const std::string CONNECT_SYNCHRONOUS   = "S";
const std::string DONE_RENDERING        = "D";
const std::string DATA_MESSAGE          = "T";
const std::string NEXT_FRAME            = "G";
const std::string CONNECT_ASYNCHRONOUS  = "A";
const std::string RESET_ALL             = "R";
const std::string PAUSE_ALL             = "P";
const std::string SEPERATOR             = "|";
const std::string DELIMITER             = "\n";
const std::string DATA_SEPERATOR        = ",";
    
class MPEMessage;
typedef std::shared_ptr< MPEMessage > MPEMessageRef;
    
class MPEMessage : public TCP::Message {
public:
    explicit MPEMessage( const std::string& type, const int &myId );
    explicit MPEMessage( const std::string& fullMessage );
    inline static MPEMessageRef createEmptyMessage( const std::string& type, const int &myId )
    { return MPEMessageRef( new MPEMessage( type, myId ) ); }
    inline static MPEMessageRef createFinishedMessage( const std::string& fullMessage )
    { return MPEMessageRef( new MPEMessage( fullMessage ) ); }
    
    TCP::MessageRef get();
    
    void insertData( const std::string &data );
    
    void setSpceificRecipient( int clientId );
    
private:
    MPEMessage();
    std::string message;
    int         myId;
    std::vector< std::string > data;
    int         specificClient;
    
};
    
}
