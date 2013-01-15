#include "SpriteBoard.hh"
#include <iostream>

namespace Sprite
{
	SpriteBoard::SpriteBoard(const std::string &imgFile, const std::string &cfgFile)
	{
		// _sprite = 
		_sprite = new Board(imgFile, cfgFile);
		_animInfos = _sprite->generateAnimInfo();
	}

	SpriteBoard::SpriteBoard(const SpriteBoard &other)
	{
		// _sprite = other._sprite;
		// _animInfos = other._animInfos;
		_sprite = new Board(*other._sprite);
		_animInfos = _sprite->generateAnimInfo();
		//new AnimationInfos(*other._animInfos);
	}

	SpriteBoard &SpriteBoard::operator=(const SpriteBoard &other)
	{
		if (this != &other) {
			_sprite = new Board(*other._sprite);
			_animInfos = _sprite->generateAnimInfo();
					// _sprite = other._sprite;
		// _animInfos = other._animInfos;
		}
		return (*this);
	}

	SpriteBoard::~SpriteBoard(void)
	{
		delete _sprite;
		delete _animInfos;
	}

	void SpriteBoard::setSprite(const Board &sprite)
	{
		delete _sprite; _sprite = new Board(sprite);
	}

	void SpriteBoard::setAnimation(const AnimationInfos &anim)
	{
		delete _animInfos; _animInfos = new AnimationInfos(anim);
	}

	Board *SpriteBoard::getSprite(void)
	{
 		return (_sprite);
	}

	AnimationInfos *SpriteBoard::getAnimInfo(void)
	{
		return (_animInfos);
	}
}