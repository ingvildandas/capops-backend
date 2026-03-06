#pragma once

#include "Repositories/IRiskEventRepository.hpp"

class RiskEventService 
{
public:
    explicit RiskEventService(IRiskEventRepository& repository);

private:
    IRiskEventRepository& _repository;
};