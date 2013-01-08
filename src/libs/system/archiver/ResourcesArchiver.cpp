#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include "system/log/Log.hh"
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
    if (!ifs.good())
        log::warn << "Undefined reference to file " << path << " (skipped)" << log::endl;
    std::string content((std::istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()));
    return content;
}

void ResourcesArchiver::add(const std::string &file)
{
    if (file.length() > 100)
		log::warn << "Filename is too large for this archive" << log::endl;
    else
        _files.push_back(file);
}

void ResourcesArchiver::pack(void) const
{
    if (_files.size() <= 0)
        log::notice << "The output archive will be empty (no files added)" << log::endl;

    std::ofstream f(_name + "." + _extension, std::ofstream::binary);
    std::string data;
    char name[FILE_NAME_LENGTH];
    std::stringstream size;

    for (auto it = _files.begin(); it != _files.end(); ++it)
    {
        std::memset(name, 0, FILE_NAME_LENGTH);
        std::strncpy(name, it->c_str(), FILE_NAME_LENGTH);

        data = ResourcesArchiver::readFile(*it);
        if (data.length() > 0)
        { 
            // Write file name
            f.write(name, FILE_NAME_LENGTH);
            
            // Get file size
            size.str("");
            size.clear();
            size << data.length();

            // Write size + data
            f.write(&size.str()[0], SIZE_FILE_LENGTH);
            f.write(data.c_str(), data.length());
        }
    }
    f.write(END_OF_ARCHIVE, strlen(END_OF_ARCHIVE));
    f.close();
}

// TMP
bool ResourcesArchiver::unpack(const std::string &file, const std::string &dir)
{
    std::ifstream ifs(file, std::ios::binary);;
    std::string content((std::istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()));
    return ResourcesArchiver::unpack(content.c_str(), dir);
}

bool ResourcesArchiver::unpack(const char *data, const std::string &dir)
{
    std::string name;
    char size[SIZE_FILE_LENGTH];
    std::fstream f;

    while (std::strcmp(data, END_OF_ARCHIVE))
    {
        if (!std::strlen(data))
        {
			log::critic << "Corrupted data. Archive can't be unpack" << log::endl;
            return false;
        }

        // Get File name
        name.resize(std::strlen(data));
        std::strncpy(&name[0], data, std::strlen(data));
        ResourcesArchiver::formatName(name);
        data += FILE_NAME_LENGTH;

        // Get File size
        std::memset(size, 0, SIZE_FILE_LENGTH);
        std::strncpy(size, data, SIZE_FILE_LENGTH);
        data += SIZE_FILE_LENGTH;

        log::info << "Unpack file " << name << " (" << size << ")" << log::endl;

        // Write data in the resource file
        f.open(dir + "/" + name, std::fstream::out | std::fstream::binary);
        f.write(data, atoi(size));
        if (f.bad())
        {
            log::critic << "Corrupted data. Archive can't be unpack" << log::endl;
            return false;
        }
        data += atoi(size);
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
