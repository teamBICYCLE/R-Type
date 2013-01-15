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

std::vector<std::string> ExploreDir::run(const std::string &dir)
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
        if (entry->d_type == isFile)
            files.push_back(dir + "/" + entry->d_name);

    closedir(dp);
    return files;
}


