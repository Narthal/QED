# Define option tokens here

from OptionToken import OptionToken

optionTokens = []

# Help token definition
def Help():
	print("help")
optionTokens.append(OptionToken.CreateOptionToken("help", 'h', Help, False, "", "Lists all option tokens and any documentation attached to them"))

# Option token definitions
def Input(file):
	print("Input file : " + file)
optionTokens.append(OptionToken.CreateOptionToken("input", 'i', Input, True, "io"))
optionTokens.append(OptionToken.CreateOptionToken("output", 'o'))
