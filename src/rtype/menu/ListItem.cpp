#include "ListItem.hh"

ListItem::ListItem(const sf::Vector2f& dimension, const sf::Vector2f& position,
		   const std::string& label, const std::string& texture)
  : Button(dimension, position, texture)
  , _label(sf::String(label))
{
  _label.setPosition(position);
  _label.setCharacterSize(14);
}

ListItem::~ListItem()
{
}

void		ListItem::draw(sf::RenderTarget& target)
{
  target.draw(_sprite);
  target.draw(_label);
}

const std::string	ListItem::getLabel() const
{
  return _label.getString();
}

void			ListItem::setLabel(const std::string &s)
{
  _label.setString(s);
}

void			ListItem::setPosition(const sf::Vector2f &pos)
{
  sf::Vector2f		vec;

  _sprite.setPosition(pos);
  vec.x = pos.x + 20; // horizontal offset
  vec.y = pos.y + ((_dimension.y / 2) - (_label.getCharacterSize() / 2)); // vertical align center
  _label.setPosition(vec);
}
