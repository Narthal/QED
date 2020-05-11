#include "EnginePCH.h"
#include "Runtime.h"

#define PY_SSIZE_T_CLEAN
#include <Python.h>

namespace QED
{
	namespace Engine
	{
		namespace Script
		{
			Runtime::Runtime()
			{
				std::string pythonHome = "C:\\Users\\balas\\source\\GitHubRepos\\QED\\External\\Vendor\\cpython";
				std::string scriptName = "multiply";
				std::string mainFunctionName = "multiply";
				std::vector<int> funcArgs = { 2, 3 };

				PyObject* name;		// Runtime name
				PyObject* module;	// File to load
				PyObject* func;		// Main function to call in file
				PyObject* args;		// Args to pass to main function
				PyObject* value;	// Return value of main function

				// Initialize
				size_t pythonHomeLocaleString;
				Py_SetPythonHome(Py_DecodeLocale(pythonHome.c_str(), &pythonHomeLocaleString));
				Py_Initialize();
				name = PyUnicode_DecodeFSDefault(scriptName.c_str());
				// TODO: error check name

				

				// Load module
				module = PyImport_Import(name);
				Py_DECREF(name);

				if (module != NULL)
				{
					func = PyObject_GetAttrString(module, mainFunctionName.c_str());
					/* pFunc is a new reference */

					if (func && PyCallable_Check(func))
					{
						args = PyTuple_New(2);
						for (int i = 0; i < funcArgs.size(); ++i)
						{
							value = PyLong_FromLong(funcArgs[i]);
							if (!value)
							{
								Py_DECREF(args);
								Py_DECREF(module);
								fprintf(stderr, "Cannot convert argument\n");
								return;
							}
							/* pValue reference stolen here: */
							PyTuple_SetItem(args, i, value);
						}
						value = PyObject_CallObject(func, args);
						Py_DECREF(args);
						if (value != NULL)
						{
							printf("Result of call: %ld\n", PyLong_AsLong(value));
							Py_DECREF(value);
						}
						else
						{
							Py_DECREF(func);
							Py_DECREF(module);
							PyErr_Print();
							fprintf(stderr, "Call failed\n");
							return;
						}
					}
					else
					{
						if (PyErr_Occurred())
							PyErr_Print();
						fprintf(stderr, "Cannot find function \"%s\"\n", mainFunctionName.c_str());
					}
					Py_XDECREF(func);
					Py_DECREF(module);
				}
				else
				{
					PyErr_Print();
					fprintf(stderr, "Failed to load \"%s\"\n", scriptName.c_str());
					return;
				}


				if (Py_FinalizeEx() < 0)
				{
					return;
				}

				return;
			}
		}
	}
}
