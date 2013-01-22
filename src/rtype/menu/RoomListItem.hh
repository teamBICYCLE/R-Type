#ifndef __ROOMLISTITEM_HH__
# define __ROOMLISTITEM_HH__

# include <string>
# include <SFML/Graphics.hpp>
# include <SFML/Graphics/Text.hpp>
# include "ListItem.hh"

class RoomListItem : public ListItem {
private:
  sf::Text		_minPlayerLabel;
  sf::Text		_maxPlayerLabel;

public:
  RoomListItem(const sf::Vector2f& dimension, const std::string& label,
	       const std::string& minPlayer, const std::string& maxPlayer,
	       const std::string& texture = DEFAULT_LISTITEM_TEXTURE);
  virtual ~RoomListItem();

  virtual void		draw(sf::RenderTarget& target);

  const std::string	getMinPlayerLabel() const;
  void			setMinPlayerLabel(const std::string&);
  const std::string	getMaxPlayerLabel() const;
  void			setMaxPlayerLabel(const std::string&);
  virtual void		setPosition(const sf::Vector2f& pos);
};

#endif // !__ROOMLISTITEM_HH__
