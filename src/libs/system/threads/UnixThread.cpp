#include <cstdlib>
#include "UnixThread.hh"

UnixThread::UnixThread()
	: _threadArg(nullptr)
    , _isRunning(false)
{
}

UnixThread::~UnixThread()
{
	terminate();
}

bool	UnixThread::start(std::function<void*(void*)> routine, void *arg)
{
	if (_isRunning == false)
	{
        _threadRoutine = routine;
        _threadArg = arg;
		if (pthread_create(&_threadHandle, nullptr, &unixThreadTrampolineRoutine, this) != 0)
        {
            _threadRoutine = nullptr;
            _threadArg = nullptr;
			return false;
        }
		_isRunning = true;
		return true;
	}
	return false;
}

bool	UnixThread::terminate(void)
{
    if (_isRunning)
    {
        //problem if cancel successful but wait fails? When it is really cancelled,
        //the _isRunning boolean will probably still evaluate to true
        if (pthread_cancel(_threadHandle) == 0)
            return wait(nullptr);
    }
	return false;
}

bool	UnixThread::wait(void **returnValue)
{
	if (_isRunning)
	{
		if (pthread_join(_threadHandle, returnValue) == 0)
		{
            _threadRoutine = nullptr;
            _threadArg = nullptr;
            _isRunning = false;
			return true;
		}
	}
	return false;
}

bool	UnixThread::isRunning(void) const
{
	return _isRunning;
}

void    *UnixThread::internalRoutine(void)
{
  return _threadRoutine(_threadArg);
}

void    *unixThreadTrampolineRoutine(void *arg)
{
  return reinterpret_cast<UnixThread*>(arg)->internalRoutine();
}
