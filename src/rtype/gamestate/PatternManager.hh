#ifndef		_PATTERN_MANAGER_HH_
# define	_PATTERN_MANAGER_HH_

# include <vector>
# include <list>
# include <memory>
# include <chrono>
# include <memory>
# include <map>
# include "Pattern.hh"
# include "units/Unit.hh"
# include "pool/UnitPool.hh"
# include "utilities/Vector2D.hh"

# define MONSTER_SPEED	500.f

# ifdef     __gnu_linux__
	#define SHARED_EXT ".so"
# elif      _WIN32
	#define SHARED_EXT ".dll"
# else
#	error "Unsupported architecture."
# endif

typedef std::function<const Vector2D(const Vector2D &)> moveStyle;

class PatternManager
{

public:
	PatternManager(void);
	~PatternManager(void);

public:
	// list peut etre constante ?
	std::list<Monster*> get(const std::shared_ptr<UnitPool> &pool) const;

public:
	typedef struct MonsterDefinition
	{	
		const char *name;
		unsigned int resourceId;
		unsigned int pv;
		unsigned int munition;
		int timeToReload;
		int fireFrenquence;
	} MonsterDefinition;

private:
	void load(void);
	void loadShared(void);
	void checkShared(const std::string &);
	void createMoveStyles(void);

private:
	std::vector<std::shared_ptr<Pattern>> _patterns;
	std::map<std::string, std::shared_ptr<MonsterDefinition>> _monsters;
	std::map<std::string, moveStyle> _moveStyles;
};

#endif /*!_PATTERN_MANAGER_HH_*/
