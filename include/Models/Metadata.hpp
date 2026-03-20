#pragma once

#include <QDateTime>

class Metadata
{
public:
    Metadata(const QDateTime& timestamp);

    QDateTime getTimestamp() const;
public:

private:
    QDateTime _timestamp;
};