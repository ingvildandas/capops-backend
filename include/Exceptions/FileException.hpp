#include <exception>
#include <string>

#include "ApplicationException.hpp"

class FileException : public ApplicationException {
public:
    explicit FileException(const std::string& message)
        : ApplicationException("File Error: " + message) 
    {}
};