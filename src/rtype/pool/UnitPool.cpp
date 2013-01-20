#include "UnitPool.hh"

static UnitPool *	_instance = NULL;

UnitPool::UnitPool(void)
{
	
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