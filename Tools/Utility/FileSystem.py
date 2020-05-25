
import os

import Registration.RegisterPaths as RegisterP

def CreateDirectory(root, dir, tags):
	newPath = root.joinpath(dir)
	try:
		os.makedirs(newPath)
	except OSError:
		print("Creation of the directory %s failed" % newPath)
	else:
		print("Successfully created the directory %s" % newPath)

	RegisterP.RegisterDirectory(root, dir, tags, 1)
