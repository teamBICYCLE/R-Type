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
# include "utilities/Vector2D.hh"


# ifdef     __gnu_linux__
	#define SHARED_EXT ".so"
# elif      _WIN32
	#define SHARED_EXT ".dll";
# else
#	error "Unsupported architecture."
# endif

class PatternManager
{

public:
	PatternManager(void);
	~PatternManager(void);

public:
	// list peut etre constante ?
	std::list<Unit *> get(const Vector2D &, const Vector2D &) const;

public:
	typedef struct MonsterDefinition
	{	
		unsigned int pv;
		unsigned int munition;
		std::chrono::milliseconds timeToReload;
		std::chrono::milliseconds timeBetweenFires;
	} MonsterDefinition;

private:
	void load(void);
	void loadShared(void);
	void checkShared(const std::string &);

private:
	std::vector<std::shared_ptr<Pattern>> _patterns;
	std::map<std::string, std::shared_ptr<MonsterDefinition>> _monsters;
};

#endif /*!_PATTERN_MANAGER_HH_*/