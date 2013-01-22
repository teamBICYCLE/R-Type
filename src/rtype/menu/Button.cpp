#include "Button.hh"

Button::Button(const sf::Vector2f& dimension, const sf::Vector2f& position, const std::string &texture)
  : _param(NULL)
{
  _texture.loadFromFile(texture, sf::IntRect(position.x, position.y, dimension.x, dimension.y));
  _sprite.setTexture(_texture);
  _sprite.setPosition(position);
  _dimension = dimension;
}

Button::~Button()
{
}

void	Button::draw(sf::RenderTarget& target)
{
  target.draw(_sprite);
}

void	Button::onClick(void)
{
  if (_callback.target_type() != typeid(void))
    _callback(0);
}

bool		Button::isClicked(sf::Vector2i coord) const
{
  float			x, y;
  x = coord.x;
  y = coord.y;
  if (_sprite.getGlobalBounds().contains(x, y))
    return true;
  return false;
}

const sf::Vector2f&	Button::getPosition() const
{
  return _sprite.getPosition();
}

void			Button::setPosition(const sf::Vector2f &pos)
{
  _sprite.setPosition(pos);
}

const sf::Vector2f&	Button::getDimension() const
{
  return _dimension;
}

void			Button::setDimension(const sf::Vector2f &dim)
{
  _dimension = dim;
}

void			Button::setCallback(const std::function<void(int)> &f)
{
  _callback = f;
}
