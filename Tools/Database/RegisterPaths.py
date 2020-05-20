
import os
from pathlib import Path

import ExternalScript.ExternalScriptRunner as scriptRunner
from Database.RegisterDatabase import databaseCollection, GetDatabase

def RegisterPaths(dirPath, pathGlob, tags):
	# Get registry
	registryDB = GetDatabase("Registry")
	
	# Get paths from pathGlob
	paths = dirPath.glob(pathGlob)

	for path in paths:
		# Get relative path of db
		relPath = path.relative_to(scriptRunner.rootPath)

		# If Registry doesn't contain this path, add it to Registry
		registryDB.AddRow("pathCollection", path = relPath, type = 1, generated = 0, tags = tags)

	registryDB.Commit()

def RegisterDirectory(dirPath, tags):
	# Get registry
	registryDB = GetDatabase("Registry")

	# Get relative path of db
	relPath = dirPath.relative_to(scriptRunner.rootPath)

	# If Registry doesn't contain this path, add it to Registry
	registryDB.AddRow("pathCollection", path = relPath, type = 0, generated = 0, tags = tags)

	registryDB.Commit()