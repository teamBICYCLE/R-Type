#include <iostream>
#include <fstream>
#include <cstring>

#ifdef  __gnu_linux__
# include <dirent.h>
#elif      _WIN32
# include "dirent.h"
#else
# error "Unsupported architecture."
#endif

#include <sstream>
#include <stdexcept>
#include <functional>
#include "system/log/Log.hh"
#include "system/exploredir/ExploreDir.hh"
#include "ResourcesArchiver.hh"

using namespace TBSystem;

ResourcesArchiver::ResourcesArchiver(const std::string &n, const std::string &e)
    : _name(n), _extension(e)
{
}

ResourcesArchiver::~ResourcesArchiver(void)
{
}

const std::string ResourcesArchiver::readFile(const std::string &path) const
{
    std::ifstream ifs(path, std::ios::binary);
    std::string content;
    if (!ifs.good())
        log::warn << "Undefined reference to file " << path << " (skipped)" << log::endl;
    else
        content.assign((std::istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()));
    return content;
}

bool ResourcesArchiver::add(const std::string &file)
{
    if (file.length() > FILE_NAME_LENGTH)
    {
	   log::warn << "Filename is too large for this archive" << log::endl;
       return false;
    }
    _files.push_back(file);
    return true;
}

bool ResourcesArchiver::addDirectory(const std::string &dir)
{
    using namespace TBSystem;
    _files = ExploreDir::run(dir);
    if (_files.size() == 0)
        return false;
    return true;
}

void ResourcesArchiver::pack(void) const
{
    if (_files.size() <= 0)
        log::notice << "The output archive will be empty (no files added)" << log::endl;

    std::ofstream f(_name + "." + _extension, std::ofstream::binary);
    std::string data;
    char name[FILE_NAME_LENGTH];
    char size[SIZE_FILE_LENGTH];
    std::stringstream sizeStream;

    for (auto it : _files)
    {
    	std::memset(name, 0, FILE_NAME_LENGTH);
        std::strncpy(name, it.c_str(), FILE_NAME_LENGTH);

        data = ResourcesArchiver::readFile(it);
        if (data.length() > 0)
        { 
            // Write file name
            f.write(name, FILE_NAME_LENGTH);
            
            // Get file size
            sizeStream.str("");
            sizeStream.clear();
            sizeStream << data.length();
            std::memset(size, 0, SIZE_FILE_LENGTH);
            std::strncpy(size, &sizeStream.str()[0], SIZE_FILE_LENGTH);

            // Write size + data
            f.write(size, SIZE_FILE_LENGTH);
            f.write(data.c_str(), data.length());
        }
    }
    f.write(END_OF_ARCHIVE, strlen(END_OF_ARCHIVE));
    f.close();
}

bool ResourcesArchiver::unpack(const char *data, const std::string &dir)
{
    std::string name;
    char size[SIZE_FILE_LENGTH];
    int isize;
    std::fstream f;

    std::function<double(void)> dataError = [](void) {
        log::critic << "Corrupted data. Archive can't be unpack" << log::endl;
        return false;
    };

    while (std::strcmp(data, END_OF_ARCHIVE))
    {
        if (!std::strlen(data))
            return dataError();

        // Get File name
        name.resize(std::strlen(data));
        std::strncpy(&name[0], data, std::strlen(data));
        ResourcesArchiver::formatName(name);
        data += FILE_NAME_LENGTH;

        // Get File size
        std::memset(size, 0, SIZE_FILE_LENGTH);
        std::strncpy(size, data, SIZE_FILE_LENGTH);
        data += SIZE_FILE_LENGTH;

        try {
            isize = 0;
            isize = std::stoi(size);            
        } catch (std::invalid_argument &e) {
            return dataError(); 
        } catch (std::out_of_range &e) {
            return dataError(); 
        }

        // Write data in the resource file
        log::info << "Unpack file " << name << " (" << size << ")" << log::endl;
        f.open(dir + "/" + name, std::fstream::out | std::fstream::binary);
        f.write(data, isize);
        if (f.bad())
            return dataError();

        data += isize;
        f.close();
    }
    return true;
}

void ResourcesArchiver::formatName(std::string &name)
{
    size_t dir = name.find_last_of("/");
    if (dir != std::string::npos)
        name = name.substr(dir + 1, name.length() - dir);
}
