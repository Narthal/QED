#ifndef MODULE_H
#define MODULE_H

#if QED_WINDOWS
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
			namespace Interfaces
			{
				class ModuleInterface;
			}

			class Module
			{
				public:
				// Handle by which DLLs are referenced
				typedef HMODULE HandleType;
				// Store handle for unload & function lookup
				HandleType handle;

				public:
				std::string moduleName;

				public:
				// Signature for the modules's registration function
				typedef void Register(Module&);

				public:
				// Collection of implemented interfaces in module
				std::vector<Interfaces::ModuleInterface*> interfaces;

				public:
				// Constructor with string path arg
				Module(const std::string& path)
				{
					// Load module
					handle = Load(path);

					// Register module
					std::function func = GetFunctionPointer<Register>(handle, "Register");
					func(*this);
				}


				private:
				// Loads the DLL from the specified path
				HandleType Load(const std::string& path)
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
				void Unload(HandleType sharedLibraryHandle)
				{
					BOOL result = FreeLibrary(sharedLibraryHandle);
					if (result == FALSE)
					{
						throw std::runtime_error("Could not unload DLL");
					}
				}

				public:
				// Looks up a function exported by the DLL
				template<typename TFunctionSigniture>
				TFunctionSigniture* GetFunctionPointer (HandleType sharedLibraryHandle, const std::string& functionName)
				{
					FARPROC functionAddress = GetProcAddress(sharedLibraryHandle, functionName.c_str());

					if (functionAddress == NULL)
					{
						throw std::runtime_error("Could not find exported function");
					}

					return reinterpret_cast<TFunctionSigniture*>(functionAddress);
				}
			};
		}
	}
}


#endif // !MODULE_H
