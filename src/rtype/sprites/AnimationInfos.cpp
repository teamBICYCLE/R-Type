#include "AnimationInfos.hh"

using namespace Sprite;

AnimationInfos::AnimationInfos(const Board &spriteBoard)
: _spriteBoard(spriteBoard), _nbPlay(-1)
{
	
}

AnimationInfos::AnimationInfos(const AnimationInfos &other)
: _currentAnim(other._currentAnim), _currentSpriteTime(other._currentSpriteTime),
_spriteBoard(other._spriteBoard), _nbPlay(other._nbPlay)
{}

AnimationInfos &AnimationInfos::operator=(const AnimationInfos &other)
{
	if (this != &other) {
		_currentAnim = other._currentAnim;
		_currentSpriteTime = other._currentSpriteTime;
		_spriteBoard = other._spriteBoard;
		_nbPlay = other._nbPlay;
	}
	return (*this);
}

AnimationInfos::~AnimationInfos(void)
{
}

bool AnimationInfos::setAnimationName(const std::string &animName)
{
	if (_spriteBoard.hasSpriteNamed(animName)) {
		if (_currentAnim != animName) {
			_currentAnim = animName;
			startAnimation();
		}
		return (true);
	}
	return (false);
}

void AnimationInfos::startAnimation(void)
{
	_currentSpriteTime = std::chrono::steady_clock::now();
}

std::chrono::milliseconds AnimationInfos::getDurationAnimation(void)
{
	return (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _currentSpriteTime));
}

sf::Sprite &AnimationInfos::getSprite(void)
{
	return _spriteBoard.getSprite(_currentAnim, getDurationAnimation(), _nbPlay);
}

void AnimationInfos::setPlayAnimNumber(int nbPlay)
{
	_nbPlay = nbPlay;
}