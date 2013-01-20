#include "units/Player.hh"
#include "units/Monster.hh"
#include "units/graphics/GPlayer.hh"
#include "SUnitFactory.hh"

SUnitFactory::SUnitFactory() :
	UnitFactory()
{
	_collection.push_back(std::make_pair(typeid(Player).name(), new Player()));
	_collection.push_back(std::make_pair(typeid(Monster).name(), new Monster()));
}

SUnitFactory::~SUnitFactory()
{

}
