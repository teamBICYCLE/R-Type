#ifndef     __UNIXMUTEX_HH__
# define    __UNIXMUTEX_HH__

# include   <pthread.h>
# include   "IMutex.hh"

class   UnixMutex : public IMutex
{
    public:
        UnixMutex();
        virtual ~UnixMutex();

    public:
        virtual void	lock(void);
        virtual void	unlock(void);
        virtual bool	trylock(void);

    private:
        pthread_mutex_t     _mutex;
        pthread_mutexattr_t _mutexAttr;
};

#endif /* !__UNIXMUTEX_HH__ */
