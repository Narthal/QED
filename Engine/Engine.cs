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
                sources.AddFiles("*.cpp", true, "enginePCH");

                FileGroup headers = new FileGroup(this, "EngineHead");
                headers.AddFiles("*.h", true, "enginePCH");

                FileGroup pchHeader = new FileGroup(this, "EnginePCHHead");
                pchHeader.AddFile("PCH\\EnginePCH.h");

                FileGroup pchSrc = new FileGroup(this, "EnginePCHSrc");
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

                // References
                AdditionalReferences = new List<string>()
                {
                    "GLFW",
                    "GLAD",
                    "ImGui"
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
                            "MAKE_ENGINE",          // QED API
                            "GLFW_INCLUDE_NONE",    // GLAD already includes OpenGL
                        },

                        AdditionalIncludeDirs = new List<string>()
                        {
                            BuildTool.GetDirectory("VendorGLFWDirectory").DirectoryPath + "\\" +"include",
                            BuildTool.GetDirectory("VendorGLADDirectory").DirectoryPath + "\\" + "include",
                            BuildTool.GetDirectory("VendorImGuiDirectory").DirectoryPath,
                            BuildTool.GetDirectory("CommonDirectory").DirectoryPath,
                            BuildTool.GetDirectory("VendorGLMDirectory").DirectoryPath,
                            BuildTool.GetDirectory("VendorStbDirectory").DirectoryPath,
                            BuildTool.GetDirectory("EngineDirectory").DirectoryPath + "\\" + "PCH",
                            BuildTool.GetDirectory("EngineDirectory").DirectoryPath,
                        },

                        AdditionalReferences = new List<string>()
                        {
                            "opengl32.lib",                                                                           // OpenGL                                                                              // GLFW
                            BuildTool.GetDirectory("BuildGLFWDirectory").DirectoryPath + "/src/Debug/" + "glfw3.lib", // glfw3.lib                                                                            // GLAD
                            BuildTool.GetDirectory("BuildGLADDirectory").DirectoryPath + "\\" + "glad.lib",           // glad.lib                                                                             // ImGui
                            BuildTool.GetDirectory("BuildImGuiDirectory").DirectoryPath + "\\" + "imgui.lib"          // imgui.lib
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
                            "/sdl-"
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


