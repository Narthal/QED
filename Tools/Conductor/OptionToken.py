



class OptionToken:
	# Token collection to check redefinition
	tokenNames = []
	tokenAliases = ""

	# Token definitions
	longTokenDefinitions = []
	shortTokenDefinitions = ""

	# Ctor
	def __init__(self, tokenName, tokenAlias, tokenFunc, hasArgument, tokenGroup, tokenDoc):
		# If both tokenName & tokenAlias is empty, the optionToken cannot be called. Throw error in such a case
		if (tokenName == "" and tokenAlias == ''):
			raise Exception("Uncallable option token : both tokenName and tokenAlias is empty")

		# If tokenAlias is longer than 1 character, throw error as only single characters are valid aliases
		if (len(tokenAlias) > 1):
			raise Exception("Invalid tokenAlias : " + tokenAlias + " . Only single characters are valid aliases")

		# If either tokenName or tokenAlias exists in static collection, throw error, as each option must have unique tokenNames and tokenAliases
		if (tokenName != "" and tokenName in OptionToken.tokenNames):
			raise Exception("Redefinition of tokenName : " + tokenName + " each OptionToken must have a unique tokenName")
		if (tokenAlias != '' and tokenAlias in OptionToken.tokenAliases):
			raise Exception("Redefinition of tokenAlias : " + tokenAlias + " . Each OptionToken must have a unique tokenAlias")
		
		# Set other member variables
		self.tokenName = tokenName
		self.tokenAlias = tokenAlias
		self.tokenFunc = tokenFunc
		self.hasArgument = hasArgument
		self.tokenGroup = tokenGroup
		self.tokenDoc = tokenDoc

		# Add token name and alias to static collection
		if (tokenName != ""):
			OptionToken.tokenNames.append(tokenName)
		if (tokenAlias != ''):
			OptionToken.tokenAliases += tokenAlias

		# Add definitions
		if (tokenName != ""):
			OptionToken.longTokenDefinitions.append(self.GetLongOptionDefinition())
		if (tokenAlias != ''):
			OptionToken.shortTokenDefinitions += self.GetShortOptionDefinition()

	# Create short option token
	@classmethod
	def CreateShortOptionToken(cls, tokenAlias, tokenFunc = lambda : None, hasArgument = False, tokenGroup = "", tokenDoc = ""):
		return cls("", tokenAlias, tokenFunc, hasArgument, tokenGroup, tokenDoc)

	# Create long option token
	@classmethod
	def CreateLongOptionToken(cls, tokenName, tokenFunc = lambda : None, hasArgument = False, tokenGroup = "", tokenDoc = ""):
		return cls(tokenName, "", tokenFunc, hasArgument, tokenGroup, tokenDoc)

	# Create full option token
	@classmethod
	def CreateOptionToken(cls, tokenName, tokenAlias, tokenFunc = lambda : None, hasArgument = False, tokenGroup = "", tokenDoc = ""):
		return cls(tokenName, tokenAlias, tokenFunc, hasArgument, tokenGroup, tokenDoc)

	# Get option definition
	def GetShortOptionDefinition(self):
		# If no alias is defined, no option definition can be constructed
		if (self.tokenAlias == ""):
			return ""

		# Construct option definition
		optionDefinition = self.tokenAlias
		if (self.hasArgument == True):
			optionDefinition += ':'
		return optionDefinition

	# Get option definition
	def GetLongOptionDefinition(self):
		# If no tokenName is defined, no option definition can be constructed
		if (self.tokenName == ""):
			return ""
		
		# Construct long option definition
		longOptionDefinition = self.tokenName
		if (self.hasArgument == True):
			longOptionDefinition += '='
		return longOptionDefinition

	# Get short option token
	def GetShortOptionToken(self):
		return '-' + self.tokenAlias

	# Get long option token
	def GetLongOptionToken(self):
		return '--' + self.tokenName