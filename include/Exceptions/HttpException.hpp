#include <exception>
#include <string>

#include "ApplicationException.hpp"

class HttpException : public ApplicationException {
public:
    explicit HttpException(const std::string& message)
        : ApplicationException("HTTP Error: " + message) 
    {}
};