#ifndef VPP_API_HPP_
#define VPP_API_HPP_

#include "vapi/vapi.hpp"
#include "vapi/vpe.api.vapi.hpp"

#include "vapi/interface.api.vapi.hpp"
#include "vapi/tapv2.api.vapi.hpp"
#include "vapi/pppoe.api.vapi.hpp"
#include "vapi/policer.api.vapi.hpp"

#include "config.hpp"
#include "log.hpp"

struct InterfaceConf;

enum class IfaceType: uint8_t {
    LOOPBACK,
    HW_IFACE,
    TAP,
    SUBIF
};

struct VPPInterface {
    std::string name;
    std::string device;
    mac_t mac;
    uint32_t sw_if_index;
    uint32_t speed;
    uint16_t mtu;
    IfaceType type;
};

struct VPP_PPPOE_Session {
    uint16_t session_id;
    mac_t mac;
    address_v4_t address;
    uint32_t sw_if_index;
    uint32_t encap_if_index;
};

struct VPPIfaceCounters {
    uint64_t rxPkts;
    uint64_t rxBytes;
    uint64_t txPkts;
    uint64_t txBytes;
    uint64_t drops;
};

std::ostream& operator<<( std::ostream &stream, const IfaceType &iface );
std::ostream& operator<<( std::ostream &stream, const struct VPPInterface &iface );

class VPPAPI {
public:
    VPPAPI( boost::asio::io_context &io, std::unique_ptr<Logger> &l );
    ~VPPAPI();

    // Interface dump methods
    std::set<uint32_t> get_tap_interfaces();
    std::vector<VPPInterface> get_ifaces();
    void get_stats( uint32_t sw_if_index );

    // Subif
    std::tuple<bool,uint32_t> add_subif( uint32_t iface, uint16_t outer_vlan, uint16_t inner_vlan );
    bool del_subif( uint32_t sw_if_index );

    // Tap
    std::tuple<bool,uint32_t> create_tap( const std::string &host_name );
    bool delete_tap( uint32_t id );

    // Interface configuration
    bool setup_interfaces( const std::vector<InterfaceConf> &ifaces );
    bool set_ip( uint32_t id, network_v4_t address );
    bool set_state( uint32_t ifi, bool admin_state );
    bool set_mtu( uint32_t ifi, uint16_t mtu );

    // PPPoE methods
    std::tuple<bool,uint32_t> add_pppoe_session( uint32_t ip_address, uint16_t session_id, std::array<uint8_t,6> mac, bool is_add = true );
    bool add_pppoe_cp( uint32_t sw_if_index, bool to_del = false );
    std::vector<VPP_PPPOE_Session> dump_pppoe_sessions();

    // Stats
    std::tuple<bool,VPPIfaceCounters> get_counters_by_index( uint32_t ifindex );
private:
    void collect_counters();

    void process_msgs( boost::system::error_code err );
    boost::asio::io_context &io;
    boost::asio::steady_timer timer;
    std::unique_ptr<Logger> &logger;
    std::map<uint32_t,VPPIfaceCounters> counters;
    vapi::Connection con;
};

#endif