#ifndef  __ANIMATION_MANAGER__
# define __ANIMATION_MANAGER__

# include <map>
# include <string>
# include "SpriteBoard.hh"

namespace Sprite
{
	class AnimationManager
	{
	public:
		AnimationManager(void);
		AnimationManager(const AnimationManager &other);
		AnimationManager& operator=(const AnimationManager &other);
		virtual ~AnimationManager(void);

		SpriteBoard &operator[](const std::string &spriteFile);
		bool addSource(const std::string& spriteFile , const std::string &cfgFile);
		bool setAnimationName(const std::string &animName, const std::string &spriteFile);
// scan folder
// get rect of anim()

	private:
		std::map<std::string, SpriteBoard> _animations;
	};
}
#endif /*!__ANIMATION_MANAGER__ */