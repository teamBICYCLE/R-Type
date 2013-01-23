#ifndef		_UNIT_POOL_HH_
# define	_UNIT_POOL_HH_

# include <memory>
# include <map>
# include <list>
# include <stdexcept>
# include <libs/system/log/Log.hh>
# include "units/Unit.hh"
# include "pool/UnitFactory.hh"
# include "units/Player.hh"
# include "units/graphics/GPlayer.hh"
# include "units/graphics/GUnit.hh"
# include "units/Monster.hh"
# include "units/Missile.hh"

# define	PLAYER_NB	4
# define	MONSTER_NB	100
# define	ROCKET_NB	300


class UnitPool
{

public:
	
	enum Type {
		GRAPHIC = 0,
		SERVER = 1
	};

public:
	UnitPool(const std::shared_ptr<UnitFactory> &);
	virtual ~UnitPool(void);

public:
	
	template <typename T>
	T *get(void)
	{
		const char *type = typeid(T).name();
		auto it = _collection.find(type);
		if (it != _collection.end())
		{
			T *ptr = nullptr;
			if (!_collection[type].empty())
			{
				ptr = dynamic_cast<T *>(_collection[type].front());
				_collection[type].pop_front();
			}
			else {
				ptr = _factory->create<T>();
			}
			ptr->setId(_currentId++);
			return ptr;
		}
		else
		{
			using namespace TBSystem;
			std::string typeStr(type);
			log::err << "Pool : can't return an object of type " + typeStr << log::endl;
			throw std::logic_error("Pool : can't return an object of type " + typeStr);
		}
	}

	template <typename T>
	bool release(T* ptr)
	{
		const char *type = typeid(T).name();
		auto found = find_if(_collection[type].begin(), _collection[type].end(),
							[ptr](Unit *t) -> bool { return (ptr == t); });
		auto it = _collection.find(type);
		if (found == _collection[type].end() && it != _collection.end() && ptr)
		{
			ptr->reset();
			_collection[type].push_back(ptr);
			return true;
		}
		using namespace TBSystem;
		log::warn << "Pool : can't release an object of type " + std::string(type) + " or a non-valid pointer" << log::endl;
		return false;
	}

protected:
	std::map<const char *, std::list< Unit *>> _collection;
	unsigned int _currentId;
	std::shared_ptr<UnitFactory> _factory;
};

#endif /*!_UNIT_POOL_HH_*/