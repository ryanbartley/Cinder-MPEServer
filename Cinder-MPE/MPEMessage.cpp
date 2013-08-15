//
//  MPEMessage.cpp
//  CinderTCPServer
//
//  Created by Ryan Bartley on 7/25/13.
//
//

#include "MPEMessage.h"

namespace MPE {
    
MPEMessage::MPEMessage( const std::string& type, const int &myId )
: TCP::Message(), message(type), myId(myId), specificClient(-1)
{
    
}

MPEMessage::MPEMessage( const std::string& fullMessage )
: TCP::Message(), message(fullMessage), specificClient(-1)
{
    
}
    
TCP::MessageRef MPEMessage::get()
{
    message += SEPERATOR;
    
    if (specificClient >= 0) {
        message += specificClient;
        message += DELIMITER;
    }
    
    for ( auto dataIt = data.begin(); dataIt != data.end() ; ++dataIt ) {
        message += *dataIt;
        message += DATA_SEPERATOR;
    }
    
    message += DELIMITER;
    
     message.find_first_of(DELIMITER);
    
    return shared_from_this();
}
    
void MPEMessage::insertData( const std::string& data )
{
    this->data.push_back( data );
}
    
void MPEMessage::setSpceificRecipient( int clientId )
{
    specificClient = clientId;
}
    
}