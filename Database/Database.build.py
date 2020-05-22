
import Registration.RegisterDatabase as RegisterDB

def RegisterDatabase():
	# Get dir path from this script path
	parentPath = path.parent
	# Register database
	RegisterDB.Register(parentPath.joinpath("Tools/Registry.db"), "")