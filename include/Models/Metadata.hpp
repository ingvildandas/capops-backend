#pragma once

#include <QDateTime>;

class Metadata
{
public:
    Metadata(const QDateTime& timestamp);

    const QDateTime& getTimestamp() const;
public:
    static int version;

private:
    QDateTime _timestamp;
};