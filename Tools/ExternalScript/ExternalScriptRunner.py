
import os
from pathlib import Path

from ExternalScript.ExternalScript import Script
import ExternalScript.BuildScriptAttributes as BuildScriptAttributes


rootPath = Path()
scriptCollection = []

# 1 Get root dir
# 2 Compile and run all scripts from root, collect them to a list
# 3 Call Registration functions from collection
	# 1 Get handle database registrations
	# 2 Populate databases by handling other registration functions


def GetRootDir():
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
	AddScriptsInDirectoryToCollection(rootPath)


def CallRegistrationFunctions():
	for script in scriptCollection:
		success, attribute = script.GetAttribute(BuildScriptAttributes.registerDatabase)
		if (success):
			attribute()