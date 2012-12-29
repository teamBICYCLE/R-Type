#include <cstring>
#include <string>
#include <stdexcept>
#include "UnixMutex.hh"

UnixMutex::UnixMutex()
{
    int ret;

    if ((ret = pthread_mutexattr_init(&_mutexAttr)) != 0)
        throw std::runtime_error(std::string("Failed to initialize pthread mutexattr: ") + strerror(ret));
    pthread_mutexattr_settype(&_mutexAttr, PTHREAD_MUTEX_RECURSIVE);
    if ((ret = pthread_mutex_init(&_mutex, &_mutexAttr)) != 0)
        throw std::runtime_error(std::string("Failed to initialize pthread mutex: ") + strerror(ret));
}

UnixMutex::~UnixMutex()
{
    pthread_mutexattr_destroy(&_mutexAttr);
    pthread_mutex_destroy(&_mutex);
}

void	UnixMutex::lock(void)
{
    int ret;

    if ((ret = pthread_mutex_lock(&_mutex)) != 0)
        throw std::runtime_error(std::string("Failed to lock mutex: ") + strerror(ret));
}

void	UnixMutex::unlock(void)
{
    int ret;

    if ((ret = pthread_mutex_unlock(&_mutex)) != 0)
        throw std::runtime_error(std::string("Failed to unlock mutex: ") + strerror(ret));
}

bool	UnixMutex::trylock(void)
{
    int ret;

    ret = pthread_mutex_trylock(&_mutex);
    if (ret == 0)
        return true;
    if (ret != EBUSY)
        throw std::runtime_error(std::string("Failed to trylock mutex: ") + strerror(ret));
	return false;
}

