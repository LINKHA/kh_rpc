#pragma once
#include <string>

#include "router.h"

namespace KhRpc
{

class rpc_server : private asio::noncopyable
{
public:
    rpc_server(unsigned short port, size_t size, size_t timeout_seconds = 15, size_t check_seconds = 10);
    ~rpc_server();

private:

    //io_service_pool _io_service_pool;
	//tcp::acceptor _acceptor;

    router _router;
};

}