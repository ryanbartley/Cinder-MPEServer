//
//  TCPServer.h
//  CinderTCPServer
//
//  Created by Ryan Bartley on 7/20/13.
//
//

#pragma once

#include <string>
#include <vector>
#include <map>
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <functional>

#include "TCPConnection.h"

namespace  TCP {

class Server;
typedef std::shared_ptr< Server > ServerRef;
     
class Server :
    public std::enable_shared_from_this< Server >,
    private boost::noncopyable {

public:
    explicit Server( const std::string& address, const std::string& port, std::size_t threadPoolSize );
    static ServerRef create( const std::string& address, const std::string& port, std::size_t threadPoolSize )
    { return ServerRef( new Server( address, port, threadPoolSize ) ); }

    void run();
    void disconnect( int clientId );
    void stop();
    bool hasStopped();

    boost::asio::io_service&    getIoService() { return mIoService; }
    std::map<int, ConnectRef>&  getConnectedClients() { return ConnectedClients; }
       
    // Sets the timer interval of the object. The interval is changed after
    // the next update is called.
    void setTimerInterval( int32_t timerIntervalMilli ) { mTimerInterval = timerIntervalMilli; }
    
    // Returns the timer interval of the object.
    int32_t getTimerInterval() const { return mTimerInterval; }
        
    // Called on each timer event.
    void onTimer( const boost::posix_time::time_duration & delta );

private:
    void startAccept();
    void handleAccept( const boost::system::error_code& e );
    void handleStop();
    
    void dispatchTimer( const boost::system::error_code & ec );
	void startTimer();
    void handleTimer( const boost::system::error_code & ec );
    
    
    
    std::map<int, ConnectRef>       ConnectedClients;
    ConnectRef                      newConnection;
    std::size_t                     threadPoolSize;
    boost::asio::io_service         mIoService;
    boost::shared_ptr< boost::asio::io_service::work >  mWorkPtr;
    boost::asio::signal_set         terminationSignals;
    boost::asio::ip::tcp::acceptor  acceptor;
    
    boost::asio::deadline_timer     mTimer;
    boost::posix_time::ptime        mLastTime;
    int32_t                         mTimerInterval;
    volatile uint32_t               mShutdown;
        
    // Called when the client has successfully connected to the local
    // host.
    std::function< void( ConnectRef, int ) > onAcceptEvent;

// Adding Listeners
public:
        
    template<

};


        
}// <-TCP
