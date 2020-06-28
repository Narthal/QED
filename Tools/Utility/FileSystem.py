
import os
import inspect

import Registration.RegisterPaths as RegisterP

def CreateDirectory(root, dir, tags):
	# Get path
	newPath = root.joinpath(dir)

	# Try to create new dir
	try:
		os.makedirs(newPath)
	except OSError:
		print("Creation of the directory %s failed" % newPath)
	else:
		print("Successfully created the directory %s" % newPath)

	# Get build script caller info
	callerFile = inspect.stack()[1][1]
	callerFunction = inspect.stack()[1][3]
	generated = callerFile
	if (callerFunction != "<module>"):
		generated += ' ' + callerFunction

	# Register new directory
	RegisterP.RegisterDirectory(root, dir, tags, generated)
