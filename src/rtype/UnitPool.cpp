#include "UnitPool.hh"

static UnitPool *	_instance = NULL;

UnitPool::UnitPool(void)
{
	UnitFactory f;

	// create Players
	for (int i = 0; i != PLAYER_NB; ++i)
		_collection[typeid(Player).name()].push_back(f.create<Player>());

	// create Monsters
	for (int i = 0; i != MONSTER_NB; ++i)
		_collection[typeid(Monster).name()].push_back(f.create<Monster>());

	using namespace TBSystem;
	log::info << "Pool Size = " <<
		_collection[typeid(Player).name()].size() +
		_collection[typeid(Monster).name()].size()
	<< log::endl;
}

UnitPool::~UnitPool(void)
{
	using namespace TBSystem;
	log::info << "Pool Size = " <<
		_collection[typeid(Player).name()].size() +
		_collection[typeid(Monster).name()].size()
	<< log::endl;
	
	for (auto it : _collection[typeid(Player).name()])
		delete it;
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