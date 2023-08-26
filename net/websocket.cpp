#include "websocket.h"

#include <photon/net/socket.h>

#include <memory>

//   0                   1                   2                   3
//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
//  +-+-+-+-+-------+-+-------------+-------------------------------+
//  |F|R|R|R| opcode|M| Payload len |    Extended payload length    |
//  |I|S|S|S|  (4)  |A|     (7)     |             (16/64)           |
//  |N|V|V|V|       |S|             |   (if payload len==126/127)   |
//  | |1|2|3|       |K|             |                               |
//  +-+-+-+-+-------+-+-------------+ - - - - - - - - - - - - - - - +
//  |     Extended payload length continued, if payload len == 127  |
//  + - - - - - - - - - - - - - - - +-------------------------------+
//  |                               |Masking-key, if MASK set to 1  |
//  +-------------------------------+-------------------------------+
//  | Masking-key (continued)       |          Payload Data         |
//  +-------------------------------- - - - - - - - - - - - - - - - +
//  :                     Payload Data continued ...                :
//  + - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - +
//  |                     Payload Data continued ...                |
//  +---------------------------------------------------------------+

namespace photon {
namespace net {

// ============================================================================
// ============================================================================

class WebSocketStreamImpl : public IWebSocketStream
{
public:
    WebSocketStreamImpl(ISocketStream* tcpstream)
        : tcpstream(tcpstream)
    {
    }

    ssize_t recv(void *buf, size_t count, int flags)
    {
        return 0;
    }

    ssize_t send(const void *buf, size_t count, int flags)
    {
        return 0;
    }

private:
    std::unique_ptr<ISocketStream> tcpstream;
};

// ============================================================================
// ============================================================================

class WebSocketClientImpl : public IWebSocketClient
{
    IWebSocketStream* connect(std::string_view url) override
    {
        EndPoint ep;
        ISocketClient* client = new_tcp_socket_client();
        ISocketStream* tcpstream = client->connect(ep);
        return new WebSocketStreamImpl(tcpstream);
    }
};

// ============================================================================
// ============================================================================

extern "C"
{
IWebSocketClient* new_websocket_client()
{
    return new WebSocketClientImpl();
}
}

} // namespace net
} // namespace photon