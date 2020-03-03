using System;
using System.Collections.Generic;
using System.Text;

using QED.BuildTool.Core;

namespace QED
{
    namespace BuildTool
    {
        [RegisterPath]
        public class TestDirectory : Directory
        {
            public TestDirectory()
            {
                FileGroup sources = new FileGroup(this, "HelloSrc");
                sources.AddFile("Main.cpp");

                FileGroup headers = new FileGroup(this, "HelloHeader");
                headers.AddFile("Main.h");
            }
        }

        [RegisterProject]
        public class TestProject : Project
        {
            public TestProject()
            {
                // Basic config
                Name = "Hello";
                OutputType = OutputType.Application;
                CppVersion = CppVersion.cpp17;

                // Directories
                OutputDirectory = BuildTool.GetDirectory("TestDirectory");
                SourceFileGroups.Add("HelloSrc");
                HeaderFileGroups.Add("HelloHeader");

                // Targets
                Targets = new Targets()
                {
                    Architecture = Architecture.x86 | Architecture.x64,
                    Platform = Platform.Windows,
                    Configuration = Configuration.Debug | Configuration.Release,
                };

                // Conditionals
                Conditionals = new List<Conditional>()
                {
                    new Conditional
                    (
                        // Filters
                        Architecture.x86 | Architecture.x64,
                        Platform.Windows,
                        Configuration.Debug
                    )
                    {
                        // Configuration

                        // Basic configuration
                        EnableOptimizations = false,
                        UseDebugStdLibrary = true,
                        StaticLinkStdLibrary = true,

                        // Precompiled headers
                        EnablePrecompiledHeaders = true,
                        PrecompiledHeaderFileGroup = "PCH",

                        // Compiler options
                        CompilerOptions = new List<string>() { "/sdl-" },

                        // Preprocessor
                        PreprocessorDefinitions = new List<string>() { "DEBUG" },
                    }
                };
            }
        }
    }
}
