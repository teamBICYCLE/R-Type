#include <system/log/Log.hh>
#include <fstream>
#include <iostream>
#include <cstring>
#include "Pattern.hh"

Pattern::Pattern(const std::string &path)
	: _isValid(false)
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
    	std::cout << "DEF -> " << content.substr(defpos, drapos - defpos) << std::endl;
    	
    	try {
    		_definition = new csv::Parser(content.substr(defpos, drapos - defpos), csv::DataType::PURE);
    	}
    	catch (csv::Error &e) {
        	log::err << e.what() << log::endl;
        	return;
    	}

    	//std::cout << _definition->getRow(0).getValue<std::string>(0) << std::endl;

    	drapos += std::strlen(DRAWING_BLOCK);
    	std::cout << "DRA -> " << content.substr(drapos, content.length() - drapos) << std::endl;
    	_isValid = true;
    }
    else
    	std::cout << "not valid !" << std::endl;

}

Pattern::~Pattern(void)
{
	delete _definition;
}