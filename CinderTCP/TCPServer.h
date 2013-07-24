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

    boost::asio::io_service& getIoService() { return mIoService; }
    std::map<int, ConnectRef>& getConnectedClients() { return ConnectedClients; }

protected:
    std::map<int, ConnectRef>       ConnectedClients;

private:
    void startAccept();
    void handleAccept( const boost::system::error_code& e );
    void handleStop();
    void startTimer();
    void handleTimer();

    std::size_t                     threadPoolSize;
    boost::asio::io_service         mIoService;
    boost::asio::signal_set         terminationSignals;
    boost::asio::ip::tcp::acceptor  acceptor;
    ConnectRef                      newConnection;


};


        
}// <-TCP
