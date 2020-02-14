using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace QED
{
    namespace BuildTool
    {
        namespace VisualStudio
        {
            class Solution
            {
                public async void Generate()
                {
                    using (StreamWriter writer = File.CreateText("solution.sln"))
                    //using (StreamWriter writer = new StreamWriter(Console.OpenStandardOutput()))
                    {
                        // Write Visual studio version specific header
                        await writer.WriteLineAsync("Microsoft Visual Studio Solution File, Format Version 12.00");
                        await writer.WriteLineAsync("# Visual Studio 16");

                        // Define projects
                        await writer.WriteLineAsync(String.Format("Project(\"{{{0}}}\") = \"project\", \"project.vcxproj\", \"{{{1}}}\"", GUID.ProjectGUID, GUID.predefinedGUIDs[0]));
                        await writer.WriteLineAsync("EndProject");

                        // Start global area
                        await writer.WriteLineAsync("Global");

                        // Define architecture / platform
                        await writer.WriteLineAsync("\tGlobalSection(SolutionConfigurationPlatforms) = preSolution");

                        await writer.WriteLineAsync("\t\tDebug|Win32 = Debug|Win32");
                        await writer.WriteLineAsync("\t\tRelease|Win32 = Release|Win32");
                        
                        await writer.WriteLineAsync("\tEndGlobalSection");

                        // List all possible configs for all projects
                        await writer.WriteLineAsync("\tGlobalSection(ProjectConfigurationPlatforms) = postSolution");

                        await writer.WriteLineAsync(String.Format("\t\t{{{0}}}.Debug|Win32.ActiveCfg = Debug|Win32", GUID.predefinedGUIDs[0]));
                        await writer.WriteLineAsync(String.Format("\t\t{{{0}}}.Debug|Win32.Build.0 = Debug|Win32", GUID.predefinedGUIDs[0]));
                        await writer.WriteLineAsync(String.Format("\t\t{{{0}}}.Release|Win32.ActiveCfg = Release|Win32", GUID.predefinedGUIDs[0]));
                        await writer.WriteLineAsync(String.Format("\t\t{{{0}}}.Release|Win32.ActiveCfg = Release|Win32", GUID.predefinedGUIDs[0]));

                        await writer.WriteLineAsync("\tEndGlobalSection");

                        // Disable hide solution flag
                        await writer.WriteLineAsync("\tGlobalSection(SolutionProperties) = preSolution");
                        await writer.WriteLineAsync("\t\tHideSolutionNode = FALSE");
                        await writer.WriteLineAsync("\tEndGlobalSection");

                        // Assign projects to virtual folders
                        //TODO: Assign projects to virtual folders

                        // End file
                        await writer.WriteLineAsync("EndGlobal");
                    }
                }
            }
        }
    }
}
