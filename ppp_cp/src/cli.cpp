#include "main.hpp"

extern std::shared_ptr<PPPOERuntime> runtime;

CLIServer::CLIServer( boost::asio::io_context &io_context, const std::string &path ): 
    acceptor_( io_context, stream_protocol::endpoint( path ) )
{
    do_accept();
}

void CLIServer::do_accept() {
    acceptor_.async_accept(
        [ this ]( boost::system::error_code ec, stream_protocol::socket socket ) {
            if( !ec ) {
                runtime->logger->logInfo() << LOGS::MAIN << "CLI new connection" << std::endl;
                std::make_shared<CLISession>( std::move( socket ) )->start();
            }
        do_accept();
    });
}

void CLISession::start() {
    do_read();
}

void CLISession::do_read() {
    auto self( shared_from_this() );
    socket_.async_read_some(
        boost::asio::buffer( data_ ),
        [ this, self ]( boost::system::error_code ec, std::size_t length ) {
            if( !ec ) {
                run_cmd( { data_.begin(), data_.begin() + length } );
            }
        }
    );
}

void CLISession::do_write( std::string &out ) {
    auto self( shared_from_this() );
    out.append( "\r\n\r\n" );
    socket_.async_write_some(
        boost::asio::buffer( out.data(), out.size() ),
        [ this, self ]( boost::system::error_code ec, std::size_t ) {
            if( !ec ) {
                do_read();
            }
        }
    );
}

inline bool startWith( const std::string &s1, const std::string &s2 ) {
    return s1.find( s2 ) == 0;
}

void CLISession::run_cmd( const std::string &cmd ) {
    std::string output;
    if( startWith( cmd, "show subscribers" ) ) {
        output = "show subscribers output...";
    } else {
        output = "unknown command";
    }
    do_write( output );
}