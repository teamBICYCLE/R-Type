extern "C" 
{
	const char *getName(void)
	{
		return "dumbMonster";
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
		return 0;
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
