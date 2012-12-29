#include <dlfcn.h>
#include "UnixDLoader.hh"

UnixDLoader::UnixDLoader(const std::string &filename)
{
	_handle = dlopen(filename.c_str(), RTLD_LAZY);
    if (!_handle)
        throw std::logic_error("can't load library named \"" + filename + "\"");
}

UnixDLoader::~UnixDLoader(void)
{
	if (dlclose(_handle) != 0)
		throw std::logic_error(dlerror());
}