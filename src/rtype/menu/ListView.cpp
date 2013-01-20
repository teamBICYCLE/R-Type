#include "ListView.hh"
#include <iterator>

ListView::ListView(const sf::Vector2f &pos, const sf::Vector2f &itemSize, unsigned int maxRow)
  : _position(pos), _itemSize(itemSize), _maxRow(maxRow), _background()
{
  _background.setFillColor(sf::Color(0,0,0,128));
  _background.setOutlineColor(sf::Color::Black);
  _background.setOutlineThickness(1);
}

ListView::~ListView()
{
}

void	ListView::update(std::vector<void*> &list)
{
  _list.clear();
  for (auto it = list.begin(); it != list.end(); it++)
    {
      ListItem		*item = new ListItem(_itemSize, sf::Vector2f(0,0), "127.0.0.1:4242");
      item->setCallback(_globalCallback);
      this->addItemToList(item);
    }
}

bool	ListView::checkClick(sf::Vector2i coord) const
{
  for (auto it = _list.begin(); it != _list.end(); it++)
    {
      if ((*it)->isClicked(coord)) {
	(*it)->onClick();
	return true;
      }
    }
  return false;
}

void	ListView::draw(sf::RenderTarget& target)
{
  int	countRow = 0;

  _background.setSize(sf::Vector2f(_itemSize.x,(_maxRow * _itemSize.y + ((_maxRow - 1) * VERTICAL_ITEM_SPACING))));
  _background.setPosition(_position);
  target.draw(_background);
  for (auto it = _list.begin(); it != _list.end(); it++)
    {
      (*it)->draw(target);
      if (++countRow >= _maxRow)
	break;
    }
}

void	ListView::addItemToList(ListItem *item)
{
  float x = _position.x;
  float y = _position.y + (_list.size() * _itemSize.y) + (_list.size() * VERTICAL_ITEM_SPACING);
  item->setPosition(sf::Vector2f(x,y));
  _list.push_back(item);
}

const std::vector<ListItem*>&	ListView::getList() const
{
  return _list;
}

const sf::Vector2f&		ListView::getPosition() const
{
  return _position;
}

const sf::Vector2f&		ListView::getItemSize() const
{
  return _itemSize;
}

void	ListView::setGlobalCallback(std::function<void()> f)
{
  this->_globalCallback = f;
}