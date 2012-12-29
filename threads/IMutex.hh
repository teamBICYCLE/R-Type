#ifndef		__IMUTEX_HH
# define	__IMUTEX_HH__

class IMutex
{
public:
	virtual	~IMutex() {}

public:
	virtual void	lock(void) = 0;
	virtual void	unlock(void) = 0;
	virtual bool	trylock(void) = 0;
};

#endif // !__IMUTEX_HH
