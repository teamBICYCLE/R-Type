#include <system/exploredir/ExploreDir.hh>
#include <system/log/Log.hh>
#include <fstream>
#include "PatternManager.hh"

PatternManager::PatternManager(void)
{
	PatternManager::load();	
}

PatternManager::~PatternManager(void)
{

}

void PatternManager::load(void)
{
	using namespace TBSystem;
	std::vector<std::string> files = ExploreDir::run("resources/patterns");
	if (files.size() < 0)
		log::warn << "No patterns defined for generate random Monsters" << log::endl;
	for (auto it : files)
		_patterns.push_back(Pattern(it));
}

std::list<Unit *> PatternManager::get(const Vector2D &left, const Vector2D &right) const
{
	// TMP
	std::list<Unit *> ret;
	ret.push_back(new Unit());
	return ret;
}