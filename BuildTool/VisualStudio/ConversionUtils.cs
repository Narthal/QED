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
                public static string GetConfigurationString(Core.Configuration? configuration)
                {
                    return Enum.GetName(configuration.GetType(), configuration);
                }

                public static string GetArchitectureString(Core.Architecture? architecture)
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

                public static string GetOptimizationString(bool? enabled)
                {
                    // If not defined, default to false
                    bool lEnabled = false;
                    if (enabled != null)
                    {
                       lEnabled = enabled.Value;
                    }

                    if (lEnabled)
                    {
                        return "MaxSpeed";
                    }
                    else
                    {
                        return "Disabled";
                    }
                }

                public static string GetRuntimeLibraryString(bool? staticLinkRuntimeLibrary, Core.Configuration? configuration)
                {
                    bool lStaticLink = false;
                    if (staticLinkRuntimeLibrary.HasValue)
                    {
                        lStaticLink = staticLinkRuntimeLibrary.Value;
                    }

                    if (lStaticLink)
                    {
                        throw new Exception("get keyword and implement this");
                    }
                    else
                    {
                        switch (configuration)
                        {
                            case Core.Configuration.Debug:
                                return "MultiThreadedDebugDLL";
                            case Core.Configuration.Release:
                                return "MultiThreadedDLL";
                            case Core.Configuration.Distribution:
                                return "MultiThreadedDLL";
                            default:
                                throw new Exception("invalid configuration");
                        }
                    }
                }

                public static string GetOutputTypeString(Core.OutputType outputType)
                {
                    switch (outputType)
                    {
                        case Core.OutputType.Application:
                            return "Application";
                        case Core.OutputType.SharedLibrary:
                            return "DynamicLibrary";
                        case Core.OutputType.StaticLibrary:
                            return "StaticLibrary";
                        case Core.OutputType.Utility:
                            return "Utility";
                        default:
                            throw new Exception("Unknown output type");
                    }
                }

                public static string GetLanguageStandardString(Core.CppVersion cppVersion)
                {
                    switch (cppVersion)
                    {
                        case Core.CppVersion.cpp11:
                            return "stdcpp11";
                        case Core.CppVersion.cpp14:
                            return "stdcpp14";
                        case Core.CppVersion.cpp17:
                            return "stdcpp17";
                        default:
                            throw new Exception("unknown cpp version");
                    }
                }

                public static string GetTargetExtensionString(Core.OutputType outputType)
                {
                    switch (outputType)
                    {
                        case Core.OutputType.Application:
                            return ".exe";
                        case Core.OutputType.SharedLibrary:
                            return ".dll";
                        case Core.OutputType.StaticLibrary:
                            return ".lib";
                        case Core.OutputType.Utility:
                            return "";
                        default:
                            throw new Exception("unknown outputType");
                    }
                }
            }
        }
    }
}
