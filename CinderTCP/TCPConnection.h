//
//  TCPConnection.h
//  CinderTCPServer
//
//  Created by Ryan Bartley on 7/20/13.
//
//

#pragma once

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/interprocess/detail/atomic.hpp>

#include "Message.h"


namespace TCP {
        
class Server;
typedef std::shared_ptr< Server > ServerRef;
class Connection;
typedef std::shared_ptr< Connection > ConnectRef;

class Connection
:   public std::enable_shared_from_this< Connection >,
    private boost::noncopyable
{
        
  public:
    explicit Connection( ServerRef mServer );
    static ConnectRef create( ServerRef mServer )
    { return ConnectRef( new Connection( mServer ) ); }
    ~Connection();
    
    // Posts data to be sent to the connection.
    void send( const std::vector< std::string > & buffer );
    
    // Posts a recv for the connection to process. If total_bytes is 0, then
	// as many bytes as possible up to GetReceiveBufferSize() will be
	// waited for. If Recv is not 0, then the connection will wait for exactly
	// total_bytes before invoking OnRecv.
    void recv( int32_t totalBytes = 0 );
    
    // Posts an asynchronous disconnect event for the object to process.
	void disconnect();
    
    // Starts an a/synchronous connect.
	void connect( const std::string & host, uint16_t port );
    
    boost::asio::ip::tcp::socket&   getSocket() { return mSocket; }
    boost::asio::strand&            getStrand() { return mStrand; }
    
    // Sets the application specific receive buffer size used. For stream
	// based protocols such as HTTP, you want this to be pretty large, like
	// 64kb. For packet based protocols, then it will be much smaller,
	// usually 512b - 8kb depending on the protocol. The default value is
	// 4kb.
	void setReceiveBufferSize( int32_t size ) { mReceiveBufferSize = size; }
    
	// Returns the size of the receive buffer size of the current object.
	int32_t getReceiveBufferSize() const { return mReceiveBufferSize; }
    
	// Returns true if this object has an error associated with it.
	bool hasError();
    
  private:
    Connection( const Connection & rhs );
	Connection & operator =( const Connection & rhs );
    
    void handleConnect( const boost::system::error_code & ec );
	// Called when the connection has successfully connected to the remote
	// host.
	void onConnect( const std::string & host, uint16_t port );
    
    // send (from public) calls dispatchSend which calls handleSend
    // startSend calls handleSend from handle (this is the loop)
    // handleSend calls onSend with the actual buffer string created
    //    then calls startsend again
    // onSend is the place available to create your functions to process
    //    received data
    void dispatchSend( std::vector< std::string > buffer );
	void startSend();
    void handleSend( const boost::system::error_code & ec,  std::list< std::vector< std::string > >::iterator sendIt );
    // Called when data has been sent by the connection.
	void onSend( const MessageRef & buffer );
    
    
    void dispatchRecv( int32_t totalBytes );
	void startRecv( int32_t totalBytes );
    void handleRecv( const boost::system::error_code & ec, int32_t actualBytes );
    // Called when data has been received by the connection.
	void onRecv( std::vector< std::string > & buffer );
    
	void startError( const boost::system::error_code & ec );
	// Called when an error is encountered.
	void onError( const boost::system::error_code & ec );
    
  private:
    ServerRef                               mServer;
    boost::asio::io_service::strand         mStrand;
    boost::asio::ip::tcp::socket            mSocket;
    std::vector< std::string >              mRecvBuffer;
    std::list< int32_t >                    mPendingRecvs;
    std::list< std::vector< std::string > > mPendingSends;
    int32_t                                 mReceiveBufferSize;
    
    volatile uint32_t                       mErrorState;
    
  public:
    
    
    
};


}
