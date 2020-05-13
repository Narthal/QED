

class Script:
	# Ctor
	def __init__(self, path):
		# Create member variables
		self.path = path
		self.code = {}

		# Compile and execute code
		compiledCode = compile(open(path).read(), path, 'exec')
		exec(compiledCode, self.code)

		# Log
		print("Running script : " + str(path))

	def GetAttribute(self, attribute):
		# Try to get value with name valueName
		success = False
		value = ""
		try:
			value = self.code[attribute[0]]
			success = True
		except:
			pass

		if (success == True and type(value) != attribute[1]):
			success = False
			print("Incorrect type of attribute " + attribute[0] + " in build script")

		return success, value

	def SearchForAttributes(self, matchString, filterCallable = 0):
		attributes = []
		for attribute in self.code:
			if (matchString in attribute):
				if (filterCallable == 0):
					attributes.append(self.code[attribute])
				if (filterCallable == 1 and callable(self.code[attribute])):
					attributes.append(self.code[attribute])
				if (filterCallable == 2 and not callable(self.code[attribute])):
					attributes.append(self.code[attribute])

		return attributes