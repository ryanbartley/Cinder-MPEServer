//
//  TCPServer.cpp
//  CinderTCPServer
//
//  Created by Ryan Bartley on 7/20/13.
//
//

#include "TCPServer.h"
#include <thread>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>


namespace TCP {
        
Server::Server( const std::string& address, const std::string& port, std::size_t threadPoolSize )
: threadPoolSize(threadPoolSize),
    terminationSignals( mIoService ),
    acceptor( mIoService ),
    newConnection()
{
    terminationSignals.add(SIGINT);
    terminationSignals.add(SIGTERM);
    #if defined(SIGQUIT)
        terminationSignals.add(SIGQUIT);
    #endif
    terminationSignals.async_wait( boost::bind( &Server::handleStop, this ) );
    
    boost::asio::ip::tcp::resolver resolver( mIoService );
    boost::asio::ip::tcp::resolver::query query( address, port );
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve( query );
    
    acceptor.open( endpoint.protocol() );
    acceptor.set_option( boost::asio::ip::tcp::acceptor::reuse_address( true ) );
    acceptor.bind( endpoint );
    acceptor.listen();
    
    startAccept();
}

void Server::run()
{
    std::vector< std::shared_ptr< std::thread > > threadPool;
    for ( std::size_t i = 0; i < threadPoolSize; ++i ) {
        std::shared_ptr< std::thread > thread( new std::thread( boost::bind( &boost::asio::io_service::run, &mIoService ) ) );
        threadPool.push_back( thread );
    }
     
    for ( auto threadIt = threadPool.begin(); threadIt != threadPool.end(); ++threadIt ) {
        (*threadIt)->join();
    }
}

void Server::startAccept()
{
    newConnection = Connection::create( shared_from_this() );
    acceptor.async_accept( newConnection->getSocket(), boost::bind(&Server::handleAccept, this, boost::asio::placeholders::error ) );
}

void Server::handleAccept(const boost::system::error_code& e)
{
    if (!e) {
        newConnection->start();
        ConnectedClients.insert(std::pair<int, ConnectRef>(ConnectedClients.size()+1, newConnection) );
    }
    
    startAccept();
}

void Server::handleStop()
{
    mIoService.stop();
}

}
