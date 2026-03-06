#pragma once

#include <vector>

#include "IRiskEventRepository.hpp"

class RiskEvent;
class DatabaseConnection;

class RiskEventRepository : public IRiskEventRepository
{
public:
    explicit RiskEventRepository(DatabaseConnection& conn);
    
    virtual RiskEvent selectById(const int riskEventId) override;
    virtual std::vector<RiskEvent> selectOrderByTimestamp(const int count) override;
    virtual std::vector<RiskEvent> selectByBetweenTimestamps
    (
        const std::chrono::system_clock::time_point& startTimestamp,
        const std::chrono::system_clock::time_point& endTimestamp
    ) override;

    virtual void insert(const RiskEvent& riskEvent) override;
    virtual void insertMultiple(std::vector<const RiskEvent *> riskEvents) override;
    virtual void update(const RiskEvent& riskEvent) override;
    virtual void deleteById(const int riskEventId) override;

private:
    DatabaseConnection& _conn;
};