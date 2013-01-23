#ifdef  __gnu_linux__
# include <dirent.h>
#elif defined _WIN32
# include <Windows.h>
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

#ifdef  __gnu_linux__
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
#elif _WIN32
    std::vector<std::string> ExploreDir::run(const std::string &dir, const std::string &ext)
    {
        WIN32_FIND_DATA data;
        std::wstring path(L"*");
        std::wstring *name;
        HANDLE hFile = FindFirstFile(dir.c_str(), &data);
        std::vector<std::string> files;

        if (hFile == INVALID_HANDLE_VALUE)
        {    
            log::warn << "Error(" << errno << ") opening " << dir << log::endl;
            return files;
        }

        while (FindNextFile(hFile, &data) != 0 || GetLastError() != ERROR_NO_MORE_FILES)
            if (checkExtension(data.cFileName, ext))
                files.push_back(data.cFileName);
        return files;
    }
#else
# error "Unsupported architecture."   
#endif

bool ExploreDir::checkExtension(const std::string &file, const std::string &need)
{
    if (!need.empty())
    {
        size_t dot = file.find_last_of('.');
        if (dot != std::string::npos && file.substr(dot, file.length() - dot) == need)
            return true;
        return false;
    }
}




