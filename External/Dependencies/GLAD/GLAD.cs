using System;
using System.Collections.Generic;
using System.Text;
using QED.BuildTool.Core;

namespace QED
{
    namespace BuildTool
    {
        [RegisterPath]
        public class GLADDirectory : Directory
        {
            public GLADDirectory()
            {

            }
        }

        [RegisterPath]
        [RegisterProject]
        public class GLAD : Project
        {
            public GLAD()
            {
                // Basic config
                Name = "GLAD";
                OutputType = OutputType.StaticLibrary;
                CppVersion = CppVersion.cpp17;

                // Directories
                OutputDirectory = BuildTool.GetDirectory("BuildGLADDirectory");
                HeaderFileGroups.Add("GLADHead");
                SourceFileGroups.Add("GLADSrc");


                // Targets
                Targets = new Targets()
                {
                    Architecture = Architecture.x86 | Architecture.x64,
                    Platform = Platform.Windows,
                    Configuration = Configuration.Debug | Configuration.Release
                };

                // Conditionals
                Conditionals = new List<Conditional>()
                {
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
                        AdditionalIncludeDirs = new List<string>() { BuildTool.GetDirectory("VendorGLADDirectory").DirectoryPath + "\\" + "include" },
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
                        AdditionalIncludeDirs = new List<string>() { BuildTool.GetDirectory("VendorGLADDirectory").DirectoryPath + "\\" + "include" },
                    }
                };
            }
        }
    }
}


