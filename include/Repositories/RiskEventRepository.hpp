#pragma once

#include <vector>

#include "IRiskEventRepository.hpp"

class RiskEvent;
class DatabaseConnection;

class RiskEventRepository : public IRiskEventRepository
{
public:
    explicit RiskEventRepository(DatabaseConnection& conn);
    
    RiskEvent selectById(const int riskEventId) override;
    std::vector<RiskEvent> selectOrderByTimestamp(const int count) override;
    std::vector<RiskEvent> selectByBetweenTimestamps
    (
        const std::chrono::system_clock::time_point& startTimestamp,
        const std::chrono::system_clock::time_point& endTimestamp
    ) override;

    void insert(const RiskEvent& riskEvent) override;
    void insertMultiple(std::vector<const RiskEvent *> riskEvents) override;
    void update(const RiskEvent& riskEvent) override;
    void deleteById(const int riskEventId) override;

private:
    DatabaseConnection& _conn;
};