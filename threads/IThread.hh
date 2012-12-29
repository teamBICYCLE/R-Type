#ifndef		__ITHREAD_HH__
# define	__ITHREAD_HH__

# include	<functional>

class IThread
{
public:
	virtual ~IThread() {}

public:
	virtual bool	start(std::function<void*(void*)> routine, void *arg) = 0;

	/**
	* Terminates a thread.
	*
	* Do NOT use it, it's dangerous (at least on Windows).
	* Any resource allocated, any mutex locked will be lost.
	* To stop a thread, set a condition on your thread's loop,
	* change it when you want it to stop and then wait for it.
	*/
	virtual bool	terminate(void) = 0;
	virtual bool	wait(void **returnValue) = 0;
	virtual bool	isRunning(void) const = 0;
};

#endif // !__ITHREAD_HH__
