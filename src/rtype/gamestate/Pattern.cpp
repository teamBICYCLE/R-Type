#include <system/log/Log.hh>
#include <fstream>
#include <iostream>
#include <cstring>
#include "Pattern.hh"

Pattern::Pattern(const std::string &path)
	: _valid(false)
{
	Pattern::loadFile(path);
}

void Pattern::loadFile(const std::string &path)
{
	std::cout << "Pattern loadFile -> " << path << std::endl;
	using namespace TBSystem;
	std::ifstream ifs(path);
    std::string content;
    if (!ifs.good())
        log::warn << "Undefined reference to file " << path << " (skipped)" << log::endl;
    else
        content.assign((std::istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()));

    // PARSE

    size_t defpos = content.find(DEFINITION_BLOCK);
    size_t drapos = content.find(DRAWING_BLOCK);
    if (defpos != std::string::npos &&
    	drapos != std::string::npos && defpos < drapos)
    {
    	defpos += std::strlen(DEFINITION_BLOCK);
        
        try {
            Pattern::loadCsv(content.substr(defpos, drapos - defpos));
            drapos += std::strlen(DRAWING_BLOCK);
            Pattern::loadDrawing(content.substr(drapos, content.length() - drapos));
        } catch (csv::Error &e) {
            log::err << e.what() << log::endl;
            return;
        }
    	_valid = true;
    }
    else
    	std::cout << "not valid !" << std::endl;

}

void Pattern::loadCsv(const std::string &data)
{
    _definition = new csv::Parser(data, csv::DataType::ePURE);
}

void Pattern::loadDrawing(const std::string &data)
{
    std::istringstream stream(data);
    std::string definedChar;
    std::string line;
    std::vector<std::string> rows;
    
    // get defined Char
    for (int i = 0; i != _definition->rowCount(); ++i)
        definedChar.append((*_definition)[i]["char"]);

    // get Data line by line
    while (std::getline(stream, line))
        if (line != "")
            rows.push_back(line);

    // read pattern
    unsigned int y = 0;
    for (auto row : rows)
    {
        unsigned int x = 0; 
        for (auto e : row)
        {
            size_t charPos = definedChar.find(e);
            if (charPos != std::string::npos)
            {
                std::shared_ptr<Element> pe(new Element());
                //Element *pe = new Element();
                pe->posx = x;
                pe->posy = y;
                pe->type = (*_definition)[charPos]["type"];
                pe->moveStyle = (*_definition)[charPos]["move"];
                _patternElements.push_back(pe);
                //std::cout << e << " pos : (" << pe.posx << ", " << pe.posy << ") " << "type " << pe.type << " " << pe.moveStyle << std::endl;
            }
            ++x;
        }
        ++y;
    }
}

bool Pattern::isValid(void) const
{
    return _valid;
}

const std::list<std::shared_ptr<Pattern::Element>> &Pattern::getPatternElements(void) const
{
    return _patternElements;
}

Pattern::~Pattern(void)
{
    _patternElements.clear();
	delete _definition;
}