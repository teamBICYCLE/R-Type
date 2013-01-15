#include <iostream>
#include <exception>
#include "AnimationManager.hh"

using namespace Sprite;

AnimationManager::AnimationManager(void)
{}

AnimationManager::~AnimationManager(void)
{}

AnimationManager::AnimationManager(const AnimationManager &other)
{
	_animations = other._animations;
}

AnimationManager& AnimationManager::operator=(const AnimationManager &other)
{
	if (this != &other) {
		_animations = other._animations;
	}
	return (*this);
}

bool AnimationManager::addSource(const std::string& spriteFile, const std::string &cfgFile)
{
	try {
		_animations.insert(std::make_pair(spriteFile,
							SpriteBoard(spriteFile, cfgFile)));
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		return (false);
	}
	return (true);
}

bool AnimationManager::setAnimationName(const std::string &animName, const std::string &spriteFile)
{
	if (_animations.find(spriteFile) != _animations.end()) {
		_animations.find(spriteFile)->second.getAnimInfo()->setAnimationName(animName);
		return (true);
	} else {
		return (false);
	}
}

SpriteBoard &AnimationManager::operator[](const std::string &spriteFile)
{
	if (_animations.find(spriteFile) != _animations.end()) {
		return (_animations.find(spriteFile)->second);
	} else {
		throw std::invalid_argument("Can not find " + spriteFile + ".");
	}
}