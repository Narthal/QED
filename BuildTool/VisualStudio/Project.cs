using QED.BuildTool.Core;
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
                        // Included files
                        WriteIncludedHeaderFiles(writer, project);

                        // 11
                        // Source files
                        WriteIncludedSourceFiles(writer, project);

                        // 12
                        // Add links to other projects
                        WriteProjectReferences(writer, project);

                        // 13
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
                    using (System.IO.StreamWriter file = new System.IO.StreamWriter(project.Path))
                    {
                        file.Write(sb.ToString());
                    }
                    Console.WriteLine("Done writing project file at " + project.Path);
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

                    writer.WriteElementString("ProjectGuid", '{' + GUID.predefinedGUIDs[project.ProjectID] + '}');
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
                    foreach (Core.Filter filter in project.Filters)
                    {
                        writer.WriteStartElement("PropertyGroup");
                        writer.WriteAttributeString("Condition", "'$(Configuration)|$(Platform)'=='" + ConversionUtils.GetConfigurationString(filter.ConfigurationFilter) + '|' + ConversionUtils.GetArchitectureString(filter.ArchitectureFilter) + '\'');
                        writer.WriteElementString("LinkIncremental", filter.EnableIncrementalLinking.ToString());
                        writer.WriteElementString("OutDir", project.OutputDirectory.DirectoryPath + '\\');
                        writer.WriteElementString("IntDir", project.OutputDirectory.DirectoryPath + "\\Intermediate\\");
                        writer.WriteElementString("TargetName", project.Name);
                        writer.WriteElementString("TargetExt", ConversionUtils.GetTargetExtensionString(project.OutputType));
                        writer.WriteEndElement();
                    }
                }

                private void WriteCompilerConfig(XmlWriter writer, Core.Project project)
                {
                    foreach (Core.Filter filter in project.Filters)
                    {
                        writer.WriteStartElement("ItemDefinitionGroup");

                        writer.WriteAttributeString("Condition", "'$(Configuration)|$(Platform)'=='" + ConversionUtils.GetConfigurationString(filter.ConfigurationFilter) + '|' + ConversionUtils.GetArchitectureString(filter.ArchitectureFilter) + '\'');
                        
                        // CLcompile
                        writer.WriteStartElement("ClCompile");
                        writer.WriteElementString("WarningLevel", "Level3"); // TODO: default value here, expose to project data

                        if (filter.EnablePrecompiledHeaders == true)
                        {
                            writer.WriteElementString("PrecompiledHeader", "Use");
                        }
                        writer.WriteElementString("PrecompiledHeaderFile", "pch.h"); // TODO: hardcoded pch name

                        // TODO: implement debug data handling
                        // <DebugInformationFormat> EditAndContinue / ProgramDatabase </DebugInformationFormat>

                        writer.WriteElementString("Optimization", ConversionUtils.GetOptimizationString(filter.EnableOptimizations));
                        writer.WriteElementString("RuntimeLibrary", ConversionUtils.GetRuntimeLibraryString(filter.StaticLinkStdLibrary, filter.ConfigurationFilter));

                        string definitions = "";
                        foreach (string definition in filter.PreprocessorDefinitions)
                        {
                            definitions += definition;
                            definitions += ';';
                        }
                        writer.WriteElementString("PreprocessorDefinitions", definitions + "%(PreprocessorDefinitions)");

                        string additionalIncludePaths = "";
                        foreach (string includePath in filter.AdditionalIncludeDirs)
                        {
                            additionalIncludePaths += includePath + ';';
                        }
                        writer.WriteElementString("AdditionalIncludeDirectories", additionalIncludePaths + "%(AdditionalIncludeDirectories)");

                        string options = "";
                        foreach (var option in filter.AdditionalOptions)
                        {
                            options += option + ';';
                        }
                        writer.WriteElementString("AdditionalOptions", options + "%(AdditionalOptions)");

                        writer.WriteElementString("LanguageStandard", ConversionUtils.GetLanguageStandardString(project.CppVersion));

                        writer.WriteEndElement();

                        // Link
                        writer.WriteStartElement("Link");
                        writer.WriteElementString("SubSystem", "Console"); // TODO: hardcoded console subsystem
                        writer.WriteElementString("GenerateDebugInformation", "true");

                        string references = "";
                        foreach (var reference in filter.AdditionalReferences)
                        {
                            references += reference + ';';
                        }
                        writer.WriteElementString("AdditionalDependencies", references + "%(AdditionalDependencies)");

                        writer.WriteEndElement();

                        writer.WriteStartElement("PostBuildEvent");
                        writer.WriteElementString("Command", filter.PostBuildCommand);
                        writer.WriteEndElement();

                        writer.WriteStartElement("PreBuildEvent");
                        writer.WriteElementString("Command", filter.PreBuildCommand);
                        writer.WriteEndElement();

                        writer.WriteEndElement();
                    }
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
                            writer.WriteAttributeString("Include", Utils.GetRelativePath(filePath, project.GetProjectDirectory()));
                            writer.WriteEndElement();
                        }
                    }

                    // End itemgroup
                    writer.WriteEndElement();
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
                            writer.WriteAttributeString("Include", Utils.GetRelativePath(filePath, project.GetProjectDirectory()));
                            writer.WriteEndElement();
                        }
                    }

                    if (project.PreCompiledHeaderGroup != null)
                    {
                        if (BuildTool.fileGroups[project.PreCompiledHeaderGroup].Count != 1)
                        {
                            throw new Exception("Only one pch.cpp is allowed");
                        }
                        string pchcpp = BuildTool.fileGroups[project.PreCompiledHeaderGroup][0];
                        writer.WriteStartElement("ClCompile");
                        writer.WriteAttributeString("Include", pchcpp);
                        writer.WriteElementString("PrecompiledHeader", "Create");
                        writer.WriteEndElement();
                    }


                    // End itemgroup
                    writer.WriteEndElement();
                }

                private void WriteProjectReferences(XmlWriter writer, Core.Project project)
                {
                    writer.WriteStartElement("ItemGroup");

                    foreach (string projectName in project.AdditionalReferences)
                    {
                        int projectID = BuildTool.GetProject(projectName).ProjectID;

                        writer.WriteStartElement("ProjectReference");
                        writer.WriteAttributeString("Include", BuildTool.projects[projectID].Path);
                        writer.WriteElementString("Project", '{' + GUID.predefinedGUIDs[projectID] + '}');
                        writer.WriteEndElement();
                    }

                    writer.WriteEndElement();
                }

                private void WriteImportCppTargets(XmlWriter writer)
                {
                    writer.WriteStartElement("Import");
                    writer.WriteAttributeString("Project", @"$(VCTargetsPath)\Microsoft.Cpp.Targets");
                    writer.WriteEndElement();
                }
            }
        }
    }
}
