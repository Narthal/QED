#ifndef LOAD_MODULE_H
#define LOAD_MODULE_H

#if QED_ENGINE_WINDOWS
#include <Windows.h>
#else
#error "Didnt implement linux loader"
#endif

namespace QED
{
	namespace Engine
	{
		namespace Module
		{
			class Module
			{
				public:
				// Handle by which DLLs are referenced
				typedef HMODULE HandleType;

				public:
				// Loads the DLL from the specified path
				static HandleType Load(const std::string& path)
				{
					std::string pathWithExtension = path + ".dll";

					HMODULE moduleHandle = LoadLibraryA(pathWithExtension.c_str());
					if (moduleHandle == NULL)
					{
						throw std::runtime_error("Could not load DLL");
					}

					return moduleHandle;
				}

				public:
				// Unloads the DLL with the specified handle
				static void Unload(HandleType sharedLibraryHandle)
				{
					BOOL result = FreeLibrary(sharedLibraryHandle);
					if (result == FALSE)
					{
						throw std::runtime_error("Could not unload DLL");
					}
				}


				// Looks up a function exported by the DLL
				template<typename TSignature>
				static TSignature* GetFunctionPointer (HandleType sharedLibraryHandle, const std::string& functionName)
				{
					FARPROC functionAddress = GetProcAddress(sharedLibraryHandle, functionName.c_str());

					if (functionAddress == NULL)
					{
						throw std::runtime_error("Could not find exported function");
					}

					return reinterpret_cast<TSignature*>(functionAddress);
				}
			};
		}
	}
}


#endif // !LOAD_MODULE_H
