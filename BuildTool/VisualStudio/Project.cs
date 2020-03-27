using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;

namespace QED
{
    namespace BuildTool
    {
        namespace VisualStudio
        {
            public class Project
            {
                public void Generate(Core.Project project)
                {
                    Console.WriteLine();
                    Console.WriteLine("Initializing project generation on project : " + project.Name);

                    // Create XML writer
                    var settings = new XmlWriterSettings()
                    {
                        Indent = true,
                        IndentChars = "  ",
                        Encoding = Encoding.UTF8,

                    };

                    StringBuilder sb = new StringBuilder();

                    using (XmlWriter writer = XmlWriter.Create(sb, settings))
                    {
                        // 1
                        // Write xml version, encoding
                        writer.WriteStartDocument();

                        // 2
                        // Project header element
                        WriteProjectHeader(writer);

                        // 3
                        // Configuration / Platform
                        WriteConfiguration(writer, project);

                        // 4
                        // Globals
                        WriteGlobals(writer, project);

                        // 5
                        // Import cpp default props
                        WriteImportDefaultCppProperties(writer);

                        // 6
                        // Output type / toolset
                        WriteOutputTypeAndToolset(writer, project);

                        // 7
                        // Import cpp props
                        WriteImportCppProperties(writer);

                        // 8
                        // Set incremental linking to project value
                        WriteIncrementCompileSetting(writer, project);

                        // 9
                        // Set compiler options such as runtme lib
                        WriteCompilerConfig(writer, project);

                        // 10
                        // Compiled files
                        WriteIncludedSourceFiles(writer, project);

                        // 11
                        // Included files
                        WriteIncludedHeaderFiles(writer, project);

                        // 12
                        // Import cpp targets
                        WriteImportCppTargets(writer);

                        // End of xml
                        writer.WriteEndElement();   // End project element
                        writer.WriteEndDocument();  // End document

                        writer.Flush();
                    }

                    // Write project to console
                    Console.WriteLine("Generated project");
                    Console.ForegroundColor = ConsoleColor.Yellow;
                    Console.Write(sb);
                    Console.WriteLine();
                    Console.ResetColor();

                    // Write project to file
                    string path = project.OutputDirectory.DirectoryPath + '\\' + project.Name + ".vcxproj";
                    using (System.IO.StreamWriter file = new System.IO.StreamWriter(path))
                    {
                        file.Write(sb.ToString());
                    }
                    Console.WriteLine("Done writing project file at " + path);
                }

                private void WriteProjectHeader(XmlWriter writer)
                {
                    writer.WriteStartElement("Project", "http://schemas.microsoft.com/developer/msbuild/2003");
                    writer.WriteAttributeString("DefaultTargets", "Build");
                    writer.WriteAttributeString("ToolsVersion", "16.0");
                    writer.WriteAttributeString("xmlns", "http://schemas.microsoft.com/developer/msbuild/2003");
                }

                private void WriteConfiguration(XmlWriter writer, Core.Project project)
                {
                    // Start itemgroup
                    writer.WriteStartElement("ItemGroup");
                    writer.WriteAttributeString("Label", "ProjectConfigurations");

                    // Architecture * Platform * Configuration = number of times writer need to write a target
                    foreach (Core.Architecture architecture in project.Targets.GetArchitectureFlags())
                    {
                        foreach (Core.Platform platform in project.Targets.GetPlatformFlags())
                        {
                            foreach (Core.Configuration configuration in project.Targets.GetConfigurationFlags())
                            {
                                string config = ConversionUtils.GetConfigurationString(configuration);
                                string arch = ConversionUtils.GetArchitectureString(architecture);

                                writer.WriteStartElement("ProjectConfiguration");
                                writer.WriteAttributeString("Include", config + '|' + arch);
                                writer.WriteElementString("Configuration", config);
                                writer.WriteElementString("Platform", arch);
                                writer.WriteEndElement();
                            }
                        }
                    }

                    // End itemgroup
                    writer.WriteEndElement();
                }

