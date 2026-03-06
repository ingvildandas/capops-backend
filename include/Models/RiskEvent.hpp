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

    const int getRiskEventId();
    const int getRiskSeverity();
    const std::string& getMessage();
    const bool getAcknowledged();

private:
    int _riskEventId;
    int _riskSeverity;
    std::string _message;
    bool acknowledged;
};

