#pragma once

#include <QString>

class RiskEvent
{
public:
    RiskEvent(
        const int riskEventId,
        const int riskSeverity,
        const QString& message,
        const bool acknowledged
    );

    const int getRiskEventId() const;
    const int getRiskSeverity() const;
    const QString& getMessage() const;
    const bool getAcknowledged() const;

private:
    int _riskEventId;
    int _riskSeverity;
    QString _message;
    bool _acknowledged;
};

