#pragma once

#include <QDateTime>

class Metadata
{
public:
    static void initializeVersionControl(const int version);
    static void cleanupVersionControl();
    static bool getIsInitialized();
    static int getVersion();

    Metadata(const QDateTime& timestamp);

    const QDateTime& getTimestamp() const;
public:

private:
    inline static int _version = 0;
    inline static bool _isInitialized = false;
    QDateTime _timestamp;
};