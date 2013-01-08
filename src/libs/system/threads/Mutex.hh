#ifndef     __MUTEX_HH__
# define    __MUTEX_HH__

# ifdef     __gnu_linux__
    #  include  "UnixMutex.hh"
    typedef UnixMutex  Mutex;
# elif      _WIN32
    #  include  "WinMutex.hh"
    typedef WinMutex   Mutex;
# else
    #  error    "Unsupported architecture."
# endif

#endif /* !__MUTEX_HH__ */
