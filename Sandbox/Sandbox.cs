using System;
using System.Collections.Generic;
using System.Text;
using QED.BuildTool.Core;

namespace QED
{
    namespace BuildTool
    {
        [RegisterPath]
        public class SandboxDirectory : Directory
        {
            public SandboxDirectory()
            {
                FileGroup sources = new FileGroup(this, "SandboxSrc");
                sources.AddFiles("*.cpp", true, "SandboxPCH");

                FileGroup headers = new FileGroup(this, "SandboxHead");
                headers.AddFiles("*.h", true, "SandboxPCH");

                FileGroup pchHeader = new FileGroup(this, "SandboxPCHHead");
                pchHeader.AddFile("PCH\\SandboxPCH.h");

                FileGroup pchSrc = new FileGroup(this, "SandboxPCHSrc");
                pchSrc.AddFile("PCH\\SandboxPCH.cpp");
            }
        }

        [RegisterPath]
        [RegisterProject]
        public class Sandbox : Project
        {
            public Sandbox()
            {
                // Basic config
                Name = "Sandbox";
                OutputType = OutputType.SharedLibrary;
                CppVersion = CppVersion.cpp17;

                // Directories
                OutputDirectory = BuildTool.GetDirectory("BuildSandboxDirectory");
                HeaderFileGroups.Add("SandboxHead");
                SourceFileGroups.Add("SandboxSrc");

                // References
                AdditionalReferences = new List<string>()
                {
                    "Engine"
                };

                // Targets
                Targets = new Targets()
                {
                    Architecture = Architecture.x64,
                    Platform = Platform.Windows | Platform.Linux,
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
                        Platform.Windows | Platform.Linux,
                        Configuration.Release | Configuration.Debug
                    )
                    {
                        PreprocessorDefinitions = new List<string>()
                        {
                            "MAKE_MODULE",          // QED API
                            "QED_ENABLE_ASSERTS",   // Asserts
                            "GLFW_INCLUDE_NONE",    // GLAD already includes OpenGL
                        },

                        AdditionalIncludeDirs = new List<string>()
                        {
                            BuildTool.GetDirectory("VendorSPDLogDirectory").DirectoryPath + "\\" +"include",
                            BuildTool.GetDirectory("VendorImGuiDirectory").DirectoryPath,
                            BuildTool.GetDirectory("VendorGLMDirectory").DirectoryPath,
                            BuildTool.GetDirectory("CommonDirectory").DirectoryPath,
                            BuildTool.GetDirectory("SandboxDirectory").DirectoryPath + "\\" + "PCH",
                            BuildTool.GetDirectory("EngineDirectory").DirectoryPath
                        },

                        AdditionalReferences = new List<string>()
                        {
                            BuildTool.GetDirectory("BuildEngineDirectory").DirectoryPath + "\\" + "Engine.lib"
                        }
                    },

                    // Windows
                    new Conditional
                    (
                        // Filters
                        Architecture.x64,
                        Platform.Windows,
                        Configuration.Release | Configuration.Debug
                    )
                    {
                        PreprocessorDefinitions = new List<string>()
                        {
                            "QED_WINDOWS"
                        }
                    },

                    // Debug
                    new Conditional
                    (
                        // Filters
                        Architecture.x64,
                        Platform.Windows | Platform.Linux,
                        Configuration.Debug
                    )
                    {
                        // Configuration
                        EnableOptimizations = false,
                        UseDebugStdLibrary = true,

                        PreprocessorDefinitions = new List<string>()
                        {
                            "QED_SANDBOX_DEBUG",
                            "DEBUG"
                        }
                    },

                    // Release
                    new Conditional
                    (
                        // Filters
                        Architecture.x64,
                        Platform.Windows | Platform.Linux,
                        Configuration.Release
                    )
                    {
                        // Configuration
                        EnableOptimizations = true,
                        UseDebugStdLibrary = false,

                        PreprocessorDefinitions = new List<string>()
                        {
                            "QED_SANDBOX_RELEASE"
                        }
                    }
                };

                // Windows

            }
        }
    }
}