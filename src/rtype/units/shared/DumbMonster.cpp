#include <string>
#include <chrono>

extern "C" 
{
	const std::string getName(void)
	{
		return "dumbMonster";
	}

	unsigned int getResourceId(void)
	{
		return 2;
	}

	unsigned int getPv(void)
	{
		return 1;
	}

	unsigned int getMunition(void)
	{
		return 0;
	}

	const std::chrono::milliseconds timeToReload(void)
	{
		return std::chrono::milliseconds(50);
	}

	const std::chrono::milliseconds fireFrequence(void)
	{
		return std::chrono::milliseconds(2);
	}
}
