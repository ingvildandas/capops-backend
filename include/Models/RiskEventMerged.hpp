#pragma once

#include <vector>

#include <QString>

class RiskEvent;

class RiskEventMerged
{
public:
    RiskEventMerged
    (
        const int sectorId,
        const std::vector<RiskEvent>& riskEvents
    );

    int getSectorId() const;
    std::vector<RiskEvent> getRiskEvents() const;

    void setRiskEvents(const std::vector<RiskEvent>& riskEvents);

    void addRiskEvents(const std::vector<RiskEvent>& riskEvents);

private:
    int _sectorId;
    std::vector<RiskEvent> _riskEvents;
    QString _summaryMessage;
    QString _lastMessage;

private:
    void addRiskEvent(const RiskEvent& riskEvent);
    void setSummaryMessage();
    void setLastMessage();
};