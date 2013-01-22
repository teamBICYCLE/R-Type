#include "UnitPool.hh"

UnitPool::UnitPool(const std::shared_ptr<UnitFactory> &f)
	: _currentId(0), _factory(f)
{
}

UnitPool::~UnitPool(void)
{
}