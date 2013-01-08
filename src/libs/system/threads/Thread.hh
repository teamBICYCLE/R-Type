#ifndef     __THREAD_HH__
# define    __THREAD_HH__

# ifdef     __gnu_linux__
    #  include  "UnixThread.hh"
    typedef UnixThread  Thread;
# elif      _WIN32
    #  include  "WinThread.hh"
    typedef WinThread   Thread;
# else
    #  error    "Unsupported architecture."
# endif

#endif /* !__THREAD_HH__ */
