#include "Animation.hh"

using namespace Sprite;

Animation::Animation(const std::vector<sf::Rect<int>> &sprite, const float duration)
	: _sprite(sprite), _duration((int)duration)
{}

Animation::Animation(const Animation &other)
{
	_sprite = other._sprite;
	_duration = other._duration;
}

Animation &Animation::operator=(const Animation &other)
{
	if (this != &other) {
		_sprite = other._sprite;
		_duration = other._duration;
	}
	return (*this);
}

Animation::~Animation(void)
{}

void Animation::setRects(const std::vector<sf::Rect<int>> &sprite)
{
	_sprite = sprite;
}

void Animation::setDuration(const std::chrono::milliseconds duration)
{
	_duration = duration;
}

std::vector<sf::Rect<int>> Animation::getRects(void) const
{
	return _sprite;
}

const std::chrono::milliseconds Animation::getDuration(void) const
{
	return _duration;
}

sf::Rect<int> Animation::operator[](const uint position) const
{
	return _sprite[position];
}