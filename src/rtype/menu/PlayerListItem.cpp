#include "PlayerListItem.hh"

PlayerListItem::PlayerListItem(const sf::Vector2f& dimension, const std::string& id,
			       const std::string& status, const std::string& texture)
  : ListItem(dimension, "#"+id, texture), _status(status)
{
  _status.setPosition(sf::Vector2f(0,0));
  _status.setCharacterSize(14);
}

PlayerListItem::~PlayerListItem()
{
}

void		PlayerListItem::draw(sf::RenderTarget& target)
{
  target.draw(_sprite);
  target.draw(_label);
  target.draw(_status);
}

const std::string	PlayerListItem::getStatus() const
{
  return _status.getString();
}

void			PlayerListItem::setStatus(const std::string &s)
{
  _status.setString(s);
}

void			PlayerListItem::setPosition(const sf::Vector2f &pos)
{
  sf::Vector2f		vec;

  _sprite.setPosition(pos);
  vec.x = pos.x + 20; // horizontal offset
  vec.y = pos.y + ((_dimension.y / 2) - (_label.getCharacterSize() / 2)); // vertical align center
  _label.setPosition(vec);
  vec.x = pos.x + (_dimension.x - 80);
  vec.y = pos.y + ((_dimension.y / 2) - (_status.getCharacterSize() / 2));
  _status.setPosition(vec);
}
