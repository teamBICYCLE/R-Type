#include <memory>
#include "GUnitPool.hh"
#include "GUnitFactory.hh"

GUnitPool::GUnitPool(void) :
	UnitPool(std::shared_ptr<UnitFactory>(new GUnitFactory()))
{
	// create Unit
	for (int i = 0; i != PLAYER_NB + MONSTER_NB + ROCKET_NB; ++i)
	{
		_collection[typeid(GUnit).name()].push_back(_factory->create<GUnit>());
	}
}

GUnitPool::~GUnitPool(void)
{

}