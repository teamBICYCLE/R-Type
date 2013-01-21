#ifndef	__BUTTON_HH__
# define __BUTTON_HH__

# include <string>
# include <functional>
# include <SFML/Graphics.hpp>

# define DEFAULT_BUTTON_TEXTURE "../resources/default_button.png"

class Button {
protected:
  sf::Texture			_texture;
  sf::Sprite			_sprite;
  std::function<void()>		_callback;
  void				*_param;
  sf::Vector2f			_dimension;

public:
  Button(const sf::Vector2f& dimension, const sf::Vector2f& position = sf::Vector2f(0,0),
         const std::string& texture = DEFAULT_BUTTON_TEXTURE);
  virtual ~Button();

  virtual void		draw(sf::RenderTarget& target);
  void			onClick();

  bool		isClicked(sf::Vector2i coord) const;
  const sf::Vector2f&	getPosition() const;
  virtual void		setPosition(const sf::Vector2f &pos);
  const sf::Vector2f&	getDimension() const;
  void			setDimension(const sf::Vector2f &pos);
  void			setCallback(const std::function<void()> &f);
};

#endif // !__BUTTON_HH__
