#include "UnitFactory.hh"
#include "units/Player.hh"
#include "units/Monster.hh"

UnitFactory::UnitFactory(void)
{
	_collection.push_back(std::make_pair(typeid(Player).name(), new Player()));
	_collection.push_back(std::make_pair(typeid(Monster).name(), new Monster()));
}

UnitFactory::~UnitFactory(void)
{
}