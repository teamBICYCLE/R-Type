#ifndef __LISTVIEW_HH__
# define __LISTVIEW_HH__

# include "ListItem.hh"
# include "Room.hh"
# include "RoomListItem.hh"
# include <vector>
# include <SFML/Graphics.hpp>
# include <functional>

# define VERTICAL_ITEM_SPACING	2
# define MAX_ROW 8

class ListView {
protected:
  std::vector<ListItem*>	_list;
  sf::Vector2f			_position;
  sf::Vector2f			_itemSize;
  sf::RectangleShape		_background;
  unsigned int			_maxRow;
  std::function<void()>		_globalCallback;

public:
  ListView(const sf::Vector2f &pos, const sf::Vector2f &itemSize, unsigned int maxRow = MAX_ROW);
  virtual ~ListView();

  void		update(std::vector<Room>&);
  bool		checkClick(sf::Vector2i coord) const;
  void		draw(sf::RenderTarget& target);

  void		addItemToList(ListItem *item);

  const std::vector<ListItem*>&	getList() const;
  const sf::Vector2f&		getPosition() const;
  const sf::Vector2f&		getSize() const;
  const sf::Vector2f&		getItemSize() const;

  void		setGlobalCallback(std::function<void()>);
};

#endif // !__LISTVIEW_HH__
