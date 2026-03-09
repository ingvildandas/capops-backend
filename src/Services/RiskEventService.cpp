#include "Services/RiskEventService.hpp"
#include "Repositories/IRiskEventRepository.hpp"

RiskEventService::RiskEventService(
    IRiskEventRepository& repository, 
    FlightDataStateManager& stateManager
)
    : _repository(repository), _stateManager(stateManager)
{}