#pragma once

#include <string>

class RiskEvent
{
public:
    RiskEvent(
        const int riskEventId,
        const int riskSeverity,
        const std::string& message,
        const bool acknowledged
    );

    const int getRiskEventId() const;
    const int getRiskSeverity() const;
    const std::string& getMessage() const;
    const bool getAcknowledged() const;

private:
    int _riskEventId;
    int _riskSeverity;
    std::string _message;
    bool _acknowledged;
};

