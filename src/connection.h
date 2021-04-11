#pragma once
#include <memory>

#include "use_asio.hpp"

using boost::asio::ip::tcp;

namespace KhRpc
{

class connection : public std::enable_shared_from_this<connection>
, private asio::noncopyable 
{


    tcp::socket _socket;
};

}