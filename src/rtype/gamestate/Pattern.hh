#ifndef		_PATTERN_HH_
# define	_PATTERN_HH_

# include <string>
# include "csv/CSVparser.hpp"

# define DEFINITION_BLOCK	"PATTERN_DEFINITION :"
# define DRAWING_BLOCK	  	"PATTERN_DRAWING :"

class Pattern
{

public:
	Pattern(const std::string &);
	~Pattern(void);

protected:
	void loadFile(const std::string &);
	csv::Parser *_definition;
	bool _isValid;
};

#endif /*!_PATTERN_HH_*/