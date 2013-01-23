#include <system/dll/DllExportMacros.h>

extern "C" 
{
	const char DLLEXPORT *getName(void)
	{
		return "dumbMonster";
	}

	unsigned int DLLEXPORT getResourceId(void)
	{
		return 6;
	}

	unsigned int DLLEXPORT getPv(void)
	{
		return 1;
	}

	unsigned int DLLEXPORT getMunition(void)
	{
		return 0;
	}

	int DLLEXPORT timeToReload(void)
	{
		return 50;
	}

	int DLLEXPORT fireFrequence(void)
	{
		return 2500;
	}
}
