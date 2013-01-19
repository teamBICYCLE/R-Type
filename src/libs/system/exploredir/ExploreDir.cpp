#ifdef  __gnu_linux__
# include <dirent.h>
#elif      _WIN32
# include "dirent.h"
#else
# error "Unsupported architecture."
#endif
#include "ExploreDir.hh"
#include "system/log/Log.hh"

using namespace TBSystem;

ExploreDir::ExploreDir(void)
{
}

ExploreDir::~ExploreDir(void)
{
}

std::vector<std::string> ExploreDir::run(const std::string &dir, const std::string &ext)
{
	DIR *dp;
    struct dirent *entry;
    unsigned char isFile = 0x8;
    std::vector<std::string> files;
    if (!(dp = opendir(dir.c_str())))
    {
        log::warn << "Error(" << errno << ") opening " << dir << log::endl;
        return files;
    }
    
    while ((entry = readdir(dp)))
        if (entry->d_type == isFile && checkExtension(entry->d_name, ext))
            files.push_back(dir + "/" + entry->d_name);

    closedir(dp);
    return files;
}

bool ExploreDir::checkExtension(const std::string &file, const std::string &need)
{
    if (!need.empty())
    {
        size_t dot = file.find_last_of('.');
        if (dot != std::string::npos && file.substr(dot, file.length() - dot) == need)
            return true;
        return false;
    }
    return true;
}


