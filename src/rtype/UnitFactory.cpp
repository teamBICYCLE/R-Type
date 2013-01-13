#include "UnitFactory.hh"
#include "units/Player.hh"

UnitFactory::UnitFactory(void)
{
	_collection.push_back(std::make_pair(typeid(Player).name(), new Player()));
}

UnitFactory::~UnitFactory(void)
{
	for (auto it : _collection)
		delete it.second;
}