#include "WinDLoader.hh"

WinDLoader::WinDLoader(const std::string &filename)
{
    _handle = LoadLibraryA(filename.c_str());
    if (!_handle)
        throw std::logic_error("can't load library named \"" + filename + "\"");
}

WinDLoader::~WinDLoader()
{
    if (FreeLibrary(_handle) != 0)
    {
        std::ostringstream os;
        os << GetLastError();
        throw std::logic_error(os.str());
    }
}
