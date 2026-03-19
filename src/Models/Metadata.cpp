#include <stdexcept>

#include <QDateTime>

#include "Models/Metadata.hpp"

Metadata::Metadata(const QDateTime& timestamp)
    : _timestamp(timestamp)
{}

QDateTime Metadata::getTimestamp() const
{
    return _timestamp;
}