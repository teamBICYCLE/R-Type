#ifndef		_GUNIT_POOL_HH_
# define	_GUNIT_POOL_HH

# include "UnitPool.hh"

class GUnitPool : public UnitPool
{

private:
	GUnitPool(void);
	~GUnitPool(void);

public:
	static GUnitPool *getInstance(void);
	static void	deleteInstance(void);
};

#endif /*!_GUNIT_POOL_HH_*/