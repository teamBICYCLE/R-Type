#ifndef  __ANIMATION__
# define __ANIMATION__

# include <SFML/Graphics.hpp>
# include <vector>
# include <chrono>

namespace Sprite
{
	class Animation
	{
	public:
		Animation(void) : _duration(0){};
		Animation(const std::vector<sf::Rect<int>> &sprite, const float duration);
		Animation(const Animation &other);
		Animation &operator=(const Animation &other);
		virtual ~Animation(void);


		sf::Rect<int> operator[](const unsigned int position) const;
		void setRects(const std::vector<sf::Rect<int>> &sprite);
		void setDuration(const std::chrono::milliseconds duration);
		std::vector<sf::Rect<int>> getRects(void) const;
		const std::chrono::milliseconds getDuration(void) const;

	private:
		std::vector<sf::Rect<int>> _sprite;
		std::chrono::milliseconds _duration;
	};
}
#endif /*__ANIMATION__*/
