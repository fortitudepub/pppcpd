struct PPPOESession {
    // General Data
    std::array<uint8_t,6> mac;
    bool started { false };
    uint32_t aaa_session_id{ UINT32_MAX };

    // PPPoE Data
    uint16_t session_id;
    std::string cookie;
    
    // Various data
    std::string username;
    uint32_t address;

    // PPP FSM for all the protocols we support
    LCP_FSM lcp;
    PPP_AUTH auth;
    IPCP_FSM ipcp;

    // LCP negotiated options
    uint16_t our_MRU;
    uint16_t peer_MRU;
    uint32_t our_magic_number;
    uint32_t peer_magic_number;

    PPPOESession( std::array<uint8_t,6> m, uint16_t sid ): 
        mac( m ),
        session_id( sid ),
        lcp( sid ),
        auth( sid ),
        ipcp( sid )
    {
        log( "Session UP: " + std::to_string( sid ) );
    }

    ~PPPOESession() {
        deprovision_dp();
    }

    std::string provision_dp();
    std::string deprovision_dp();
};