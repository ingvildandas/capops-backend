#include "Services/RiskEventService.hpp"
#include "Repositories/IRiskEventRepository.hpp"

RiskEventService::RiskEventService(IRiskEventRepository& repository)
    : _repository(repository)
{}