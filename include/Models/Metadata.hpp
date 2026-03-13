#pragma once

#include <QDateTime>;

class Metadata
{
public:
    static void initializeVersionControl(const int version);
    static void cleanupVersionControl();
    static bool getIsInitialized();

    Metadata(const QDateTime& timestamp);

    const QDateTime& getTimestamp() const;
public:

private:
    static int _version;
    static bool _isInitialized;
    QDateTime _timestamp;
};