                private void WriteGlobals(XmlWriter writer, Core.Project project)
                {
                    // Start itemgroup
                    writer.WriteStartElement("PropertyGroup");
                    writer.WriteAttributeString("Label", "Globals");

                    writer.WriteElementString("ProjectGuid", '{' + GUID.GetGUID() + '}');
                    writer.WriteElementString("IgnoreWarnCompileDuplicatedFilename", "true");
                    writer.WriteElementString("Keyword", "Win32Proj");
                    writer.WriteElementString("RootNamespace", project.Name);
                    writer.WriteElementString("WindowsTargetPlatformVersion", "10.0");

                    // End itemgroup
                    writer.WriteEndElement();
                }

                private void WriteImportDefaultCppProperties(XmlWriter writer)
                {
                    writer.WriteStartElement("Import");
                    writer.WriteAttributeString("Project", @"$(VCTargetsPath)\Microsoft.Cpp.default.props");
                    writer.WriteEndElement();
                }

                private void WriteOutputTypeAndToolset(XmlWriter writer, Core.Project project, string toolset = "v142")
                {
                    foreach (Core.Architecture architecture in project.Targets.GetArchitectureFlags())
                    {
                        foreach (Core.Platform platform in project.Targets.GetPlatformFlags())
                        {
                            foreach (Core.Configuration configuration in project.Targets.GetConfigurationFlags())
                            {
                                writer.WriteStartElement("PropertyGroup");
                                writer.WriteAttributeString("Label", "Configuration");
                                writer.WriteElementString("ConfigurationType", ConversionUtils.GetOutputTypeString(project.OutputType));
                                writer.WriteElementString("PlatformToolset", toolset);
                                writer.WriteElementString("CharacterSet", "Unicode");
                                writer.WriteEndElement();
                            }
                        }
                    }
                }

                private void WriteImportCppProperties(XmlWriter writer)
                {
                    writer.WriteStartElement("Import");
                    writer.WriteAttributeString("Project", @"$(VCTargetsPath)\Microsoft.Cpp.props");
                    writer.WriteEndElement();
                }

                private void WriteIncrementCompileSetting(XmlWriter writer, Core.Project project)
                {
                    foreach (Core.Conditional conditional in project.Conditionals)
                    {
                        writer.WriteStartElement("PropertyGroup");
                        writer.WriteAttributeString("Condition", "'$(Configuration)|$(Platform)'=='" + ConversionUtils.GetConfigurationString(conditional.ConfigurationFilters) + '|' + ConversionUtils.GetArchitectureString(conditional.ArchitectureFilters) + '\'');
                        writer.WriteElementString("LinkIncremental", conditional.EnableIncrementalLinking.ToString());
                        writer.WriteEndElement();
                    }
                }

                private void WriteCompilerConfig(XmlWriter writer, Core.Project project)
                {
                    foreach (Core.Conditional conditional in project.Conditionals)
                    {
                        writer.WriteStartElement("ItemDefinitionGroup");

                        writer.WriteAttributeString("Condition", "'$(Configuration)|$(Platform)'=='" + ConversionUtils.GetConfigurationString(conditional.ConfigurationFilters) + '|' + ConversionUtils.GetArchitectureString(conditional.ArchitectureFilters) + '\'');
                        
                        // CLcompile
                        writer.WriteStartElement("ClCompile");
                        writer.WriteElementString("WarningLevel", "Level3"); // TODO: default value here, expose to project data

                        if (conditional.EnablePrecompiledHeaders == true)
                        {
                            writer.WriteElementString("PrecompiledHeader", "Use");
                        }
                        writer.WriteElementString("PrecompiledHeaderFile", "pch.h"); // TODO: hardcoded pch name

                        // TODO: implement debug data handling
                        // <DebugInformationFormat> EditAndContinue / ProgramDatabase </DebugInformationFormat>

                        writer.WriteElementString("Optimization", ConversionUtils.GetOptimizationString(conditional.EnableOptimizations));
                        writer.WriteElementString("RuntimeLibrary", ConversionUtils.GetRuntimeLibraryString(conditional.ConfigurationFilters));

                        string definitions = "";
                        foreach (string definition in conditional.PreprocessorDefinitions)
                        {
                            definitions += definition;
                            definitions += ';';
                        }
                        writer.WriteElementString("PreprocessorDefinitions", definitions + "%(PreprocessorDefinitions)");
                        writer.WriteEndElement();

                        // Link
                        writer.WriteStartElement("Link");
                        writer.WriteElementString("SubSystem", "Console"); // TODO: hardcoded console subsystem
                        writer.WriteElementString("GenerateDebugInformation", "true");
                        writer.WriteEndElement();

                        writer.WriteEndElement();
                    }
                }
                
