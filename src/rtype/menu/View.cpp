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
  x = (_size.x / 2) - (listItemSize.x / 2);
  y = (_size.y / MAX_ROW);
  _listView = new ListView(sf::Vector2f(x,y), listItemSize);
  _refreshButton = new Button(sf::Vector2f(50.0,50.0));
  _refreshButton->setPosition(sf::Vector2f(0,0));
}

View::~View()
{
}

void	View::update(std::vector<void*> &list)
{
  _listView->update(list);
}

void	View::draw(sf::RenderWindow& target)
{
  target.draw(_background);
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
    if (_buttonOne->isClicked(coord))
      _buttonOne->onClick();
    if (_buttonTwo->isClicked(coord))
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

void		View::setButtonOne(const sf::Vector2f& dim, std::function<void()> f,
				   const std::string& texture)
{
  if (_buttonOne)
    delete _buttonOne;
  if (texture.empty())
    _buttonOne = new Button(dim, sf::Vector2f(0,0));
  else
    _buttonOne = new Button(dim, sf::Vector2f(0,0), texture);
  _buttonOne->setPosition(sf::Vector2f(580.0,500.0));
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
  _buttonTwo->setPosition(sf::Vector2f(690.0,500.0));
  _buttonTwo->setCallback(f);
}
