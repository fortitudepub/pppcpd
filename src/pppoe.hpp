#ifndef PPPOE_HPP_
#define PPPOE_HPP_

#include "packet.hpp"

struct encapsulation_t;

namespace pppoe {
    uint8_t insertTag( std::vector<uint8_t> &pkt, PPPOE_TAG tag, const std::string &val );
    std::tuple<std::map<PPPOE_TAG,std::string>,std::string> parseTags( std::vector<uint8_t> &pkt );
    std::string processPPPOE( std::vector<uint8_t> &inPkt, const encapsulation_t &encap );
}

#endif