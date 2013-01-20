#include "iostream"
#include "system/log/Log.hh"
#include "PreGame.hh"

int main(int ac, char *av[])
{
	if (ac < 3) {
		TBSystem::log::err << "Error : Usage : " << av[0] << " + ip + port" << TBSystem::log::endl;
	} else {
		PreGame game(av[1], av[2]);
		game.run();
	}
	return (0);
}