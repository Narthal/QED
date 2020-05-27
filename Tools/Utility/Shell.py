

import os

def RunShellCommand(command):
	try:
		os.system(command)
	except:
		print("Error : Failed command " + command)