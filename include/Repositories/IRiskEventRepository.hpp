#pragma once

#include <vector>

class RiskEvent;

class IRiskEventRepository
{
public:
    virtual ~IRiskEventRepository() = default;

    virtual RiskEvent selectById(const int riskEventId) = 0;
    virtual std::vector<RiskEvent> selectOrderByTimestamp(const int count) = 0;
    virtual std::vector<RiskEvent> selectByBetweenTimestamps
    (
        const std::chrono::system_clock::time_point& startTimestamp,
        const std::chrono::system_clock::time_point& endTimestamp
    ) = 0;

    virtual void insert(const RiskEvent& riskEvent) = 0;
    virtual void insertMultiple(std::vector<const RiskEvent *> riskEvents) = 0;
    virtual void update(const RiskEvent& riskEvent) = 0;
    virtual void deleteById(const int riskEventId) = 0;
};