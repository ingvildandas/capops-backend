#include <exception>
#include <string>

#include "ApplicationException.hpp"

class RedisEventBusException : public ApplicationException {
public:
    explicit RedisEventBusException(const std::string& message)
        : ApplicationException("Redis Event Bus Error: " + message) 
    {}
};