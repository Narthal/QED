
import os
from pathlib import Path

from ExternalScript.ExternalScript import Script
import ExternalScript.BuildScriptAttributes as BuildScriptAttributes

from Database.RegisterDatabase import databaseCollection, databaseTags, GetDatabase

rootPath = Path()
scriptCollection = []

# 1 Get root script
# 2 Compile and run all scripts from root, collect them to a list
# 3 Call Registration functions from collection
	# 1 Handle Registry database function
	# 2 Add search dirs to registry


def GetRootDir():
	# Log
	print("Searching for root directory")
	# Get directory of this script file
	path = Path(os.path.realpath(__file__))

	global rootPath
	success, value = False, False
	while ((success == False and value == False) or path == path.root):
		# Move a directory up on path (first time this gets a diretory from filepath)
		path = path.parent
		
		# Get all files in path and run all build scripts
		buildScriptPaths = path.glob("*.build.py")
		for buildScriptPath in buildScriptPaths:
			script = Script(buildScriptPath)
			success, value = script.GetAttribute(BuildScriptAttributes.rootDirVariable)
			if (success == True and value == True):
				rootPath = Path(path)
				break

	if (success == True and value == True):
		print("Found root directory : " + str(rootPath))
		return rootPath
	else:
		raise Exception("No root directory found")

def AddScriptsInDirectoryToCollection(directory):
	# Get build scripts in directory
	buildScriptPaths = directory.glob("*.build.py")

	# Compile and run each script, add them to collection and check recursively check other directories defined in new scripts
	for scriptPath in buildScriptPaths:
		script = Script(scriptPath)
		scriptCollection.append(script)
		success, value = script.GetAttribute(BuildScriptAttributes.searchDirs)
		if (success and len(value) > 0):
			for path in value:
				AddScriptsInDirectoryToCollection(directory.joinpath(path))

def BuildScriptCollection():
	# Log
	print("Compiling build scripts")
	AddScriptsInDirectoryToCollection(rootPath)


def RegisterDatabases():
	# Log
	print("Registering databases")

	# Run Registration functions, collect database instances in a list
	for script in scriptCollection:
		success, attribute = script.GetAttribute(BuildScriptAttributes.registerDatabase)
		if (success):
			attribute()

	# Get registry db
	registryDB = GetDatabase("Registry")

	# Put database paths in Registry db
	for database, tags in zip(databaseCollection, databaseTags):
		# Get relative path of db
		relPath = Path(database.path).relative_to(rootPath)

		# If Registry doesn't contain this database path, add it to Registry
		registryDB.AddRow("pathCollection", path = relPath, type = 1, generated = 1, tags = tags)
		registryDB.Commit()

def RegisterPaths():
	# Log
	print("Registering paths")
	
	# Run Registration functions, write path in registry
	for script in scriptCollection:
		success, attribute = script.GetAttribute(BuildScriptAttributes.registerPaths)
		if (success):
			attribute()