#ifndef		_UNIT_POOL_HH_
# define	_UNIT_POOL_HH_

# include <memory>
# include <map>
# include <list>
# include <stdexcept>
# include <libs/system/log/Log.hh>
# include "units/Unit.hh"
# include "UnitFactory.hh"
# include "units/Player.hh"
# include "units/Monster.hh"

# define	PLAYER_NB	4
# define	MONSTER_NB	50
# define	ROCKET_NB	150

class UnitPool
{

private:
	UnitPool(void);
	~UnitPool(void);

public:
	static UnitPool *getInstance(void);
	static void	deleteInstance(void);

public:
	template <typename T>
	T *get(void)
	{
		const char *type = typeid(T).name();
		auto it = _collection.find(type);
		if (it != _collection.end())
		{
			T *ptr;
			if (!_collection[type].empty() > 0)
			{
				ptr = dynamic_cast<T *>(_collection[type].front());
				_collection[type].pop_front();
			}
			else
			{
				UnitFactory f;
				ptr = f.create<T>();
			}
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

private:
	std::map<const char *, std::list< Unit *>> _collection;
};

#endif /*!_UNIT_POOL_HH_*/