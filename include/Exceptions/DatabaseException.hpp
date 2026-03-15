#include <exception>
#include <string>

#include "ApplicationException.hpp"

class DatabaseException : public ApplicationException {
public:
    explicit DatabaseException(const std::string& message)
        : ApplicationException("Database Error: " + message) 
    {}
};