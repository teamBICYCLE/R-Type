extern "C" 
{
	const char *getName(void)
	{
		return "advancedMonster";
	}

	unsigned int getResourceId(void)
	{
		return 6;
	}

	unsigned int getPv(void)
	{
		return 2;
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
		return 5000;
	}
}