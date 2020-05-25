
# Builtin variables
rootDirVariable = ("rootDir", bool)
searchDirs = ("searchDirs", type([]))

# Registration functions
registerDatabase = ("RegisterDatabase", type(lambda : None))
registerPaths = ("RegisterPaths", type(lambda : None))
postPathRegistration = ("PostPathRegistration", type(lambda : None))