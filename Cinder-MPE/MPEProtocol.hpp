//
//  MPEProtocol.h
//  CinderTCPServer
//
//  Created by Ryan Bartley on 7/20/13.
//
//

#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

namespace cinder {
    namespace mpe {
        
        class MPEProtocol {
          
        protected:
            
            const std::string CONNECT_SYNCHRONOUS   = "S";
            const std::string DONE_RENDERING        = "D";
            const std::string DATA_MESSAGE          = "T";
            const std::string NEXT_FRAME            = "G";
            const std::string CONNECT_ASYNCHRONOUS  = "A";
            const std::string RESET_ALL             = "R";
            const std::string PAUSE_ALL             = "P";
            
        public:
            
        };
    } //  <--MPE
} // <--CINDER
