#include <exception>
#include <string>

#include "ApplicationException.hpp"

class EntityModelException : public ApplicationException {
public:
    explicit EntityModelException(const std::string& message)
        : ApplicationException("Entity Error: " + message) 
    {}
};