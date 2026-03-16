#include <stdexcept>

#include <QDateTime>

#include "Models/Metadata.hpp"

void Metadata::initializeVersionControl(const int version)
{
    if (version < 1) 
    {
        throw new std::runtime_error("Cannot set non-positive version");
    }
    _version = version;
    _isInitialized = true;
}
void Metadata::cleanupVersionControl()
{
    _version = 0;
    _isInitialized = false;
}

bool Metadata::getIsInitialized()
{
    if (!_isInitialized || _version < 1)
    {
        return false;
    }

    return true;
}

int Metadata::getVersion()
{
    if (!getIsInitialized())
    {
        throw new std::runtime_error("Version control not initialized");
    }

    return _version;
}

Metadata::Metadata(const QDateTime& timestamp) : _timestamp(timestamp)
{
    if (!getIsInitialized())
    {
        throw new std::runtime_error("Version control not initialized");
    }
}

const QDateTime& Metadata::getTimestamp() const
{
    return _timestamp;
}