#ifndef		__ITHREAD_HH__
# define	__ITHREAD_HH__

# include	<functional>

class IThread
{
public:
	virtual ~IThread() {}

public:
	virtual bool	start(std::function<void*(void*)> routine, void *arg) = 0;
	virtual bool	terminate(void) = 0;
	virtual bool	wait(void **returnValue) = 0;
	virtual bool	isRunning(void) const = 0;
};

#endif // !__ITHREAD_HH__
