# Main script entry point

# Standard modules
import sys                      # Script args, exit
import getopt                   # Option handling
from inspect import signature   # Function arg count

# Tokens
from Conductor.TokenDefinitions import optionTokens
from Conductor.OptionToken import OptionToken

import ExternalScript.ExternalScriptRunner as ExternalScriptRunner

def UnidentifiedOptionError():
    print("Unidentified option")
    sys.exit(1)

def MixedOptionsError():
    print("Mixed options")
    sys.exit(1)

# Main function
def main(argv):
    # Try and map args to options
    try:
        opts, args = getopt.getopt(argv, OptionToken.shortTokenDefinitions, OptionToken.longTokenDefinitions)
    except getopt.GetoptError:
        UnidentifiedOptionError()
    
    optionGroup = ""

    # Iterate through options, get relevant arg for option if there's any
    for opt, arg in opts:
        # Iterate through optionTokens and match them to opt string
        for token in optionTokens:
            if (opt == token.GetShortOptionToken()):
                # Set option token group if not already set
                if (optionGroup == "" and token.tokenGroup != ""): optionGroup = token.tokenGroup

                # If token has different tokenGroup than optionGroup and is not empty, then there are mixed options
                if (token.tokenGroup != "" and token.tokenGroup != optionGroup) : MixedOptionsError()

                # Call token function and pass arg to it, if it defines a function argument
                if (len(signature(token.tokenFunc).parameters) == 0): token.tokenFunc()
                else: token.tokenFunc(arg)

    ExternalScriptRunner.GetRootDir()
    ExternalScriptRunner.BuildScriptCollection()
    ExternalScriptRunner.RegisterDatabases()
    ExternalScriptRunner.RegisterPaths()

    print("")

# Call main if this script is called
if __name__ == "__main__":
    main(sys.argv[1:])