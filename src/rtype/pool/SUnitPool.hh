#ifndef		_SUNIT_POOL_HH_
# define	_SUNIT_POOL_HH

# include "SUnitFactory.hh"
# include "UnitPool.hh"

class SUnitPool : public UnitPool
{

private:
	SUnitPool(void);
	~SUnitPool(void);

public:
	static SUnitPool *getInstance(void);
	static void	deleteInstance(void);
};

#endif /*!_GUNIT_POOL_HH_*/