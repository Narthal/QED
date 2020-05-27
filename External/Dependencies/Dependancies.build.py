
import os

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