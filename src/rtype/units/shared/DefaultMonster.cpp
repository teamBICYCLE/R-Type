#include <string>
#include <chrono>

extern "C" 
{
	const char *getName(void)
	{
		return "defaultMonster";
	}

	unsigned int getResourceId(void)
	{
		return 6;
	}

	unsigned int getPv(void)
	{
		return 1;
	}

	unsigned int getMunition(void)
	{
		return 10;
	}

	int timeToReload(void)
	{
		return 50;
	}

	int fireFrequence(void)
	{
		return 2500;
	}
}
