#include "PlayerListItem.hh"

PlayerListItem::PlayerListItem(const sf::Vector2f& dimension, const std::string& id,
			       const std::string& status, const sf::Color& color, 
			       const std::string& texture)
  : ListItem(dimension, "#"+id, texture), _color(sf::Vector2f(20,50))
{
	sf::String statusString(status);

	_status.setString(statusString);
  _status.setPosition(sf::Vector2f(0,0));
  _status.setCharacterSize(14);
  _color.setPosition(sf::Vector2f(0,0));
  _color.setFillColor(color);
}

PlayerListItem::~PlayerListItem()
{
}

void		PlayerListItem::draw(sf::RenderTarget& target)
{
  target.draw(_sprite);
  target.draw(_color);
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
  vec.x = pos.x + 60;
  vec.y = pos.y;
  _color.setPosition(vec);
}
