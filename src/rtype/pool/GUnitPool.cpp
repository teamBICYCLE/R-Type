#include "GUnitPool.hh"
#include "GUnitFactory.hh"

static GUnitPool *	_instance = NULL;

GUnitPool::GUnitPool(void) :
	UnitPool()
{
	GUnitFactory f;

	// create Player
	for (int i = 0; i != PLAYER_NB; ++i)
	{
		_collection[typeid(GPlayer).name()].push_back(f.create<GPlayer>());
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