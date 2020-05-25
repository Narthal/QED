
import Registration.RegisterDatabase as RegisterDB
import Utility.FileSystem as FS

# Get dir path from this script path
parentPath = path.parent

def RegisterDatabase():
	# Get dir path from this script path
	parentPath = path.parent
	# Register database
	RegisterDB.Register(parentPath.joinpath("Tools/Registry.db"), "")


def PostPathRegistration():
	FS.CreateDirectory(parentPath, "test", "test")