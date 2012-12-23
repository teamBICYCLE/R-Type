#include <cstring>
#include <string>
#include <stdexcept>
#include "UnixMutex.hh"

UnixMutex::UnixMutex()
    : _lockCount(0)
{
    if (pthread_mutex_init(&_mutex, nullptr) != 0)
        throw std::runtime_error("Failed to initialize pthread mutex");
}

UnixMutex::~UnixMutex()
{
    pthread_mutex_destroy(&_mutex);
}

void	UnixMutex::lock(void)
{
    int ret;

    if (_lockCount == 0)
    {
        if ((ret = pthread_mutex_lock(&_mutex)) != 0)
            throw std::runtime_error(std::string("Failed to lock mutex: ") + strerror(ret));
    }
    _lockCount++;
}

void	UnixMutex::unlock(void)
{
    int ret;

    if (_lockCount == 1)
    {
        if ((ret = pthread_mutex_unlock(&_mutex)) != 0)
            throw std::runtime_error(std::string("Failed to unlock mutex: ") + strerror(ret));
    }
    _lockCount--;
}

bool	UnixMutex::trylock(void)
{
    int ret = 0;

    if (_lockCount == 0)
        ret = pthread_mutex_trylock(&_mutex);
	if (ret == 0)
    {
        _lockCount++;
		return true;
    }
    if (ret != EBUSY)
        throw std::runtime_error(std::string("Failed to trylock mutex: ") + strerror(ret));
	return false;
}

