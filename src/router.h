#pragma once
#include <string>
#include <functional>
#include <memory>
#include <unordered_map>

//#include "io_service_pool.h"
#include "connection.h"

using boost::asio::ip::tcp;

namespace KhRpc
{
enum class ExecMode { sync, async };
const constexpr ExecMode Async = ExecMode::async;

class router : asio::noncopyable
{
public:
    template<ExecMode model, typename Function>
    void register_handler(std::string const& name, Function f) {
        return register_nonmember_func<model>(name, std::move(f));
    }
    
    router() = default;
private:
    router(const router&) = delete;
    router(router &&) = delete;
    /* data */

    template<typename Function, ExecMode mode = ExecMode::sync>
    struct invoker {
        // template<ExecMode model>
        // static inline void apply(const Function& func, std::weak_ptr<connection> conn, const char* data, size_t size,
        //     std::string& result, ExecMode& exe_model) {
        //     using args_tuple = typename function_traits<Function>::args_tuple_2nd;
        //     exe_model = ExecMode::sync;
        //     msgpack_codec codec;
        //     try {
        //         auto tp = codec.unpack<args_tuple>(data, size);
        //         call(func, conn, result, std::move(tp));
        //         exe_model = model;
        //     }
        //     catch (std::invalid_argument & e) {
        //         result = codec.pack_args_str(result_code::FAIL, e.what());
        //     }
        //     catch (const std::exception & e) {
        //         result = codec.pack_args_str(result_code::FAIL, e.what());
        //     }
        // }

        // template<ExecMode model, typename Self>
        // static inline void apply_member(const Function& func, Self* self, std::weak_ptr<connection> conn,
        //     const char* data, size_t size, std::string& result,
        //     ExecMode& exe_model) {
        //     using args_tuple = typename function_traits<Function>::args_tuple_2nd;
        //     exe_model = ExecMode::sync;
        //     msgpack_codec codec;
        //     try {
        //         auto tp = codec.unpack<args_tuple>(data, size);
        //         call_member(func, self, conn, result, std::move(tp));
        //         exe_model = model;
        //     }
        //     catch (std::invalid_argument & e) {
        //         result = codec.pack_args_str(result_code::FAIL, e.what());
        //     }
        //     catch (const std::exception & e) {
        //         result = codec.pack_args_str(result_code::FAIL, e.what());
        //     }
        // }
    };
    
    template<ExecMode model, typename Function>
    void register_nonmember_func(std::string const& name, Function f) {
        _map_invokers[name] = {
            std::bind(&invoker<Function>::template apply<model>, 
            std::move(f), std::placeholders::_1,
            std::placeholders::_2, std::placeholders::_3,
            std::placeholders::_4, std::placeholders::_5) 
        };
    }

    std::unordered_map<
        std::string,
		std::function<void(
            std::weak_ptr<connection>, 
            const char*, 
            size_t, std::string&, 
            ExecMode& model)>>
		_map_invokers;
};


}