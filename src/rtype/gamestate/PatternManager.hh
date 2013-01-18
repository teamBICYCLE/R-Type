#ifndef		_PATTERN_MANAGER_HH_
# define	_PATTERN_MANAGER_HH_

# include <vector>
# include <list>
# include <memory>
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

private:
	void load(void);
	void loadShared(void);

private:
	std::vector<std::shared_ptr<Pattern>> _patterns;
};

#endif /*!_PATTERN_MANAGER_HH_*/