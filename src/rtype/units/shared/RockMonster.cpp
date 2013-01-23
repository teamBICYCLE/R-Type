extern "C" 
{
	const char *getName(void)
	{
		return "rockMonster";
	}

	unsigned int getResourceId(void)
	{
		return 7;
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
