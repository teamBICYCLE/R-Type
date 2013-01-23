#ifndef __PLAYERLISTITEM_HH__
# define __PLAYERLISTITEM_HH__

# include <string>
# include <SFML/Graphics.hpp>
# include <SFML/Graphics/Text.hpp>
# include "ListItem.hh"

class PlayerListItem : public ListItem {
private:
  sf::Text		_status;
  sf::RectangleShape	_color;

public:
  PlayerListItem(const sf::Vector2f& dimension, const std::string& id,
		 const std::string& status = "EMPTY", const sf::Color& color = sf::Color::Black,
		 const std::string& texture = DEFAULT_LISTITEM_TEXTURE);
  virtual ~PlayerListItem();

  virtual void		draw(sf::RenderTarget& target);
  
  const std::string	getStatus() const;
  void			setStatus(const std::string&);

  virtual void		setPosition(const sf::Vector2f& pos);
};

#endif // !__PLAYERLISTITEM_HH__
