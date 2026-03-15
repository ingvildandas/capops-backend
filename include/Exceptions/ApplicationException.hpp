#pragma once

#include <exception>
#include <string>
#include <utility>

class ApplicationException : public std::exception {
public:
    explicit ApplicationException(std::string message) 
        : _message(std::move(message)) 
    {}

    [[nodiscard]] const char* what() const noexcept override 
    {
        return _message.c_str();
    }

private:
    std::string _message;
};