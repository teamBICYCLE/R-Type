#ifndef     __UNIXTHREAD_HH__
# define    __UNIXTHREAD_HH__

# include   <pthread.h>
# include   "IThread.hh"

class   UnixThread : public IThread
{
    public:
        UnixThread();
        virtual ~UnixThread();

    public:
        virtual bool	start(std::function<void*(void*)> routine, void *arg);
        virtual bool	terminate(void);
        virtual bool	wait(void **returnValue);
        virtual bool	isRunning(void) const;

    public:
        void            *internalRoutine(void);

    private:
        std::function<void*(void*)> _threadRoutine;
        void                        *_threadArg;
        pthread_t					_threadHandle;
        bool						_isRunning;
};

void    *unixThreadTrampolineRoutine(void *arg);

#endif /* !__UNIXTHREAD_HH__ */
