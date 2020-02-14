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
                public void Generate()
                {
                    // Create XML writer
                    var settings = new XmlWriterSettings()
                    {
                        Indent = true,
                        IndentChars = "  ",
                        Encoding = Encoding.UTF8,

                    };

                    using (XmlWriter writer = XmlWriter.Create(/*"project.vcxproj"*/Console.Out, settings))
                    {
                        // Write xml version, encoding
                        writer.WriteStartDocument();

                        // Project header element
                        writer.WriteStartElement("Project", "http://schemas.microsoft.com/developer/msbuild/2003");
                        writer.WriteAttributeString("DefaultTargets", "Build");
                        writer.WriteAttributeString("ToolsVersion", "16.0");
                        writer.WriteAttributeString("xmlns", "http://schemas.microsoft.com/developer/msbuild/2003");

                        // Configuration / Platform
                        writer.WriteStartElement("ItemGroup");

                        writer.WriteStartElement("ProjectConfiguration");
                        writer.WriteAttributeString("Include", "Debug|Win32");
                        writer.WriteElementString("Configuration", "Debug");
                        writer.WriteElementString("Platform", "Win32");
                        writer.WriteEndElement();

                        writer.WriteStartElement("ProjectConfiguration");
                        writer.WriteAttributeString("Include", "Release|Win32");
                        writer.WriteElementString("Configuration", "Release");
                        writer.WriteElementString("Platform", "Win32");
                        writer.WriteEndElement();

                        writer.WriteEndElement();

                        // Import cpp default props
                        writer.WriteStartElement("Import");
                        writer.WriteAttributeString("Project", @"$(VCTargetsPath)\Microsoft.Cpp.default.props");
                        writer.WriteEndElement();

                        // Output type / toolset
                        writer.WriteStartElement("PropertyGroup");
                        writer.WriteElementString("ConfigurationType", "Application");
                        writer.WriteElementString("PlatformToolset", "v142");
                        writer.WriteEndElement();

                        // Import cpp props
                        writer.WriteStartElement("Import");
                        writer.WriteAttributeString("Project", @"$(VCTargetsPath)\Microsoft.Cpp.props");
                        writer.WriteEndElement();

                        // Compiled files
                        writer.WriteStartElement("ItemGroup");
                        writer.WriteStartElement("ClCompile");
                        writer.WriteAttributeString("Include", "main.cpp");
                        writer.WriteEndElement();
                        writer.WriteEndElement();

                        // Included files
                        writer.WriteStartElement("ItemGroup");
                        writer.WriteStartElement("ClInclude");
                        writer.WriteAttributeString("Include", "main.h");
                        writer.WriteEndElement();
                        writer.WriteEndElement();

                        // Import cpp targets
                        writer.WriteStartElement("Import");
                        writer.WriteAttributeString("Project", @"$(VCTargetsPath)\Microsoft.Cpp.Targets");
                        writer.WriteEndElement();

                        // End of xml
                        writer.WriteEndElement();   // End project element
                        writer.WriteEndDocument();  // End document

                        writer.Flush();
                    }
                }
            }
        }
    }
}
