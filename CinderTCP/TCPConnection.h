//
//  TCPConnection.h
//  CinderTCPServer
//
//  Created by Ryan Bartley on 7/20/13.
//
//

#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>


namespace cinder {
    namespace TCP {
        
        class Server;
        typedef boost::shared_ptr< Server > ServerRef;
        class Connection;
        typedef boost::shared_ptr< Connection > ConnectRef;
        
        class Connection
        :   public boost::enable_shared_from_this< Connection >,
            private boost::noncopyable
        {
                
          public:
            explicit Connection( ServerRef mServer );
            static ConnectRef create( ServerRef mServer )
            { return ConnectRef( new Connection( mServer ) ); }
            
            
            
            boost::asio::ip::tcp::socket&   getSocket() { return mSocket; }
            boost::asio::strand&            getStrand() { return mStrand; }
            
            void start();
          private:
            virtual void handleRead( const boost::system::error_code& e, std::size_t bytesTransferred );
            virtual void handleWrite( const boost::system::error_code& e );
            virtual void handleConnect( const boost::system::error_code& e );
          
            
          protected:
            
          private:
            boost::asio::io_service::strand     mStrand;
            boost::asio::ip::tcp::socket        mSocket;
            boost::asio::deadline_timer         mTimer;
            boost::posix_time::ptime            mLastTime;
            std::vector< uint8_t >              mRecvBuffer;
            std::list< int32_t >                mPendingRecvs;
            std::list< std::vector< uint8_t > > mPendingSends;
            int32_t                             mReceiveBufferSize;
            int32_t                             mTimerInterval;
            
        };
        
    }
}
