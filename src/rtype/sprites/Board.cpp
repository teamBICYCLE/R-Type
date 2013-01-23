#include "Board.hh"
#include <iostream>

using namespace Sprite;

Board::Board(const std::string &boardFile, const std::string &boardCfg)
{
	_texture = new sf::Texture;
	_board = new sf::Sprite;
	refreshMap(boardFile, boardCfg);
}

Board::Board(const Board &other)
{
	_animations = other._animations;
	_texture = other._texture;
	_board = other._board;
}

Board &Board::operator=(const Board &other)
{
	if (this != &other) {
		_animations = other._animations;
		_texture = other._texture;
		_board = other._board;
	}
	return *this;
}

Board::~Board(void)
{}

void Board::refreshMap(const std::string &boardFile, const std::string &boardCfg)
{
	try	{
		csv::Parser csvCfg = csv::Parser(boardCfg);
		if (!_texture->loadFromFile(boardFile)) {
			throw std::invalid_argument("Could not load image from [" + boardFile + "].");
		} else {
			_board->setTexture(*_texture);
		}
		if (csvCfg.columnCount() != SIZEY + 1) {
			throw std::invalid_argument("Badly formated config file : [" + boardCfg + "].");
		}
		refreshAnimMap(csvCfg);
	} catch (std::runtime_error &e) {
		throw std::invalid_argument("Could not load config file : [" + boardCfg + "]." + e.what());
    }
}

void Board::refreshAnimMap(csv::Parser &csvCfg)
{
	for (unsigned int i = 0; i < csvCfg.rowCount(); ++i) {
		_animations[csvCfg[i][FileIDX::NAME]] = createSpriteBoard(csvCfg, i);
	}
}

Animation Board::createSpriteBoard(csv::Parser &csvCfg, unsigned int cfgIndex)
{
	std::vector<sf::Rect<int>> tmp;
	csv::Row row = csvCfg[cfgIndex];
	unsigned int spritesNb = row.getValue<unsigned int>(FileIDX::SpriteLoaderNB)
	, origX                = row.getValue<unsigned int>(FileIDX::ORIGX)
	, origY                = row.getValue<unsigned int>(FileIDX::ORIGY)
	, sizeY                = row.getValue<unsigned int>(FileIDX::SIZEY)
	, sizeX                = row.getValue<unsigned int>(FileIDX::SIZEX);
	unsigned int duration  = row.getValue<unsigned int>(FileIDX::DURATION);

	if (spritesNb == 0) {
		throw std::invalid_argument("Animation [" + csvCfg[cfgIndex][FileIDX::NAME] + "] in file "
 									+ csvCfg.getFileName() + " has 0 sprites numbers");
	}
	for (unsigned int i = 0; i < spritesNb; ++i) {
		sf::Rect<int> tmpRect;
		tmpRect.width = sizeX;
		tmpRect.height = sizeY;
		tmpRect.top = origY;
		tmpRect.left = origX;
		origX += sizeX;
		tmp.push_back(tmpRect);
 	}
 	if (duration == 0) {
 		throw std::invalid_argument("Animation [" + csvCfg[cfgIndex][FileIDX::NAME] + "] in file "
 									+ csvCfg.getFileName() + " has 0 milliseconds duration");
 	}
	Animation sprites(tmp, duration);
	return (sprites);
}

sf::Sprite &Board::getSprite(const std::string &animName, std::chrono::milliseconds time, int nbPlay)
{
	if (_animations.find(animName) == _animations.end() || _animations[animName].getDuration().count() == 0 ||
		_animations[animName].getRects().size() == 0) {
	   _board->setTextureRect(sf::Rect<int>(0,0,0,0));
	} else if (nbPlay != -1 && static_cast<int>((time / (_animations[animName].getDuration().count())).count()) /
							(_animations[animName].getRects().size()) >= nbPlay) {
		_board->setTextureRect(sf::Rect<int>(0,0,0,0));
	} else {
	_board->setTextureRect(_animations[animName][static_cast<int>((time /
				(_animations[animName].getDuration().count())).count())
				% (_animations[animName].getRects().size())]);
	}
	return (*_board);
}

AnimationInfos *Board::generateAnimInfo(void)
{
	return new AnimationInfos(*this);
}

bool Board::hasSpriteNamed(const std::string &name) const
{
	if (_animations.find(name) != _animations.end()) {
		return (true);
	}
	return (false);
}
