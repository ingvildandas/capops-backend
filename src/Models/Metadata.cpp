#include <stdexcept>

#include <QDateTime>

#include "Models/Metadata.hpp"

Metadata::Metadata(const QDateTime& timestamp)
    : _timestamp(timestamp)
{}

const QDateTime& Metadata::getTimestamp() const
{
    return _timestamp;
}