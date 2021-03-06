using System;
using System.Collections.Generic;
using System.Text;
using QED.BuildTool.Core;

namespace QED
{
    namespace BuildTool
    {
        [RegisterPath]
        public class EngineDirectory : Directory
        {
            public EngineDirectory()
            {
                FileGroup sources = new FileGroup(this, "EngineSrc");
                sources.AddFiles("*.cpp", true, "EnginePCH*");

                FileGroup headers = new FileGroup(this, "EngineHead");
                headers.AddFiles("*.h", true, "EnginePCH*");

                FileGroup pchHeader = new FileGroup(this, "EnginePCH");
                pchHeader.AddFile("PCH\\EnginePCH.h");

                FileGroup pchSrc = new FileGroup(this, "EnginePCH");
                pchSrc.AddFile("PCH\\EnginePCH.cpp");
            }
        }

        [RegisterPath]
        [RegisterProject]
        public class Engine : Project
        {
            public Engine()
            {
                // Basic config
                Name = "Engine";
                OutputType = OutputType.Application;
                CppVersion = CppVersion.cpp17;

                // Directories
                OutputDirectory = BuildTool.GetDirectory("BuildEngineDirectory");
                HeaderFileGroups.Add("EngineHead");
                SourceFileGroups.Add("EngineSrc");
                PreCompiledHeaderGroup = "EnginePCH";

                // References
                AdditionalReferences = new List<string>()
                {
                    "GLFW",
                    "GLAD",
                    "ImGui",
                    "SQLite"
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
                        EnablePrecompiledHeaders = true,

                        PreprocessorDefinitions = new List<string>()
                        {
                            "MAKE_ENGINE",          // QED API
                            "QED_ENABLE_ASSERTS",   // Asserts
                            "GLFW_INCLUDE_NONE",    // GLAD already includes OpenGL
                        },

                        AdditionalIncludeDirs = new List<string>()
                        {
                            BuildTool.GetDirectory("VendorCPythonDirectory").DirectoryPath + "\\" +"include",
                            BuildTool.GetDirectory("VendorSQLiteDirectory").DirectoryPath,
                            BuildTool.GetDirectory("VendorSPDLogDirectory").DirectoryPath + "\\" +"include",
                            BuildTool.GetDirectory("VendorGLFWDirectory").DirectoryPath + "\\" +"include",
                            BuildTool.GetDirectory("GLADCodeGenDirectory").DirectoryPath + "\\" + "include",
                            BuildTool.GetDirectory("VendorImGuiDirectory").DirectoryPath,
                            BuildTool.GetDirectory("CommonDirectory").DirectoryPath,
                            BuildTool.GetDirectory("VendorGLMDirectory").DirectoryPath,
                            BuildTool.GetDirectory("VendorStbDirectory").DirectoryPath,
                            BuildTool.GetDirectory("EngineDirectory").DirectoryPath + "\\" + "PCH",
                            BuildTool.GetDirectory("EngineDirectory").DirectoryPath,
                        },

                        AdditionalReferences = new List<string>()
                        {
                            "opengl32.lib",                                                                             // OpenGL
                            BuildTool.GetDirectory("BuildGLFWDirectory").DirectoryPath + "/src/Debug/" + "glfw3.lib",   // glfw3.lib
                            BuildTool.GetDirectory("BuildGLADDirectory").DirectoryPath + "\\" + "glad.lib",             // glad.lib
                            BuildTool.GetDirectory("BuildImGuiDirectory").DirectoryPath + "\\" + "imgui.lib",           // imgui.lib
                            BuildTool.GetDirectory("BuildSQLiteDirectory").DirectoryPath + "\\Debug\\" + "sqlite3.lib"  // sqlite3.lib
                        }
                    },

                    // Windows
                    new Conditional
                    (
                        // Filters
                        Architecture.x64,
                        Platform.Windows,
                        Configuration.Debug | Configuration.Release
                    )
                    {
                        PreprocessorDefinitions = new List<string>()
                        {
                            "QED_WINDOWS"
                        },

                        AdditionalOptions = new List<string>()
                        {
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
                            "QED_ENGINE_DEBUG",
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
                            "QED_ENGINE_RELEASE"
                        }
                    }
                };
            }
        }
    }
}


