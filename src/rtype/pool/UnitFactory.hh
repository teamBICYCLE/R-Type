#ifndef		_UNIT_FACTORY_HH_
# define	_UNIT_FACTORY_HH_

#include <vector>
#include <libs/system/log/Log.hh>
#include <typeinfo>
#include <memory>
#include "units/Unit.hh"
#include "units/Monster.hh"
#include "units/Missile.hh"

class UnitFactory
{

public:
	UnitFactory(void);
	~UnitFactory(void);

public:
	template <typename T>
	T *create(void) const
	{
		using namespace TBSystem;
		for (auto it : _collection)
		{
			if (it.first == typeid(T).name())
				return (dynamic_cast<T*>(it.second->clone()));
		}
		log::warn << "Factory : can't create this object (" << typeid(T).name() << " doesn't exist)" << log::endl;
		return NULL;
	}

protected:
	std::vector<std::pair<const char *, Unit *>> _collection;
};

#endif /*_UNIT_FACTORY_HH_*/