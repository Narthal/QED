using System;
using System.Collections.Generic;
using System.Text;
using QED.BuildTool.Core;

namespace QED
{
    namespace BuildTool
    {
        [RegisterPath]
        public class GLFWDirectory : Directory
        {
            public GLFWDirectory()
            {

            }
        }

        [RegisterProject]
        public class GLFW : Project
        {
            public GLFW()
            {
                // Basic config
                Name = "GLFW";
                OutputType = OutputType.Utility;
                CppVersion = CppVersion.cpp17;

                // Directories
                OutputDirectory = BuildTool.GetDirectory("BuildGLFWDirectory");

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
                    new Conditional
                    (
                        // Filters
                        Architecture.x86 | Architecture.x64,
                        Platform.Windows,
                        Configuration.Debug | Configuration.Release
                    )
                    {
                        // Configuration

                        PreBuildCommand = BuildTool.GetDirectory("BuildScriptsDirectory").DirectoryPath + "\\" + "rebuildGLFW.bat"
                    }
                };
            }
        }
    }
}


