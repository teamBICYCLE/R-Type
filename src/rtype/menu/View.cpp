#include "View.hh"
#include "ListItem.hh"
#include "ListView.hh"
#include <SFML/Graphics.hpp>

View::View(const std::string& texture, const sf::Vector2u& size, const sf::Vector2f& listItemSize)
  : _buttonOne(NULL), _buttonTwo(NULL), _size(size)
{
  float x,y;

  _texture.loadFromFile(texture);
  _background.setTexture(_texture);
  _background.setPosition(size.x, size.y);
  _background.setOrigin(1920 / 2, 1920 / 2);
  _background.scale(1.8,1.8);
  x = (_size.x / 2) - (listItemSize.x / 2);
  y = (_size.y / 2) - (MAX_ROW * listItemSize.y / 2);
  _listView = new ListView(sf::Vector2f(x,y), listItemSize);
  _title.setCharacterSize(18);
  _title.setStyle(0);
  _title.setPosition(sf::Vector2f(x - 10, y - _title.getCharacterSize() * 2));
  _refreshButton = new Button(sf::Vector2f(30,30));
  _refreshButton->setPosition(sf::Vector2f(size.x - 30,0));
}

View::~View()
{
}

void	View::update(const std::list<Room> &list)
{
  this->setTitle("Select a room:");
  _listView->update(list);
}

void	View::update(const std::list<Player> &list)
{
  this->setTitle("");
  _listView->update(list);
}

void	View::draw(sf::RenderWindow& target)
{
  _background.rotate(0.015);
  target.draw(_background);
  target.draw(_title);
  _listView->draw(target);
  if (_buttonOne)
    _buttonOne->draw(target);
  if (_buttonTwo)
    _buttonTwo->draw(target);
  if (_refreshButton)
    _refreshButton->draw(target);
}

void	View::clickEvent(sf::Vector2i coord)
{
  if (_listView->checkClick(coord))
    return;
  else {
    if (_buttonOne && _buttonOne->isClicked(coord))
      _buttonOne->onClick();
    if (_buttonOne && _buttonTwo->isClicked(coord))
      _buttonTwo->onClick();
  }
}

Button*	View::getButtonOne() const
{
  return _buttonOne;
}

Button* View::getButtonTwo() const
{
  return _buttonTwo;
}

Button* View::getRefreshButton() const
{
  return _refreshButton;
}

ListView*	View::getListView() const
{
  return _listView;
}

void		View::setGlobalCallback(std::function<void()> f)
{
  _listView->setGlobalCallback(f);
}

void		View::setRefreshCallback(std::function<void()> f)
{
  _refreshButton->setCallback(f);
}

void		View::setButtonOne(const sf::Vector2f& dim, std::function<void()> f,
				   const std::string& texture)
{
  if (_buttonOne)
    delete _buttonOne;
  if (texture.empty())
    _buttonOne = new Button(dim, sf::Vector2f(0,0));
  else
    _buttonOne = new Button(dim, sf::Vector2f(0,0), texture);
  _buttonOne->setPosition(sf::Vector2f((_listView->getPosition().x + _listView->getSize().x - dim.x + 1),
				       (_listView->getPosition().y + _listView->getSize().y + 4)));
  _buttonOne->setCallback(f);

}

void		View::setButtonTwo(const sf::Vector2f& dim, std::function<void()> f,
				   const std::string& texture)
{
  if (_buttonTwo)
    delete _buttonTwo;
  if (texture.empty())
    _buttonTwo = new Button(dim, sf::Vector2f(0,0));
  else
    _buttonTwo = new Button(dim, sf::Vector2f(0,0), texture);
  _buttonTwo->setPosition(sf::Vector2f((_listView->getPosition().x + _listView->getSize().x - (2 * dim.x + 4) + 1),
				       (_listView->getPosition().y + _listView->getSize().y + 4)));
  _buttonTwo->setCallback(f);
}

void		View::setTitle(const std::string& s)
{
  _title.setString(s);
}
