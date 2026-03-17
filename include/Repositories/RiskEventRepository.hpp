#pragma once

#include <vector>

#include "IRiskEventRepository.hpp"

class DatabaseConnection;
class RiskEvent;
class QDateTime;

class RiskEventRepository : public IRiskEventRepository
{
public:
    explicit RiskEventRepository(DatabaseConnection& conn);
    
    RiskEvent selectById(const int riskEventId) override;
    std::vector<RiskEvent> selectMultipleByCount
    (
        const int count
    ) override;
    std::vector<RiskEvent> selectMultipleByTimestamps
    (
        const int count,
        const QDateTime& from,
        const QDateTime& to
    ) override;
    std::vector<RiskEvent> selectMultipleByParameters
    (
        const int count,
        const bool acknowledged,
        const QDateTime& from,
        const QDateTime& to
    ) override;

    void insert(const RiskEvent& riskEvent) override;
    void insertMultiple(std::vector<RiskEvent>& riskEvents) override;
    void updateAcknowledged
    (
        const int riskEventId, 
        const bool acknowledged
    ) override;
    void deleteById(const int riskEventId) override;

private:
    DatabaseConnection& _conn;
};