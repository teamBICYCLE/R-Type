#include "WinMutex.hh"

WinMutex::WinMutex()
{
	InitializeCriticalSection(&_mutex);
}

WinMutex::~WinMutex()
{
	DeleteCriticalSection(&_mutex);
}

void	WinMutex::lock(void)
{
	EnterCriticalSection(&_mutex);
}

void	WinMutex::unlock(void)
{
	LeaveCriticalSection(&_mutex);
}

bool	WinMutex::trylock(void)
{
	if (TryEnterCriticalSection(&_mutex))
		return true;
	return false;
}