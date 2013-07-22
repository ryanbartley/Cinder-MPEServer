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

namespace cinder {
    namespace TCP {
        
        Connection::Connection( ServerRef mServer )
        : mStrand( mServer->getIoService() ),
            mSocket( mServer->getIoService() ),
            mTimer( mServer->getIoService() ),
            mLastTime()
            
        {
        }
        
        void Connection::start()
        {
            mSocket.async_read_some(boost::asio::buffer(mRecvBuffer), mStrand.wrap( boost::bind(&Connection::handleRead, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)));
        }
        
        void Connection::handleRead( const boost::system::error_code &e, std::size_t bytesTransferred )
        {
            if ( !e ) {
                boost::tribool result;
                std::cout << "I am reading" << std::endl;
            }
        }
        
    }
}