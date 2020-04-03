struct vppcom_service : public io_context::service {
    explicit vppcom_service( io_context &ctx );
    ~vppcom_service();
    static boost::asio::io_service::id id;
    void start();
    void run_epoll();

private:
    boost::scoped_ptr<boost::asio::io_service::work> work;
    boost::asio::io_service async_io_service;
    std::thread thread;

    // vppcom
    int fd;
};

struct vppcom_worker {
    io_context &io;
    stream_descriptor stream;
    int fd;

    vppcom_worker( io_context &i ):
        io( i ),
        stream( io, vppcom_worker_mqs_epfd() )
    {
        auto ret = vppcom_app_create( "bgp++ vppcom" );
        log( "app_create: "s + std::to_string( ret ) );
        fd = vppcom_epoll_create();
        stream.async_wait( boost::asio::posix::stream_descriptor::wait_read, std::bind( &vppcom_worker::callback, this, std::placeholders::_1 ) );
    }

    void callback( boost::system::error_code &ec );
};

struct vppcom_socket {
    uint32_t socket_handler;

    vppcom_socket( uint16_t port );
};