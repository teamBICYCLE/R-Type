#include <system/exploredir/ExploreDir.hh>
#include <system/log/Log.hh>
#include <system/log/Log.hh>
#include <system/dll/DLoader.hh>
#include <ctime>
#include <cstdlib> 
#include <cmath>
#include "pool/UnitPool.hh"
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
	DLoader loader(file);
	std::shared_ptr<MonsterDefinition> def = std::shared_ptr<MonsterDefinition>(new MonsterDefinition());
	std::function<const char*(void)>n = loader.load<const char*(void)>("getName");
	std::function<unsigned int (void)>i = loader.load<unsigned int(void)>("getResourceId");
	std::function<unsigned int (void)>p = loader.load<unsigned int(void)>("getPv");
	std::function<unsigned int (void)>m = loader.load<unsigned int(void)>("getMunition");
	std::function<int (void)>r = loader.load<int (void)>("timeToReload");
	std::function<int (void)>f = loader.load<int (void)>("fireFrequence");
	def->name = n();
	def->resourceId = i();
	def->pv = p();
	def->munition = m();
	def->timeToReload = r();
	unsigned int fireFrequence = f();
	if (fireFrequence < 1000)
		fireFrequence = 1000;
	def->fireFrenquence = fireFrequence;
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
	    Vector2D ret;
	    ret.x = -1;
	    ret.y = std::sin(pos.x * 20); 
	    ret.normalize();
	    ret /= MONSTER_SPEED;
	    ret.y *= 1;
	    return (ret);
	};

	_moveStyles.insert(std::make_pair("linear", linearfct));
	_moveStyles.insert(std::make_pair("sin", sinfct));
}

std::list<Monster*> PatternManager::get(const std::shared_ptr<UnitPool> &pool) const
{
	using namespace TBSystem;

	std::list<Monster*> ret;
	if (_patterns.size())
	{
		int random = (std::rand() % _patterns.size());
		std::list<std::shared_ptr<Pattern::Element>> elements;
		elements = _patterns[random]->getPatternElements();

		for (auto item  = elements.begin(); item != elements.end(); ++item)
		{
			auto sharedm = _monsters.find((*item)->type);
			if (sharedm != _monsters.end())
			{
				std::shared_ptr<MonsterDefinition> sharedDef = sharedm->second;
				Monster *monster = pool->get<Monster>();
				if (monster)
				{
					// load definition in monster
					monster->setResourceId(sharedDef->resourceId);
					monster->setPv(sharedDef->pv);
					monster->setCanShoot(static_cast<bool>(sharedDef->munition));
					monster->setTimeToReload(std::chrono::milliseconds(sharedDef->timeToReload));
					monster->setFireFrequence(std::chrono::milliseconds(sharedDef->fireFrenquence));

					// load pattern informations in monster
					monster->setPos(Vector2D((*item)->posx, (*item)->posy));
					auto style = _moveStyles.find((*item)->moveStyle);
					if (style == _moveStyles.end())
						style = _moveStyles.find("linear");
					monster->setMoveStyle(style->second);
					ret.push_back(monster);
				}
			}
			else
				log::warn << "Undefined reference to Monster " << (*item)->type << " (passed)" << log::endl;
		}
	}
	return ret;
}
