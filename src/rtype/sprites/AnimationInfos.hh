#ifndef  __ANIMATION_INFOS__
# define __ANIMATION_INFOS__

# include <string>
# include <chrono>
# include "Board.hh"

namespace Sprite
{
	class AnimationInfos
	{
	public:
		AnimationInfos(const Board &sprites);
		AnimationInfos(const AnimationInfos &other);
		AnimationInfos &operator=(const AnimationInfos &other);
		virtual ~AnimationInfos(void);

		void setPlayAnimNumber(const int nbPlay);
		bool setAnimationName(const std::string &animName);
		void startAnimation(void);
		std::chrono::milliseconds getDurationAnimation(void);

		sf::Sprite &getSprite(void);

	private:
	 	std::string _currentAnim;
	 	std::chrono::steady_clock::time_point _currentSpriteTime;
	 	Board _spriteBoard;
	 	int _nbPlay;
	};
}
#endif /*!__ANIMATION_INFOS__*/
