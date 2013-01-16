#include <system/exploredir/ExploreDir.hh>
#include <system/log/Log.hh>
#include <system/log/Log.hh>
#include <system/dll/DLoader.hh>
#include "PatternManager.hh"

PatternManager::PatternManager(void)
{
	PatternManager::load();
	PatternManager::loadShared();
}

PatternManager::~PatternManager(void)
{
	_patterns.clear();
}

void PatternManager::load(void)
{
	using namespace TBSystem;
	std::vector<std::string> files = ExploreDir::run("resources/patterns");
	if (files.size() < 0)
		log::warn << "No patterns defined for generate random Monsters" << log::endl;
	for (auto it : files)
		_patterns.push_back(std::shared_ptr<Pattern>(new Pattern(it)));
}

void PatternManager::loadShared(void)
{
	using namespace TBSystem;
	std::vector<std::string> files = ExploreDir::run("resources/shared", "dll");
	if (files.size() < 0)
		log::warn << "No Monster shared libraries" << log::endl;
	for (auto it : files)
		std::cout << it << std::endl;
}

std::list<Unit *> PatternManager::get(const Vector2D &left, const Vector2D &right) const
{
	// TMP
	for (auto it : _patterns)
	{
		std::list<std::shared_ptr<Pattern::Element>> elements;
		elements = it->getPatternElements();
		for (auto item  = elements.begin(); item != elements.end(); ++item)
		{
			std::cout << (*item)->posx << " " << (*item)->posy << " " << (*item)->type << " " << (*item)->moveStyle << std::endl;
		}
	}

	std::list<Unit *> ret;
	ret.push_back(new Unit());
	return ret;
}