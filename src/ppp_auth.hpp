#ifndef PPP_AUTH_HPP_
#define PPP_AUTH_HPP_

struct PPPOESession;

struct PPP_AUTH {
private:
    uint8_t pkt_id { 1U };
    bool started { false };
    PPPOESession &session;

public:

    PPP_AUTH( PPPOESession &s ):
        session( s )
    {}
    
    void open();
    void layer_up();
    void layer_down();

    FSM_RET receive( std::vector<uint8_t> &inPkt );
    // PAP methods
    void recv_auth_req( std::vector<uint8_t> &inPkt );
    FSM_RET send_auth_ack();
    FSM_RET send_auth_nak();

    FSM_RET auth_callback( uint32_t sid, const std::string &err );
};

#endif