#ifndef     _WINDLOADER_HH_
# define    _WINDLOADER_HH_

#include <functional>
#include <sstream>
#include <string>
#include <windows.h>

class WinDLoader
{
public:
    WinDLoader(const std::string &);
    ~WinDLoader();

    template<class T>
    std::function<T> load(const std::string &symbol) const
    {
        void* result = GetProcAddress(_handle, symbol.c_str());
        if (!result)
        {
            std::ostringstream os;
            os << GetLastError();
            throw std::logic_error(os.str());
        }
        return reinterpret_cast<T*>(result);
    }

private:
    HMODULE _handle;
};

#endif /*!_WINDLOADER_HH*/
