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
                        // Import cpp default props
                        WriteImportDefaultCppProperties(writer);

                        // 5
                        // Output type / toolset
                        WriteOutputTypeAndToolset(writer, project);

                        // 6
                        // Import cpp props
                        WriteImportCppProperties(writer);

                        // 7
                        // Compiled files
                        WriteIncludedSourceFiles(writer, project);

                        // 8
                        // Included files
                        WriteIncludedHeaderFiles(writer, project);

                        // 9
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

                private void WriteImportDefaultCppProperties(XmlWriter writer)
                {
                    writer.WriteStartElement("Import");
                    writer.WriteAttributeString("Project", @"$(VCTargetsPath)\Microsoft.Cpp.default.props");
                    writer.WriteEndElement();
                }

                private void WriteOutputTypeAndToolset(XmlWriter writer, Core.Project project, string toolset = "v142")
                {
                    writer.WriteStartElement("PropertyGroup");
                    writer.WriteElementString("ConfigurationType", ConversionUtils.GetOutputTypeString(project.OutputType));
                    writer.WriteElementString("PlatformToolset", toolset);
                    writer.WriteEndElement();
                }

                private void WriteImportCppProperties(XmlWriter writer)
                {
                    writer.WriteStartElement("Import");
                    writer.WriteAttributeString("Project", @"$(VCTargetsPath)\Microsoft.Cpp.props");
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
                            writer.WriteAttributeString("Include", filePath);
                            writer.WriteEndElement();
                        }
                    }

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
            }
        }
    }
}
