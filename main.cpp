#include <iostream>
#include <thread>

#include "src/rpc_server.h"
using namespace std;
using namespace KhRpc;

int main()
{
    size_t hardware_concurrency = std::thread::hardware_concurrency();
    
    rpc_server server(9000, hardware_concurrency);
    cout << "asd" << endl;
    return 0;
}