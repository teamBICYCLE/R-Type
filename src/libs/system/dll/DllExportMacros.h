#ifndef _DLLEXPORTMACROS_H__
#define _DLLEXPORTMACROS_H__

#ifdef _WIN32
# define DLLEXPORT __declspec(dllexport)
#elif defined __gnu_linux__
# define DLLEXPORT
#endif

#endif