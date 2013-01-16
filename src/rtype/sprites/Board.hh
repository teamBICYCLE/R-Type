#ifndef  __BOARD__
# define __BOARD__

# include <SFML/Graphics.hpp>
# include <string>
# include <map>
# include <memory>
# include <sstream>
# include <chrono>
# include "csv/CSVparser.hpp"
# include "Animation.hh"

namespace Sprite
{
	class AnimationInfos;

	class Board
	{
	public:
		Board(const std::string &boardFile, const std::string &boardCfg);
		Board(const Board &other);
		Board &operator=(const Board &other);
		virtual ~Board(void);

		bool hasSpriteNamed(const std::string &name) const;
		sf::Sprite &getSprite(const std::string &animName, std::chrono::milliseconds time);
		AnimationInfos *generateAnimInfo(void);
	private:
		void refreshMap(const std::string &boardFile, const std::string &boardCfg);
		void refreshAnimMap(csv::Parser &csvCfg);
		Animation createSpriteBoard(csv::Parser &csvCfg, unsigned int i);

		std::map<std::string, Animation> _animations;
		sf::Texture  *_texture;
		sf::Sprite   *_board;

		enum FileIDX {
		      NAME           = 0
			, SpriteLoaderNB = 1
			, DURATION       = 2
			, ORIGX          = 3
			, SIZEX          = 4
			, ORIGY          = 5
			, SIZEY          = 6
		};

	};
}

# include "AnimationInfos.hh"

#endif /*!__BOARD__*/
