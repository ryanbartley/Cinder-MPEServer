//
//  TCPConnection.cpp
//  CinderTCPServer
//
//  Created by Ryan Bartley on 7/20/13.
//
//

#include "TCPConnection.h"
#include "TCPServer.h"
#include <boost/bind.hpp>
#include <vector>

namespace TCP {
    
Connection::Connection( ServerRef mServer )
: mStrand( mServer->getIoService() ),
    mSocket( mServer->getIoService() ),
    mTimer( mServer->getIoService() ),
    mLastTime()
{
}



}