                private void WriteIncludedSourceFiles(XmlWriter writer, Core.Project project)
                {
                    // Start itemgroup
                    writer.WriteStartElement("ItemGroup");

                    foreach (string fileGroup in project.SourceFileGroups)
                    {
                        foreach (string filePath in BuildTool.fileGroups[fileGroup])
                        {
                            writer.WriteStartElement("ClCompile");
                            writer.WriteAttributeString("Include", filePath);
                            writer.WriteEndElement();
                        }
                    }

                    string pchcpp = BuildTool.fileGroups[project.Conditionals[0].PrecompiledHeaderFileGroup][0];    // TODO: super bad, get pch.cpp 
                    writer.WriteStartElement("ClCompile");
                    writer.WriteAttributeString("Include", pchcpp);
                    writer.WriteElementString("PrecompiledHeader", "Create");
                    writer.WriteEndElement();

                    // End itemgroup
                    writer.WriteEndElement();
                }

                private void WriteIncludedHeaderFiles(XmlWriter writer, Core.Project project)
                {
                    // Start itemgroup
                    writer.WriteStartElement("ItemGroup");

                    foreach (string fileGroup in project.HeaderFileGroups)
                    {
                        foreach (string filePath in BuildTool.fileGroups[fileGroup])
                        {
                            writer.WriteStartElement("ClInclude");
                            writer.WriteAttributeString("Include", filePath);
                            writer.WriteEndElement();
                        }

                        string pchcpp = BuildTool.fileGroups[project.Conditionals[0].PrecompiledHeaderFileGroup][1];    // TODO: super bad, get pch.cpp 
                        writer.WriteStartElement("ClInclude");
                        writer.WriteAttributeString("Include", pchcpp);
                        writer.WriteEndElement();
                    }

                    // End itemgroup
                    writer.WriteEndElement();
                }

                private void WriteImportCppTargets(XmlWriter writer)
                {
                    writer.WriteStartElement("Import");
                    writer.WriteAttributeString("Project", @"$(VCTargetsPath)\Microsoft.Cpp.Targets");
                    writer.WriteEndElement();
                }


                // TODO:
                // [ ] Precompiled header
                // [ ] Warning level (VS)
                // [ ] Preprocessor defs
                // [ ] Additional include dirs (VS)
                // [ ] Optimizations switch
                // [ ] STD lib linkage switch
                // [ ] STD lib debug switch
                // [ ] Additional options (per use case)
                // [ ] Language standard

                // TODO: write vs project generator extensions

                // Cheat sheet
                //<PrecompiledHeader>Use</PrecompiledHeader>
                //<PrecompiledHeaderFile>EnginePCH.h</PrecompiledHeaderFile>
                //<WarningLevel>Level3</WarningLevel>
                //<PreprocessorDefinitions>MAKE_DLL;QED_ENGINE_WINDOWS;BUILD_OS="10.0 0.0 18362.0 Windows 10 Home";GLFW_INCLUDE_NONE;QED_ENGINE_DEBUG;DEBUG;%(PreprocessorDefinitions)</PreprocessorDefinitions>
                //<AdditionalIncludeDirectories>..\Common;PCH;..\External\Dependencies\GLFW\include;..\External\Dependencies\GLAD\include;..\External\Dependencies\ImGui;..\External\Dependencies\GLM;%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
                //<DebugInformationFormat>EditAndContinue</DebugInformationFormat>
                //<Optimization>Disabled</Optimization>
                //<RuntimeLibrary>MultiThreadedDebug</RuntimeLibrary>
                //<AdditionalOptions>/sdl- %(AdditionalOptions)</AdditionalOptions>
                //<LanguageStandard>stdcpp17</LanguageStandard>
            }
        }
    }
}
