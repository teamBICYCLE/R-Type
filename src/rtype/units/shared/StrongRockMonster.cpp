extern "C" 
{
	const char *getName(void)
	{
		return "strongRockMonster";
	}

	unsigned int getResourceId(void)
	{
		return 8;
	}

	unsigned int getPv(void)
	{
		return 2;
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
