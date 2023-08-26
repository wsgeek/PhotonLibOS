#pragma once

#include <photon/common/object.h>

#include <cstdint>
#include <string_view>

namespace photon {
namespace net {

class IWebSocketStream : public Object
{
public:
    ssize_t recv(void *buf, size_t count, int flags = 0);
    ssize_t send(const void *buf, size_t count, int flags = 0);
};

class IWebSocketClient : public Object
{
public:
    virtual IWebSocketStream* connect(std::string_view url) = 0;
};

extern "C"
{
IWebSocketClient* new_websocket_client();
}

} // namespace net
} // namespace photon