#ifndef		_DEFAULT_MONSTER_HH_
# define	_DEFAULT_MONSTER_HH_

# include "ISharedMonster.hh"

class DefaultMonster : public ISharedMonster
{

public:
	DefaultMonster(void);
	virtual ~DefaultMonster(void);

private:
	std::string _name;
};

#endif /*!_DEFAULT_MONSTER_HH_*/