
import Registration.RegisterPaths as RegisterP

# Get dir path from this script path
parentPath = path.parent


def RegisterPaths():
	# Register cpython
	RegisterP.RegisterDirectory(parentPath, "cpython", "Vendor cpython PYTHONHOME")
	RegisterP.RegisterDirectory(parentPath, "cpython/Include", "Vendor cpython include")

	# Register GLAD
	RegisterP.RegisterDirectory(parentPath, "GLAD", "Vendor GLAD")

	# Register GLFW
	RegisterP.RegisterDirectory(parentPath, "GLFW", "Vendor GLFW")

	# Register GLM
	RegisterP.RegisterDirectory(parentPath, "GLM", "Vendor GLM")

	# Register ImGui
	RegisterP.RegisterDirectory(parentPath, "ImGui", "Vendor ImGui Dir")
	RegisterP.RegisterPaths(parentPath, "ImGui/**/*.cpp", "Vendor ImGui Cpp")
	RegisterP.RegisterPaths(parentPath, "ImGui/**/*.h", "Vendor ImGui Headers")

	# Register spdlog
	RegisterP.RegisterDirectory(parentPath, "spdlog", "Vendor spdlog")

	# Register SQLiteAmalgamation
	RegisterP.RegisterDirectory(parentPath, "SQLiteAmalgamation", "Vendor SQLite")

	# Register stb
	RegisterP.RegisterDirectory(parentPath, "stb", "Vendor stb")