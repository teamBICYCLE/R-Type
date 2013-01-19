#ifndef		_PATTERN_HH_
# define	_PATTERN_HH_

# include <string>
# include <memory>
# include "csv/CSVparser.hpp"
# include "utilities/Vector2D.hh"

# define DEFINITION_BLOCK	"PATTERN_DEFINITION :"
# define DRAWING_BLOCK	  	"PATTERN_DRAWING :"


class Pattern
{

public:
	typedef struct Element
	{	
		unsigned int posx;
		unsigned int posy;
		std::string type;
		std::string moveStyle;
	} Element;

public:
	Pattern(const std::string &);
	~Pattern(void);

public:
	bool	isValid(void) const;
	const std::list<std::shared_ptr<Element>> &getPatternElements(void) const;

protected:
	void loadFile(const std::string &);
	void loadCsv(const std::string &);
	void loadDrawing(const std::string &);

private:
	csv::Parser *_definition;
	bool _valid;
	std::list<std::shared_ptr<Element>> _patternElements;
};

#endif /*!_PATTERN_HH_*/