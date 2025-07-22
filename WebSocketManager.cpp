#include "WebSocketManager.h"

#include "external/json/stringbuffer.h"


WebSocketManager::WebSocketManager() {}

WebSocketManager::~WebSocketManager() {
    if (_ws) {
        _ws->close();
        delete _ws;
        _ws = nullptr;
    }
}

void WebSocketManager::connect(const std::string& url) {
    if (_ws) return;

    _ws = new ax::network::WebSocket();
    if (!_ws->open(this, url)) {
        AXLOG("Failed to open WebSocket connection.");
        delete _ws;
        _ws = nullptr;
    }
   
}

void WebSocketManager::sendMessage(const std::string& msg) {
    if (_ws && _ws->getReadyState() == ax::network::WebSocket::State::OPEN) {
        _ws->send(msg);
    }
}

void WebSocketManager::onOpen(ax::network::WebSocket* ws) {
    AXLOG("WebSocket connected.");
    sendMessage("Hello from client!");
}

void WebSocketManager::onMessage(ax::network::WebSocket* ws, const ax::network::WebSocket::Data& data) {
    AXLOG("WebSocket message received: %s", std::string(data.bytes, data.len).c_str());
}

void WebSocketManager::onClose(ax::network::WebSocket* ws, uint16_t code, std::string_view reason) {
    AXLOG("WebSocket closed. Code: %d, Reason: %s", code, std::string(reason).c_str());
}

void WebSocketManager::onError(ax::network::WebSocket* ws, const ax::network::WebSocket::ErrorCode& error) {
    AXLOG("WebSocket error occurred: %d", static_cast<int>(error));
}
