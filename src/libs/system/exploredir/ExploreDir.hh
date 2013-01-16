#ifndef		_EXPLORE_DIR_HH_
# define	_EXPLORE_DIR_HH_

# include <vector>
# include <string>

namespace TBSystem
{
	class ExploreDir
	{

	public:
		ExploreDir(void);
		~ExploreDir(void);

	public:
		static std::vector<std::string> run(const std::string &dir);
	};
};

#endif /*!_EXPLORE_DIR_H_*/