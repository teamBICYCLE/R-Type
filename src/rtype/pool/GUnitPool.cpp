#include "GUnitPool.hh"
#include "GUnitFactory.hh"

static GUnitPool *	_instance = NULL;

GUnitPool::GUnitPool(void) :
	UnitPool()
{
	GUnitFactory f;

	// create Player
	for (int i = 0; i != PLAYER_NB + MONSTER_NB + ROCKET_NB; ++i)
	{
		_collection[typeid(GUnit).name()].push_back(f.create<GUnit>());
	}
}

GUnitPool::~GUnitPool(void)
{

}

GUnitPool *GUnitPool::getInstance(void)
{
	if (!_instance)
		_instance = new GUnitPool();
	return _instance;
}

void	GUnitPool::deleteInstance(void)
{
	delete _instance;
	_instance = NULL;
}
