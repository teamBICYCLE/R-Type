#include "units/graphics/GPlayer.hh"
#include "GUnitFactory.hh"

GUnitFactory::GUnitFactory() :
	UnitFactory()
{
	_collection.push_back(std::make_pair(typeid(GPlayer).name(), new GPlayer()));
	//std::cout << _collection[typeid(GPlayer).name()] << std::endl;
}

GUnitFactory::~GUnitFactory()
{

}

