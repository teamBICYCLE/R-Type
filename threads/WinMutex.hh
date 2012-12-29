#ifndef		__WINMUTEX_HH__
# define	__WINMUTEX_HH__

# include	<Windows.h>
# include	"IMutex.hh"

class WinMutex : public IMutex
{
public:
	WinMutex();
	virtual ~WinMutex();

public:
	virtual void	lock(void);
	virtual void	unlock(void);
	virtual bool	trylock(void);

private:
	CRITICAL_SECTION	_mutex;
};

#endif // !__WINMUTEX_HH__
