#ifndef		_PATTERN_MANAGER_HH_
# define	_PATTERN_MANAGER_HH_

# include <vector>
# include <list>
# include "Pattern.hh"
# include "units/Unit.hh"

class PatternManager
{

public:
	PatternManager(void);
	~PatternManager(void);

public:
	// list peut etre constante ?
	std::list<Unit *> get(const Vector2D &, const Vector2D &) const;
	//void loadFile(const std::string &);

private:
	void load(void);

private:
	std::vector<Pattern> _patterns;
};

#endif /*!_PATTERN_MANAGER_HH_*/