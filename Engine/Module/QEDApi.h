#ifndef QED_API_H
#define QED_API_H

#ifdef MAKE_DLL
#  define QED_API __declspec(dllexport)
#else
#  define QED_API __declspec(dllimport)
#endif

#endif // !QED_API_H
