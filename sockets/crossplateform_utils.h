#ifndef _CROSSPLATEFORM_UTILS_H__
#define _CROSSPLATEFORM_UTILS_H__

#ifdef __gnu_linux__
# define CROSSPLATEFORM(linux, win) linux
#elif defined _WIN32
# define CROSSPLATEFORM(linux, win) win
#endif

#endif /* !_CROSSPLATEFORM_UTILS_H__ */
