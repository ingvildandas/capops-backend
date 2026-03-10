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
    const int count,
    const bool acknowledged,
    const QTimeZone& from,
    const QTimeZone& to
)
{
    return std::vector<RiskEvent>{};
}

void RiskEventRepository::insert(const RiskEvent& riskEvent) 
{}

void RiskEventRepository::insertMultiple
(
    std::vector<const RiskEvent*>& riskEvents
) 
{}

void RiskEventRepository::updateAcknowledged(const int riskEventId, const bool acknowledged) 
{}

void RiskEventRepository::deleteById(const int riskEventId) 
{}

