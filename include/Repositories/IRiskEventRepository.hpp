#pragma once

#include <vector>

class RiskEvent;
class QDateTime;

class IRiskEventRepository
{
public:
    virtual ~IRiskEventRepository() = default;

    virtual RiskEvent selectById(const int riskEventId) = 0;
    virtual std::vector<RiskEvent> selectMultipleByCount(const int count) = 0;
    virtual std::vector<RiskEvent> selectMultipleByAcknowledged
    (
        const int count, 
        const bool acknowledged
    ) = 0;
    virtual std::vector<RiskEvent> selectMultipleByTimestamps
    (
        const int count,
        const QDateTime& from,
        const QDateTime& to
    ) = 0;
    virtual std::vector<RiskEvent> selectMultipleByParameters
    (
        const int count,
        const bool acknowledged,
        const QDateTime& from,
        const QDateTime& to
    ) = 0;

    virtual void insert(const RiskEvent& riskEvent) = 0;
    virtual void insertMultiple(const std::vector<RiskEvent>& riskEvents) = 0;
    virtual void updateAcknowledged
    (
        const int riskEventId, 
        const bool acknowledged
    ) = 0;
    virtual void updateMultipleAcknowledged(const std::vector<int>& riskEventIds) = 0;
    virtual void deleteById(const int riskEventId) = 0;
};