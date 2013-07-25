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
: mServer( mServer ),
    mStrand( mServer->getIoService() ),
    mSocket( mServer->getIoService() )
{
}

Connection::~Connection()
{
}
    void Connection::send( const std::vector< std::string > & buffer )
    {
        mStrand.post( boost::bind( &Connection::dispatchSend, shared_from_this(), buffer ) );
    }
    
    void Connection::dispatchSend( std::vector<std::string> buffer )
    {
        bool shouldStartSend = mPendingSends.empty();
        mPendingSends.push_back( buffer );
        if ( shouldStartSend ) {
            startSend();
        }
    }

    void Connection::startSend()
    {
        if ( !mPendingSends.empty() ) {
            boost::asio::async_write( mSocket, boost::asio::buffer( mPendingSends.front() ), mStrand.wrap( boost::bind( &Connection::handleSend, shared_from_this(), boost::asio::placeholders::error, mPendingSends.begin() ) ) );
        }
    }
    
    void Connection::handleSend( const boost::system::error_code &ec, std::list< std::vector< std::string> >::iterator sendIt )
    {
        if ( ec || hasError() || mServer->hasStopped() ) {
            startError( ec );
        } else {
            onSend( *sendIt );
            mPendingSends.erase( sendIt );
            startSend();
        }
    }
    
    //TODO: Change up this function make it a signal
//    void Connection::onSend( const std::vector<std::string> &buffer )
//    {
//        global_stream_lock.lock();
//        std::cout << "[" << __FUNCTION__ << "] " << buffer.size() << " bytes" << std::endl;
//        for (size_t x = 0; x < buffer.size(); ++x) {
//            std::cout << std::hex << std::setfill( '0' ) << std::setw( 2 ) << (int)buffer[ x ] << " ";
//            if ( ( x + 1 ) % 16 == 0) {
//                std::cout << std::endl;
//            }
//        }
//        std::cout << std::endl;
//        global_stream_lock.unlock();
//    }
    
    void Connection::recv( int32_t totalBytes )
    {
        mStrand.post( boost::bind( &Connection::dispatchRecv, shared_from_this(), totalBytes ) );
    }
    
    void Connection::dispatchRecv( int32_t totalBytes )
    {
        bool shouldStartRecv = mPendingRecvs.empty();
        mPendingRecvs.push_back( totalBytes );
        if ( shouldStartRecv ) {
            startRecv( totalBytes );
        }
    }
    
    void Connection::startRecv( int32_t totalBytes )
    {
        if ( totalBytes > 0 ) {
            mRecvBuffer.resize( totalBytes );
            boost::asio::async_read( mSocket, boost::asio::buffer( mRecvBuffer ), mStrand.wrap( boost::bind( &Connection::handleRecv, shared_from_this(), _1, _2 ) ) );
        } else {
            mRecvBuffer.resize( totalBytes );
            boost::asio::async_read( mSocket, boost::asio::buffer( mRecvBuffer ), mStrand.wrap( boost::bind( &Connection::handleRecv, shared_from_this(), _1, _2 ) ) );
        }
    }
    
    void Connection::handleRecv( const boost::system::error_code &ec, int32_t actualBytes )
    {
        if ( ec || hasError() || mServer->hasStopped() ) {
            startError( ec );
        } else {
            mRecvBuffer.resize( actualBytes );
            onRecv( mRecvBuffer );
            mPendingRecvs.pop_front();
            if ( !mPendingRecvs.empty() ) {
                startRecv( mPendingRecvs.front() );
            }
        }
    }
    
    //TODO: Change up this function make it a signal
//    void Connection::onRecv( std::vector< std::string > & buffer )
//    {
//        global_stream_lock.lock();
//        std::cout << "[" << __FUNCTION__ << "] " << buffer.size() << " bytes" << std::endl;
//        for (size_t x = 0; x < buffer.size(); ++x) {
//            std::cout << std::hex << std::setfill( '0' ) << std::setw( 2 ) << (int)buffer[ x ] << " ";
//            if ( (x + 1 ) % 16 == 0) {
//                std::cout << std::endl;
//            }
//        }
//        std::cout << std::endl;
//        global_stream_lock.unlock();
//        
//        // Start the next receive
//        recv();
//        
//        // Echo the data back
//        send( buffer );
//    }
    
    void Connection::startError( const boost::system::error_code & error )
    {
        if( boost::interprocess::ipcdetail::atomic_cas32( &mErrorState, 1, 0 ) == 0 )
        {
            boost::system::error_code ec;
            mSocket.shutdown( boost::asio::ip::tcp::socket::shutdown_both, ec );
            mSocket.close( ec );
            //mTimer.cancel( ec );
            onError( error );
        }
    }
    
    //TODO: Change up this function make it a signal
//    void Connection::onError( const boost::system::error_code &ec )
//    {
//        
//    }
    
    void Connection::disconnect()
    {
        
    }

}
