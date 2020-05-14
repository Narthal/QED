
import Database.RegisterDatabase as RegisterDB

def RegisterDatabase(path):
	# Get dir path from this script path
	path = path.parent
	# Register database
	RegisterDB.Register(path.joinpath("Tools/Registry.db"))