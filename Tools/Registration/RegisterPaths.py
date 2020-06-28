
import os
from pathlib import Path

import ExternalScript.ExternalScriptRunner as scriptRunner
from Registration.RegisterDatabase import databaseCollection, GetDatabase

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

	# Flag for having modified the database
	modifiedDB = False

	for path in paths:
		# Check if path exists
		exists = os.path.exists(path)

		if (exists == True):
			# If Registry doesn't contain this path, add it to Registry
			registryDB.AddRow("pathCollection", path = path, type = 1, generated = "", tags = tags)

			# Increment registered files
			registeredFiles += 1
			
			# Set modified flag to true so commit will commence at the end of the glob iteration
			modifiedDB = True

	if (modifiedDB == True):
		registryDB.Commit()

def RegisterDirectory(parentPath, subDir, tags, generated = ""):
	global registeredDirs

	# Get path
	dirPath = parentPath.joinpath(subDir)

	# Get registry
	registryDB = GetDatabase("Registry")

	# Check if path exists
	exists = os.path.exists(dirPath)
	
	if (exists == True):
		# If Registry doesn't contain this path, add it to Registry
		registryDB.AddRow("pathCollection", path = dirPath, type = 0, generated = generated, tags = tags)

		# Increment registered files
		registeredDirs += 1

		registryDB.Commit()