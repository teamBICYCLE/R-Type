#include <cstdlib>
#include "WinThread.hh"

WinThread::WinThread()
	: _threadArg(nullptr)
	, _threadReturnValue(nullptr)
	, _threadHandle(nullptr)
	, _isRunning(false)
{
}

WinThread::~WinThread()
{
	terminate();
}

bool	WinThread::start(std::function<void*(void*)> routine, void *arg)
{
	if (_isRunning == false)
	{
		_threadRoutine = routine;
		_threadArg = arg;
		_threadHandle = CreateThread(nullptr, 0, &winThreadTrampolineRoutine, this, 0, nullptr);
		//passer de CreateThread a _beginthreadex ?
		if (_threadHandle == nullptr)
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

bool	WinThread::terminate(void)
{
	if (TerminateThread(_threadHandle, EXIT_SUCCESS))
	{
		cleanUp();
		return true;
	}
	return false;
}

bool	WinThread::wait(void **returnValue)
{
	if (_isRunning)
	{
		DWORD	ret = WaitForSingleObject(_threadHandle, INFINITE);

		if (ret != WAIT_FAILED)
		{
			if (returnValue != nullptr)
				*returnValue = _threadReturnValue;
			cleanUp();
			return true;
		}
	}
	return false;
}

bool	WinThread::isRunning(void) const
{
	return _isRunning;
}

DWORD WINAPI	WinThread::internalRoutine(void)
{
	_threadReturnValue = _threadRoutine(_threadArg);
	return EXIT_SUCCESS;
}

void		WinThread::cleanUp(void)
{
	CloseHandle(_threadHandle); _threadHandle = nullptr;
	_threadRoutine = nullptr;
	_threadArg = nullptr;
	_threadReturnValue = nullptr;
	_isRunning = false;
}

DWORD WINAPI	winThreadTrampolineRoutine(LPVOID arg)
{
	return reinterpret_cast<WinThread*>(arg)->internalRoutine();
}