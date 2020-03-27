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
                sources.AddFiles("*.cpp", true, "pch.cpp");

                FileGroup headers = new FileGroup(this, "HelloHeader");
                headers.AddFiles("*.h");

                FileGroup pch = new FileGroup(this, "PCH");
                pch.AddFile("pch.cpp");
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
                PreCompiledHeaderGroup = "PCH";

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
                        // TODO: try this when conditionals are resolved into filters
                        Architecture.x86 | Architecture.x64,
                        Platform.Windows,
                        Configuration.Debug | Configuration.Release
                    )
                    {
                        // Configuration

                        // Basic configuration
                        EnableOptimizations = false,
                        UseDebugStdLibrary = true,
                        StaticLinkStdLibrary = false,

                        // Precompiled headers
                        EnablePrecompiledHeaders = true,

                        // Compiler options
                        CompilerOptions = new List<string>() { "/sdl-" },
                        EnableIncrementalLinking = true,

                        // Preprocessor
                        PreprocessorDefinitions = new List<string>() { "DEBUG" },

                        // Additional
                        AdditionalOptions = new List<string>() { "/sdl-" },
                    }
                };
            }
        }
    }
}
