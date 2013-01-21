#include "SUnitPool.hh"

//static SUnitPool *	_instance = NULL;

SUnitPool::SUnitPool(void) :
	UnitPool()
{
	SUnitFactory f;

	// create Players
	for (int i = 0; i != PLAYER_NB; ++i)
		_collection[typeid(Player).name()].push_back(f.create<Player>());

	// create Monsters
	for (int i = 0; i != MONSTER_NB; ++i)
		_collection[typeid(Monster).name()].push_back(f.create<Monster>());
}

SUnitPool::~SUnitPool(void)
{
	for (auto it : _collection[typeid(Player).name()])
		delete it;

	for (auto it : _collection[typeid(Monster).name()])
		delete it;
}

// SUnitPool *SUnitPool::getInstance(void)
// {
// 	if (!_instance)
// 		_instance = new SUnitPool();
// 	return _instance;
// }

// void	SUnitPool::deleteInstance(void)
// {
// 	delete _instance;
// 	_instance = NULL;
// }