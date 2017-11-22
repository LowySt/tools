#ifndef LS_COMPILERDIRECTIVES_H
#define LS_COMPILERDIRECTIVES_H

#ifdef _WIN32
#define LS_PLAT_WINDOWS
#elif __GNUC__
#define LS_PLAT_LINUX

#ifdef LS_PLAT_WINDOWS
#define __align(x) _declspec(align(x))
#elif LS_PLAT_LINUX
#define __align(x) __attribute__((aligned (x)))
#endif

#endif
