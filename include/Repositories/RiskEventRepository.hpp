#pragma once

#include <vector>

#include "IRiskEventRepository.hpp"

class DatabaseConnection;
class RiskEvent;
class QTimeZone;

class RiskEventRepository : public IRiskEventRepository
{
public:
    explicit RiskEventRepository(DatabaseConnection& conn);
    
    RiskEvent selectById(const int riskEventId) override;
    std::vector<RiskEvent> selectOrderByTimestamp(const int count) override;
    std::vector<RiskEvent> selectByBetweenTimestamps
    (
        const int count,
        const bool acknowledged,
        const QTimeZone& from,
        const QTimeZone& to
    ) override;

    void insert(const RiskEvent& riskEvent) override;
    void insertMultiple(std::vector<const RiskEvent*>& riskEvents) override;
    void updateAcknowledged(const int riskEventId, const bool acknowledged) override;
    void deleteById(const int riskEventId) override;

private:
    DatabaseConnection& _conn;
};