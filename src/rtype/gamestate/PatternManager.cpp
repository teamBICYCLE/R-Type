#include <system/exploredir/ExploreDir.hh>
#include <system/log/Log.hh>
#include <system/log/Log.hh>
#include <system/dll/DLoader.hh>
#include <ctime>
#include <cstdlib> 
#include <cmath>
#include "pool/SUnitPool.hh"
#include "PatternManager.hh"

PatternManager::PatternManager(void)
{
	std::srand(std::time(0));
	PatternManager::load();
	PatternManager::loadShared();
	PatternManager::createMoveStyles();
}

PatternManager::~PatternManager(void)
{
	_patterns.clear();
}

void PatternManager::load(void)
{
	using namespace TBSystem;
	std::vector<std::string> files = ExploreDir::run(PATTERNS_PATH);
	if (files.size() == 0)
		log::warn << "No patterns defined for generate random Monsters" << log::endl;
	for (auto it : files)
		_patterns.push_back(std::shared_ptr<Pattern>(new Pattern(it)));
}

void PatternManager::loadShared(void)
{
	using namespace TBSystem;

	std::vector<std::string> files = ExploreDir::run(SHARED_PATH, SHARED_EXT);
	if (files.size() == 0)
		log::warn << "No shared libraries for Monster" << log::endl;
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
	std::function<unsigned int (void)>i = loader.load<unsigned int(void)>("getResourceId");
	std::function<unsigned int (void)>p = loader.load<unsigned int(void)>("getPv");
	std::function<unsigned int (void)>m = loader.load<unsigned int(void)>("getMunition");
	std::function<const std::chrono::milliseconds (void)>r = loader.load<const std::chrono::milliseconds (void)>("timeToReload");
	std::function<const std::chrono::milliseconds (void)>f = loader.load<const std::chrono::milliseconds (void)>("fireFrequence");
	def->name = n();
	def->resourceId = i();
	def->pv = p();
	def->munition = m();
	def->timeToReload = r();
	def->fireFrenquence = f();
	_monsters.insert(std::make_pair(n(), def));
}

void PatternManager::createMoveStyles(void)
{
	moveStyle linearfct = [](const Vector2D &pos) {
		(void)pos;

		Vector2D v; v.x -= 1 / MONSTER_SPEED;
		return v;
	};

	moveStyle sinfct = [](const Vector2D &pos) {

		// float posx = pos.x * 800;
		// float posy = pos.y * 800;
		// float newPosx = posx;
		// float newPosy = std::sin(pos.x)
		Vector2D newPos(pos.x, std::sin(pos.x));
		//Vector2D v(newPos - pos) / MONSTER_SPEED;
		return (newPos - pos);
	};

	_moveStyles.insert(std::make_pair("linear", linearfct));
	_moveStyles.insert(std::make_pair("sin", sinfct));
}

std::list<Unit *> PatternManager::get(void) const
{
	using namespace TBSystem;

	int random = (std::rand() % _patterns.size());
	std::list<std::shared_ptr<Pattern::Element>> elements;
	elements = _patterns[random]->getPatternElements();
	SUnitPool *pool = SUnitPool::getInstance();
	std::list<Unit *> ret;

	for (auto item  = elements.begin(); item != elements.end(); ++item)
	{
		auto sharedm = _monsters.find((*item)->type);
		if (sharedm != _monsters.end())
		{
			std::shared_ptr<MonsterDefinition> sharedDef = sharedm->second;
			Monster *monster = pool->get<Monster>();

			// load definition in monster
			//monster->setSpritePath(SPRITE_PATH + sharedDef->name);
			monster->setResourceId(sharedDef->resourceId);
			monster->setPv(sharedDef->pv);
			monster->setMunition(sharedDef->munition);
			monster->setTimeToReload(sharedDef->timeToReload);
			monster->setFireFrequence(sharedDef->fireFrenquence);

			// load pattern informations in monster
			monster->setPos(Vector2D((*item)->posx, (*item)->posy));
			auto style = _moveStyles.find((*item)->moveStyle);
			if (style == _moveStyles.end())
				style = _moveStyles.find("linear");
			monster->setMoveStyle(style->second);
			ret.push_back(monster);
			//std::cout << (*item)->posx << " " << (*item)->posy << " " << (*item)->type << " " << (*item)->moveStyle << std::endl;
		}
		else
			log::warn << "Undefined reference to Monster " << (*item)->type << " (passed)" << log::endl;
	}

	return ret;
}