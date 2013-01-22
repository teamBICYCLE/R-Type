#ifndef __VIEW_HH__
# define __VIEW_HH__

# include "ListView.hh"
# include "ListItem.hh"
# include "Room.hh"
# include "RoomListItem.hh"
# include "Player.hh"
# include "PlayerListItem.hh"
# include "Button.hh"
# include <SFML/Graphics.hpp>
# include <functional>

using namespace gooey;

class View {
private:
  ListView	*_listView;
  Button	*_buttonOne;
  Button	*_buttonTwo;
  Button	*_refreshButton;
  sf::Texture		_texture;
  sf::Sprite		_background;
  sf::Vector2u		_size;
  sf::Text		_title;

public:
  View(const std::string& texture, const sf::Vector2u& size, const sf::Vector2f& listItemSize);
  virtual ~View();

  void		update(const std::list<Room>&);
  void		update(const std::list<Player>&);
  void		draw(sf::RenderWindow&);
  void		clickEvent(sf::Vector2i coord);

  Button*	getButtonOne() const;
  Button*	getButtonTwo() const;
  Button*	getRefreshButton() const;
  ListView*	getListView() const;
  void		setGlobalCallback(std::function<void(int)>);
  void		setRefreshCallback(std::function<void(int)>);
  void		setButtonOne(const sf::Vector2f& dim, std::function<void(int)> f, const std::string&);
  void		setButtonTwo(const sf::Vector2f& dim, std::function<void(int)> f, const std::string&);
  void		unsetButtonOne();
  void		unsetButtonTwo();
  void		setTitle(const std::string& s);
};

#endif // !__VIEW_HH__
