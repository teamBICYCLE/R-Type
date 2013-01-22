#include "RoomListItem.hh"

RoomListItem::RoomListItem(const sf::Vector2f& dimension, const std::string& id,
			   const std::string& minPlayer, const std::string& maxPlayer,
			   const std::string& texture)
  : ListItem(dimension, "#"+id, texture), _minPlayerLabel(minPlayer), _maxPlayerLabel("/" + maxPlayer)
{
  _minPlayerLabel.setPosition(sf::Vector2f(0,0));
  _maxPlayerLabel.setPosition(sf::Vector2f(0,0));
  _minPlayerLabel.setCharacterSize(14);
  _maxPlayerLabel.setCharacterSize(14);
}

RoomListItem::~RoomListItem()
{
}

void		RoomListItem::draw(sf::RenderTarget& target)
{
  target.draw(_sprite);
  target.draw(_label);
  target.draw(_minPlayerLabel);
  target.draw(_maxPlayerLabel);
}

const std::string	RoomListItem::getMinPlayerLabel() const
{
  return _minPlayerLabel.getString();
}

void			RoomListItem::setMinPlayerLabel(const std::string &s)
{
  _minPlayerLabel.setString(s);
}

const std::string	RoomListItem::getMaxPlayerLabel() const
{
  return _maxPlayerLabel.getString();
}

void			RoomListItem::setMaxPlayerLabel(const std::string &s)
{
  _maxPlayerLabel.setString("/" + s);
}

void			RoomListItem::setPosition(const sf::Vector2f &pos)
{
  sf::Vector2f		vec;

  _sprite.setPosition(pos);
  vec.x = pos.x + 20; // horizontal offset
  vec.y = pos.y + ((_dimension.y / 2) - (_label.getCharacterSize() / 2)); // vertical align center
  _label.setPosition(vec);
  vec.x = pos.x + (_dimension.x - 40);
  vec.y = pos.y + ((_dimension.y / 2) - (_minPlayerLabel.getCharacterSize() / 2));
  _minPlayerLabel.setPosition(vec);
  vec.x = pos.x + (_dimension.x - 30);
  vec.y = pos.y + ((_dimension.y / 2) - (_maxPlayerLabel.getCharacterSize() / 2));
  _maxPlayerLabel.setPosition(vec);
}
