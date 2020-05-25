

import os

import Registration.RegisterPaths as RegisterP

# Get dir path from this script path
parentPath = path.parent

def RegisterPaths():
	# Register headers
	RegisterP.RegisterPaths(parentPath, "**/*.h", "EngineSource Headers")

	# Register cpps
	RegisterP.RegisterPaths(parentPath, "**/*.cpp", "EngineSource Cpp")

