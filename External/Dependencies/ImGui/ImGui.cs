using System;
using System.Collections.Generic;
using System.Text;
using QED.BuildTool.Core;

namespace QED
{
    namespace BuildTool
    {
        [RegisterPath]
        public class ImGuiDirectory : Directory
        {
            public ImGuiDirectory()
            {

            }
        }

        [RegisterPath]
        [RegisterProject]
        public class ImGui : Project
        {
            public ImGui()
            {
                // Basic config
                Name = "ImGui";
                OutputType = OutputType.StaticLibrary;
                CppVersion = CppVersion.cpp17;

                // Directories
                OutputDirectory = BuildTool.GetDirectory("BuildImGuiDirectory");
                HeaderFileGroups.Add("ImGuiHead");
                SourceFileGroups.Add("ImGuiSrc");


                // Targets
                Targets = new Targets()
                {
                    Architecture = Architecture.x64,
                    Platform = Platform.Windows,
                    Configuration = Configuration.Debug | Configuration.Release
                };

                // Conditionals
                Conditionals = new List<Conditional>()
                {
                    // All configs
                    new Conditional
                    (
                        // Filters
                        Architecture.x64,
                        Platform.Windows,
                        Configuration.Release | Configuration.Debug
                    )
                    {
                        PreprocessorDefinitions = new List<string>() { "IMGUI_API=__declspec(dllexport)" },
                        AdditionalIncludeDirs = new List<string>() { BuildTool.GetDirectory("VendorImGuiDirectory").DirectoryPath }
                    },

                    // Debug
                    new Conditional
                    (
                        // Filters
                        Architecture.x86 | Architecture.x64,
                        Platform.Windows,
                        Configuration.Debug
                    )
                    {
                        // Configuration
                        EnableOptimizations = false,
                        UseDebugStdLibrary = false,
                    },

                    // Release
                    new Conditional
                    (
                        // Filters
                        Architecture.x86 | Architecture.x64,
                        Platform.Windows,
                        Configuration.Release
                    )
                    {
                        // Configuration
                        EnableOptimizations = true,
                        UseDebugStdLibrary = false,
                    }
                };
            }
        }
    }
}


