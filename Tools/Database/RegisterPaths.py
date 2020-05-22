
import os
from pathlib import Path

import ExternalScript.ExternalScriptRunner as scriptRunner
from Database.RegisterDatabase import databaseCollection, GetDatabase

registeredFiles = 0
registeredDirs = 0

def GetNewEntryCount():
	return registeredFiles, registeredDirs

def RegisterPaths(dirPath, pathGlob, tags):
	global registeredFiles

	# Get registry
	registryDB = GetDatabase("Registry")
	
	# Get paths from pathGlob
	paths = dirPath.glob(pathGlob)

	for path in paths:
		# Get relative path of db
		relPath = path.relative_to(scriptRunner.rootPath)

		# If Registry doesn't contain this path, add it to Registry
		registryDB.AddRow("pathCollection", path = relPath, type = 1, generated = 0, tags = tags)

		# Increment registered files
		registeredFiles += 1

	registryDB.Commit()

def RegisterDirectory(parentPath, subDir, tags):
	global registeredDirs

	# Get path
	dirPath = parentPath.joinpath(subDir)

	# Get registry
	registryDB = GetDatabase("Registry")

	# Get relative path of db
	relPath = dirPath.relative_to(scriptRunner.rootPath)

	# If Registry doesn't contain this path, add it to Registry
	registryDB.AddRow("pathCollection", path = relPath, type = 0, generated = 0, tags = tags)

	# Increment registered files
	registeredDirs += 1

	registryDB.Commit()