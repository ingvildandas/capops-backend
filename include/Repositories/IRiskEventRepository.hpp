#pragma once

#include <vector>

class RiskEvent;
class QTimeZone;

class IRiskEventRepository
{
public:
    virtual ~IRiskEventRepository() = default;

    virtual RiskEvent selectById(const int riskEventId) = 0;
    virtual std::vector<RiskEvent> selectOrderByTimestamp(const int count) = 0;
    virtual std::vector<RiskEvent> selectByBetweenTimestamps
    (
        const int count,
        const bool acknowledged,
        const QTimeZone& from,
        const QTimeZone& to
    ) = 0;

    virtual void insert(const RiskEvent& riskEvent) = 0;
    virtual void insertMultiple(std::vector<const RiskEvent*>& riskEvents) = 0;
    virtual void updateAcknowledged(const int riskEventId, const bool acknowledged) = 0;
    virtual void deleteById(const int riskEventId) = 0;
};