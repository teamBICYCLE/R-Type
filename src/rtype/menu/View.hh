#ifndef __VIEW_HH__
# define __VIEW_HH__

# include "ListView.hh"
# include "ListItem.hh"
# include "Button.hh"
# include <SFML/Graphics.hpp>
# include <functional>

class View {
private:
  ListView	*_listView;
  Button	*_buttonOne;
  Button	*_buttonTwo;
  Button	*_refreshButton;
  sf::Texture		_texture;
  sf::Sprite		_background;
  sf::Vector2u		_size;

public:
  View(const std::string& texture, const sf::Vector2u& size, const sf::Vector2f& listItemSize);
  virtual ~View();

  void		update(std::vector<void*>&);
  void		draw(sf::RenderWindow&);
  void		clickEvent(sf::Vector2i coord);

  Button*	getButtonOne() const;
  Button*	getButtonTwo() const;
  Button*	getRefreshButton() const;
  ListView*	getListView() const;
  void		setGlobalCallback(std::function<void()>);
  void		setButtonOne(const sf::Vector2f& dim, std::function<void()> f, const std::string&);
  void		setButtonTwo(const sf::Vector2f& dim, std::function<void()> f, const std::string&);
};

#endif // !__VIEW_HH__
