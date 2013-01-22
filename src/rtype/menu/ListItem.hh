#ifndef __LISTITEM_HH__
# define __LISTITEM_HH__

# include <string>
# include <SFML/Graphics.hpp>
# include <SFML/Graphics/Text.hpp>
# include "Button.hh"

# define DEFAULT_LISTITEM_TEXTURE "../resources/default_listitem.png"

class ListItem : public Button {
protected:
  sf::Text		_label;
  int			_id;

public:
  ListItem(const sf::Vector2f& dimension,
	   const std::string& label = "",
	   const std::string& texture = DEFAULT_LISTITEM_TEXTURE);
  virtual ~ListItem();

  virtual void		draw(sf::RenderTarget& target);
  virtual void		onClick(void);

  const std::string	getLabel() const;
  void			setLabel(const std::string&);
  int			getId() const;
  void			setId(int);
  virtual void		setPosition(const sf::Vector2f& pos);
};

#endif // !__LISTITEM_HH__
