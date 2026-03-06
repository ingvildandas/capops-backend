#include <chrono>
#include <vector>

#include "Repositories/RiskEventRepository.hpp"
#include "Database/DatabaseConnection.hpp"
#include "Models/RiskEvent.hpp"

RiskEventRepository::RiskEventRepository(DatabaseConnection& conn)
    : _conn(conn)
{}

RiskEvent RiskEventRepository::selectById(const int riskEventId)
{
    return RiskEvent(0, 0, "", 0);
}

std::vector<RiskEvent> RiskEventRepository::selectOrderByTimestamp
(
    const int count
)
{
    return std::vector<RiskEvent>{};
}

std::vector<RiskEvent> RiskEventRepository::selectByBetweenTimestamps
(
    const std::chrono::system_clock::time_point& startTimestamp,
    const std::chrono::system_clock::time_point& endTimestamp
)
{
    return std::vector<RiskEvent>{};
}

void RiskEventRepository::insert(const RiskEvent& riskEvent) 
{}

void RiskEventRepository::insertMultiple
(
    std::vector<const RiskEvent *> riskEvents
) 
{}

void RiskEventRepository::update(const RiskEvent& riskEvent) 
{}

void RiskEventRepository::deleteById(const int riskEventId) 
{}

