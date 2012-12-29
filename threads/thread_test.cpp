#ifdef  __gnu_linux__
# include <unistd.h>
#endif
#include <ctime>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#ifdef  __gnu_linux__
# include "UnixMutex.hh"
# include "UnixThread.hh"
#elif   _WIN32
# include "WinMutex.hh"
# include "WinThread.hh"
#endif

std::queue<std::string>	g_work_queue;
#ifdef  __gnu_linux__
IMutex				*g_work_queue_crit_section = new UnixMutex();
#elif   _WIN32
IMutex				*g_work_queue_crit_section = new WinMutex();
#endif

void	fill_work_queue(void)
{
	g_work_queue.push("chats");
	g_work_queue.push("bites");
	g_work_queue.push("culs");
	g_work_queue.push("anes");
	g_work_queue.push("violons");
	g_work_queue.push("frigos");
	g_work_queue.push("andouilles");
	g_work_queue.push("courgettes");
	g_work_queue.push("applications mobiles nulles a chier");
}

void	waitABit()
{
#ifdef __gnu_linux__
		usleep(1000000);
#elif _WIN32
		Sleep(1000);
#endif
}

void		*thread_routine(void *arg)
{
	int		*id = static_cast<int*>(arg);
	int		*nb_tasks = new int(0);
	bool	work_available = true;

	waitABit();
	while (work_available)
	{
		g_work_queue_crit_section->lock();
		work_available = (g_work_queue.empty() == false);
		if (work_available)
		{
			std::cout << "Thread " << *id << " : J'aime les " << g_work_queue.front() << " !" << std::endl;
			g_work_queue.pop();
			(*nb_tasks)++;
		}
		g_work_queue_crit_section->unlock();
#ifdef __gnu_linux__
		usleep(((rand() % 801) + 200) * 1000);
#elif _WIN32
		Sleep((rand() % 801) + 200);
#endif
	}
	std::cout << "Thread " << *id << " : I'm out of here! I did all those " << *nb_tasks << " tasks." << std::endl;
    delete id;
	return nb_tasks;
}

void	*lock_test_routine(void *arg)
{
	int	*id = static_cast<int*>(arg);

	waitABit();
	std::cout << "Thread " << *id << " locking..." << std::endl;
	g_work_queue_crit_section->lock();
	std::cout << "Thread " << *id << " locked! Sleeping, then unlocking..." << std::endl;
	waitABit();
	std::cout << "Thread " << *id << " unlocking..." << std::endl;
	g_work_queue_crit_section->unlock();
    delete id;
	return new int(0);
}

void	*multiple_lock_test_routine(void *arg)
{
	int	*id = static_cast<int*>(arg);

	waitABit();
	std::cout << "Thread " << *id << " locking..." << std::endl;
	g_work_queue_crit_section->lock();
	std::cout << "Thread " << *id << " locked! Sleeping, then locking two times now..." << std::endl;
	waitABit();
	g_work_queue_crit_section->lock();
	g_work_queue_crit_section->lock();
	std::cout << "Thread " << *id << " done! Unlocking and leaving now..." << std::endl;
	g_work_queue_crit_section->unlock();
	g_work_queue_crit_section->unlock();
	g_work_queue_crit_section->unlock();
    delete id;
	return new int(0);
}

void	*trylock_test_routine(void *arg)
{
	int	*id = static_cast<int*>(arg);
	
	waitABit();
	std::cout << "Thread " << *id << " trylocking..." << std::endl;
	if (g_work_queue_crit_section->trylock())
	{
		std::cout << "Success! Sleeping..." << std::endl;
		waitABit();
		g_work_queue_crit_section->unlock();
	}
	else
		std::cout << "Failure..." << std::endl;
	std::cout << "Thread " << *id << " leaving!" << std::endl;
    delete id;
	return new int(0);
}

#ifdef _WIN32
void	run_routine(std::function<void*(void*)> routine, WinThread *threads, int nb_threads)
{
	for (int i = 0; i < nb_threads; i++)
	{
		int *id = new int(i + 1);
		threads[i].start(routine, id);
		waitABit();
	}
	for (int i = 0; i < nb_threads; i++)
	{
		int	*ret = nullptr;
		threads[i].wait((void**)&ret);
		std::cout << "Thread " << i + 1 << " returned with " << *ret << std::endl;
        delete ret;
	}
	std::cout << "----------------------------------------------" << std::endl;
}
#elif __gnu_linux__
void	run_routine(std::function<void*(void*)> routine, UnixThread *threads, int nb_threads)
{
	for (int i = 0; i < nb_threads; i++)
	{
		int *id = new int(i + 1);
		threads[i].start(routine, id);
		waitABit();
	}
	for (int i = 0; i < nb_threads; i++)
	{
		int	*ret = nullptr;
		threads[i].wait((void**)&ret);
		std::cout << "Thread " << i + 1 << " returned with " << *ret << std::endl;
        delete ret;
	}
	std::cout << "----------------------------------------------" << std::endl;
}
#endif

int	main(int argc, char *argv[])
{
	int		nb_threads = 2;
#ifdef _WIN32
	WinThread	*threads = nullptr;
#elif __gnu_linux__
	UnixThread	*threads = nullptr;
#endif

	srand(time(nullptr));
	try {
		if (argc >= 2)
			nb_threads = std::stoi(argv[1]);
		if (nb_threads < 2)
			throw std::logic_error("invalid number of threads (minimum is 2)");
		std::cout << "Nb threads: " << nb_threads << std::endl;
		fill_work_queue();
		std::cout << "Creating threads..." << std::endl;
#if _WIN32
		threads = new WinThread[nb_threads];
#elif __gnu_linux__
		threads = new UnixThread[nb_threads];
#endif
		run_routine(&thread_routine, threads, nb_threads);
		run_routine(&trylock_test_routine, threads, nb_threads);
		run_routine(&lock_test_routine, threads, nb_threads);
		run_routine(&multiple_lock_test_routine, threads, nb_threads);
		std::cout << "All work is done!" << std::endl;
        delete [] threads;
        delete g_work_queue_crit_section;
		return EXIT_SUCCESS;
	} catch (std::exception& error) {
		std::cerr << "Exception caught: " << error.what() << std::endl;
	}
	return EXIT_FAILURE;
}
