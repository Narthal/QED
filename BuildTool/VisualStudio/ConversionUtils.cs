using System;
using System.Collections.Generic;
using System.Text;

namespace QED
{
    namespace BuildTool
    {
        namespace VisualStudio
        {
            public static class ConversionUtils
            {
                public static string GetConfigurationString(Core.Configuration configuration)
                {
                    return Enum.GetName(configuration.GetType(), configuration);
                }

                public static string GetArchitectureString(Core.Architecture architecture)
                {
                    switch (architecture)
                    {
                        case Core.Architecture.x86:
                            return "Win32";
                            break;
                        case Core.Architecture.x64:
                            return "x64";
                            break;
                        default:
                            return "";
                            break;
                    }
                }

                public static string GetOutputTypeString(Core.OutputType outputType)
                {
                    return Enum.GetName(outputType.GetType(), outputType);
                }
            }
        }
    }
}
