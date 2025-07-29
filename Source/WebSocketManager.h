#pragma once
#include "network/WebSocket.h"

class WebSocketManager : public ax::network::WebSocket::Delegate {
public:
    WebSocketManager();
    ~WebSocketManager();

    void connect(const std::string& url);
    void sendMessage(const std::string& msg);

    // WebSocket::Delegate overrides
    virtual void onOpen(ax::network::WebSocket* ws) override;
    virtual void onMessage(ax::network::WebSocket* ws, const ax::network::WebSocket::Data& data) override;
    virtual void onClose(ax::network::WebSocket* ws, uint16_t code, std::string_view reason) override;
    virtual void onError(ax::network::WebSocket* ws, const ax::network::WebSocket::ErrorCode& error) override;
    std::function<void( std::string&)> onMessageReceived;

private:
    ax::network::WebSocket* _ws = nullptr;
};
