#ifndef		_DLOADER_HH_
# define	_DLOADER_HH_

# ifdef     __gnu_linux__
#	include "UnixDLoader.hh"
	typedef UnixDLoader DLoader;
# elif      _WIN32
#	include "WinDLoader.hh"
	typedef WinDLoader DLoader;
# else
#	error "Unsupported architecture."
# endif

#endif /*!_DLOADER_HH_*/