#include <system/exploredir/ExploreDir.hh>
#include <system/log/Log.hh>
#include <system/log/Log.hh>
#include <system/dll/DLoader.hh>
#include <ctime>
#include <cstdlib> 
#include "UnitPool.hh"
#include "PatternManager.hh"

PatternManager::PatternManager(void)
{
	PatternManager::load();
	PatternManager::loadShared();
	std::srand(std::time(0));
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

	std::vector<std::string> files = ExploreDir::run("resources/shared", SHARED_EXT);
	if (files.size() < 0)
		log::warn << "No Monster shared libraries" << log::endl;
	for (auto it : files)
	{
		try {
			PatternManager::checkShared(it);
		} catch (std::logic_error &e) {
			log::warn << "Invalid Monster : " << e.what() << log::endl;
		}
	}
}

void PatternManager::checkShared(const std::string &file)
{
	std::cout << "load shared " << file << std::endl;
	DLoader loader(file);
	std::shared_ptr<MonsterDefinition> def = std::shared_ptr<MonsterDefinition>(new MonsterDefinition());
	std::function<const std::string (void)>n = loader.load<const std::string (void)>("getName");
	std::function<unsigned int (void)>p = loader.load<unsigned int(void)>("getPv");
	std::function<unsigned int (void)>m = loader.load<unsigned int(void)>("getMunition");
	std::function<const std::chrono::milliseconds (void)>r = loader.load<const std::chrono::milliseconds (void)>("timeToReload");
	std::function<const std::chrono::milliseconds (void)>b = loader.load<const std::chrono::milliseconds (void)>("timeBetweenFires");
	def->pv = p();
	def->munition = m();
	def->timeToReload = r();
	def->timeBetweenFires = b();
	_monsters.insert(std::make_pair(n(), def));
}

std::list<Unit *> PatternManager::get(const Vector2D &left, const Vector2D &right) const
{
	using namespace TBSystem;
	int random = (std::rand() % _patterns.size());
	//std::shared_ptr<Pattern> pattern = _patterns[random];
	std::list<std::shared_ptr<Pattern::Element>> elements;
	elements = _patterns[random]->getPatternElements();
	UnitPool *pool = UnitPool::getInstance();
	std::list<Unit *> ret;

	std::cout << random << std::endl;
	for (auto item  = elements.begin(); item != elements.end(); ++item)
	{
		if (_monsters.find((*item)->type) != _monsters.end())
		{
			Monster *m = pool->get<Monster>();
			// operation sur le m;
			ret.push_back(m);
			std::cout << (*item)->posx << " " << (*item)->posy << " " << (*item)->type << " " << (*item)->moveStyle << std::endl;
		}
		else
			log::warn << "Undefined reference to Monster " << (*item)->type << " (passed)" << log::endl;
	}

	std::cout << ret.size() << std::endl;
	return ret;
}