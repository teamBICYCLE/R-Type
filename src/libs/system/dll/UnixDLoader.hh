#ifndef     _UNIX_DLOADER_HH_
# define    _UNIX_DLOADER_HH_

# include <stdexcept>
# include <string>
# include <functional>
# include <dlfcn.h>

class UnixDLoader
{

public:
    UnixDLoader(const std::string &);
    ~UnixDLoader();

    template<class T>
    std::function<T> load(const std::string &symbol)
    {
        char *error;
        dlerror();
        void* result = dlsym(_handle, symbol.c_str());
        if ((error = dlerror()))
            throw std::logic_error(error);
        return reinterpret_cast<T*>(result);
    }

private:
    void    *_handle;
};

#endif /*_UNIX_DLOADER_HH_*/
