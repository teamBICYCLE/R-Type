#ifndef		__WINTHREAD_HH__
# define	__WINTHREAD_HH__

# include	<Windows.h>
# include	"IThread.hh"

class WinThread : public IThread
{
public:
	WinThread();
	virtual ~WinThread();

public:
	virtual bool	start(std::function<void*(void*)> routine, void *arg);
	virtual bool	terminate(void);
	virtual bool	wait(void **returnValue);
	virtual bool	isRunning(void) const;

public:
	DWORD WINAPI	internalRoutine(void);

private:
	void			cleanUp(void);

private:
	std::function<void*(void*)>	_threadRoutine;
	void						*_threadArg;
	void						*_threadReturnValue;
	HANDLE						_threadHandle;
	bool						_isRunning;
};

DWORD WINAPI	winThreadTrampolineRoutine(LPVOID arg);

#endif /* !__WINTHREAD_HH__ */