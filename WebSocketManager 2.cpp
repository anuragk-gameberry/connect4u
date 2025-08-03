#include "../WebSocketManager.h"
#include "../JsonHandler.h"



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
    AXLOG("reached here3");

    _ws = new ax::network::WebSocket();
    AXLOG("reached here3.5");
    
    if(_ws == nullptr){
        AXLOG("ws is null");
    }
    
    if ((_ws != nullptr) && !_ws->open(this, url)) {
        AXLOG("Failed to open WebSocket connection.");
        delete _ws;
        _ws = nullptr;
    }
    
    AXLOG("reached final4");
 
   
    AXLOG("reached here5");
}

void WebSocketManager::sendMessage(const std::string& msg) {
    if (_ws && _ws->getReadyState() == ax::network::WebSocket::State::OPEN ){
        _ws->send(msg);
    }
    else {
        AXLOG("connection not ready");
    }
   
    
    
}

void WebSocketManager::onOpen(ax::network::WebSocket* ws) {
    if (this->initialize)
    this->initialize();
   
}

void WebSocketManager::onMessage(ax::network::WebSocket* ws, const ax::network::WebSocket::Data& data) {
    std::string jsonStr(data.bytes, data.len);
    AXLOG("WebSocket message received: %s", jsonStr.c_str());
    std::string s ="";
    s+= jsonStr;
    this->onMessageReceived(s);
//    JsonHandler::parseJson(s);
   
}

void WebSocketManager::onClose(ax::network::WebSocket* ws, uint16_t code, std::string_view reason) {
    AXLOG("WebSocket closed. Code: %d, Reason: %s", code, std::string(reason).c_str());
}

void WebSocketManager::onError(ax::network::WebSocket* ws, const ax::network::WebSocket::ErrorCode& error) {
    AXLOG("WebSocket error occurred: %d", static_cast<int>(error));
}
