#include "ListItem.hh"

ListItem::ListItem(const sf::Vector2f& dimension, const std::string& label, const std::string& texture)
  : Button(dimension, sf::Vector2f(0,0), texture), _id(0)
{
	sf::String labelString(label);

	_label.setString(labelString);
  _label.setPosition(sf::Vector2f(0,0));
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

void		ListItem::onClick(void)
{
  if (_callback.target_type() != typeid(void))
    _callback(_id);
}

const std::string	ListItem::getLabel() const
{
  return _label.getString();
}

void			ListItem::setLabel(const std::string &s)
{
  _label.setString(s);
}

int			ListItem::getId() const
{
  return _id;
}

void			ListItem::setId(int id)
{
  _id = id;
}

void			ListItem::setPosition(const sf::Vector2f &pos)
{
  sf::Vector2f		vec;

  _sprite.setPosition(pos);
  vec.x = pos.x + 20; // horizontal offset
  vec.y = pos.y + ((_dimension.y / 2) - (_label.getCharacterSize() / 2)); // vertical align center
  _label.setPosition(vec);
}
