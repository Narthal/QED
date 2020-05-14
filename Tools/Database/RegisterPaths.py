
import os
from pathlib import Path

import ExternalScript.ExternalScriptRunner as scriptRunner
from Database.RegisterDatabase import databaseCollection, GetDatabase

def Register(dirPath, pathGlob, tags):
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