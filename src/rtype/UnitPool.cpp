#include "UnitPool.hh"

static UnitPool *	_instance = NULL;

UnitPool::UnitPool(void)
{
	UnitFactory f;

	// create Players
	for (int i = 0; i != PLAYER_NB; ++i)
		_collection[typeid(Player).name()].push_back(f.create<Player>());

	using namespace TBSystem;
	log::info << "Pool Player Size = " << _collection[typeid(Player).name()].size() << log::endl;
}

UnitPool::~UnitPool(void)
{
	using namespace TBSystem;
	log::info << "Pool Player Size = " << _collection[typeid(Player).name()].size() << log::endl;
	_collection[typeid(Player).name()].clear();
}

UnitPool *UnitPool::getInstance(void)
{
	if (!_instance)
		_instance = new UnitPool();
	return _instance;
}

void	UnitPool::deleteInstance(void)
{
	delete _instance;
	_instance = NULL;
}