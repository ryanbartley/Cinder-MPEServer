//
//  Message.h
//  CinderTCPServer
//
//  Created by Ryan Bartley on 7/25/13.
//
//

#pragma once



namespace TCP {
    
class Message;
typedef std::shared_ptr< Message > MessageRef;
    
class Message : std::enable_shared_from_this< Message > {
  
public:
    virtual ~Message();
    
    std::size_t getSize() { return sizeof(this); }
    MessageRef  get() { return shared_from_this(); }
    
private:
    Message();
    
};
    
}
