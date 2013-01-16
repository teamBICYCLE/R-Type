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
		static std::vector<std::string> run(const std::string &, const std::string &e = "");
		static bool checkExtension(const std::string &file, const std::string &need);
	};
};

#endif /*!_EXPLORE_DIR_H_*/