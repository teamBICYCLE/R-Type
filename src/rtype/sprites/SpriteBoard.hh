#ifndef  __SPRITE_BOARD___
# define __SPRITE_BOARD___

# include <string>
# include "Board.hh"
# include "AnimationInfos.hh"

namespace Sprite
{
	class SpriteBoard
	{
	public:
		SpriteBoard(const std::string &imgFile, const std::string &cfgFile);
		SpriteBoard(const SpriteBoard& other);
		SpriteBoard &operator=(const SpriteBoard& other);
		~SpriteBoard(void);

		void setSprite(const Board &sprite);
		void setAnimation(const AnimationInfos &anim);

		Board *getSprite(void);
		AnimationInfos *getAnimInfo(void);
	private:
		Board *_sprite;
		AnimationInfos *_animInfos;
	};
}

#endif /*!__SPRITE_BOARD___*/