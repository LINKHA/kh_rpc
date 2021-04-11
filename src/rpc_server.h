#pragma once
#include <string>

#include "router.h"

namespace KhRpc
{

class rpc_server
{
public:
    rpc_server(unsigned short port, size_t size, size_t timeout_seconds = 15, size_t check_seconds = 10);
    ~rpc_server();

private:
    router _router;
};

}