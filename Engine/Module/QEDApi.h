#ifndef QED_API_H
#define QED_API_H

#ifdef MAKE_ENGINE
#	define QED_ENGINE_API __declspec(dllexport)
#	define QED_ENGINE_EXPORT
#else
#	define QED_ENGINE_API __declspec(dllimport)
#	define QED_ENGINE_EXPORT export
#endif

#ifdef MAKE_MODULE
#	define QED_MODULE_API __declspec(dllexport)
#else
#	define QED_MODULE_API __declspec(dllimport)
#endif

#endif // !QED_API_H
