#ifndef		_UNIT_FACTORY_HH_
# define	_UNIT_FACTORY_HH_

#include <vector>
#include <libs/system/log/Log.hh>
#include <typeinfo>
#include <memory>
#include "units/Unit.hh"
#include "units/Player.hh"

enum UnitType {
	PLAYER = 0,
};

class UnitFactory
{

public:
	UnitFactory(void);
	~UnitFactory(void);

public:
	template <typename T>
	std::unique_ptr<T> create(void) const
	{
		using namespace TBSystem;
		for (auto it : _collection)
		{
			if (it.first == typeid(T).name())
				return std::unique_ptr<T>(static_cast<T*>(it.second->clone()));
		}
		log::warn << "Factory : can't create this object (doesn't exist)" << log::endl;
		return NULL;
	}

private:
	std::vector<std::pair<const char *, Unit *>> _collection;
};

#endif /*_UNIT_FACTORY_HH_*/