

import Database.RegisterPaths as RegisterP

rootDir = True
searchDirs = ["Database"]

def RegisterPaths(path):
	# Get dir path from this script path
	path = path.parent
	
	# Register directories
	RegisterP.RegisterDirectory(path.joinpath("Engine"), "EngineDir")