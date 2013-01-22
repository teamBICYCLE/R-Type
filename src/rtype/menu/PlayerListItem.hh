#ifndef __PLAYERLISTITEM_HH__
# define __PLAYERLISTITEM_HH__

# include <string>
# include <SFML/Graphics.hpp>
# include <SFML/Graphics/Text.hpp>
# include "ListItem.hh"

class PlayerListItem : public ListItem {
private:
  sf::Text		_status;

public:
  PlayerListItem(const sf::Vector2f& dimension, const std::string& label,
		 const std::string& status = "Empty")
  virtual ~PlayerListItem();

  virtual void		draw(sf::RenderTarget& target);
  
  const std::string	getStatus() const;
  void			setStatus(const std::string&);

  virtual void		setPosition(const sf::Vector2f& pos);
};

#endif // !__PLAYERLISTITEM_HH__
