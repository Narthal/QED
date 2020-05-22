

import os

import Registration.RegisterPaths as RegisterP



# Stop build script search, this file is at the root of the project
rootDir = True

# Get dir path from this script path
parentPath = path.parent

# Collect all root directories
rootDirs = []
for root, dirs, files in os.walk(parentPath):
	for dir in dirs:
		# Ignore .git, .vs, .etc
		if (not '.' in dir):
			rootDirs.append(dir)
	break

# Add all root directories to searchDirs
searchDirs = rootDirs

def RegisterPaths():
	# Register root directories with tag dirName + Dir and RootDir
	for rootDir in rootDirs:
		RegisterP.RegisterDirectory(parentPath, rootDir, rootDir + "Dir RootDir")