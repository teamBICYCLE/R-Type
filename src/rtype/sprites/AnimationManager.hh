#ifndef  __ANIMATION_MANAGER__
# define __ANIMATION_MANAGER__

# include <map>
# include <string>
# include <vector>
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
		bool addSourceFolder(const std::string &path);
		bool addSource(const std::string& spriteFile , const std::string &cfgFile);
		bool setAnimationName(const std::string &animName, const std::string &spriteFile);
	private:
		bool findAssociatedFile(std::vector<std::string> &files);
		std::vector<std::string>::iterator  findCfgFile(std::vector<std::string> &files);
		std::vector<std::string>::iterator  findAssociatedImg(std::vector<std::string> &files,
												const std::string &cfgFile);

	private:
		std::map<std::string, SpriteBoard> _animations;
	};
}
#endif /*!__ANIMATION_MANAGER__ */