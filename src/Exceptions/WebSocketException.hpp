#include <exception>
#include <string>

#include "ApplicationException.hpp"

class WebSocketException : public ApplicationException {
public:
    explicit WebSocketException(const std::string& message)
        : ApplicationException("WebSocket Error: " + message) 
    {}
};