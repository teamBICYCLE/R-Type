#ifndef __LISTITEM_HH__
# define __LISTITEM_HH__

# include <string>
# include <SFML/Graphics.hpp>
# include "Button.hh"

# define DEFAULT_LISTITEM_TEXTURE "../resources/default_listitem.png"

class ListItem : public Button {
private:
  sf::Text		_label;

public:
  ListItem(const sf::Vector2f& dimension, const sf::Vector2f& position = sf::Vector2f(0,0),
	   const std::string& label = "",
	   const std::string& texture = DEFAULT_LISTITEM_TEXTURE);
  virtual ~ListItem();

  virtual void		draw(sf::RenderTarget& target);

  const std::string	getLabel() const;
  void			setLabel(const std::string&);
  virtual void		setPosition(const sf::Vector2f& pos);
};

#endif // !__LISTITEM_HH__
