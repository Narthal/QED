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
                public void Generate(Core.ProjectGroup projectGroup)
                {
                    StringBuilder stringBuilder = new StringBuilder();
                    using (StringWriter writer = new StringWriter(stringBuilder))
                    {
                        // Write Visual studio version specific header
                        writer.WriteLine("Microsoft Visual Studio Solution File, Format Version 12.00");
                        writer.WriteLine("# Visual Studio 16");

                        // Define projects
                        foreach (int projectID in projectGroup.ProjectIDs)
                        {
                            writer.WriteLine(String.Format("Project(\"{{{0}}}\") = \"" + BuildTool.projects[projectID].Name + "\", \"" + BuildTool.projects[projectID].Path + "\", \"{{{1}}}\"", GUID.ProjectGUID, GUID.predefinedGUIDs[projectID]));
                            writer.WriteLine("EndProject");
                        }

                        // Start global area
                        writer.WriteLine("Global");

                        // Define architecture / platform
                        writer.WriteLine("\tGlobalSection(SolutionConfigurationPlatforms) = preSolution");

                        Core.Platform firtsPlatform = BuildTool.projects[0].Filters[0].PlatformFilter;
                        foreach (Core.Filter filter in BuildTool.projects[0].Filters)
                        {
                            if (filter.PlatformFilter == firtsPlatform)
                            {
                                string configurationArchitecture = ConversionUtils.GetConfigurationString(filter.ConfigurationFilter) + '|' + ConversionUtils.GetArchitectureString(filter.ArchitectureFilter);
                                writer.WriteLine("\t\t" + configurationArchitecture + " = " + configurationArchitecture);
                            }
                        }

                        writer.WriteLine("\tEndGlobalSection");

                        // List all possible configs for all projects
                        writer.WriteLine("\tGlobalSection(ProjectConfigurationPlatforms) = postSolution");

                        foreach (int projectID in projectGroup.ProjectIDs)
                        {
                            foreach (Core.Filter filter in BuildTool.projects[projectID].Filters)
                            {
                                string configurationArchitecture = ConversionUtils.GetConfigurationString(filter.ConfigurationFilter) + '|' + ConversionUtils.GetArchitectureString(filter.ArchitectureFilter);

                                writer.WriteLine("\t\t{{{0}}}." + configurationArchitecture + ".ActiveCfg = " + configurationArchitecture, GUID.predefinedGUIDs[projectID]);
                                writer.WriteLine("\t\t{{{0}}}." + configurationArchitecture + ".Build.0 = " + configurationArchitecture, GUID.predefinedGUIDs[projectID]);
                            }
                        }

                        writer.WriteLine("\tEndGlobalSection");

                        // Disable hide solution flag
                        writer.WriteLine("\tGlobalSection(SolutionProperties) = preSolution");
                        writer.WriteLine("\t\tHideSolutionNode = FALSE");
                        writer.WriteLine("\tEndGlobalSection");

                        // Assign projects to virtual folders
                        //TODO: Assign projects to virtual folders

                        // End file
                        writer.WriteLine("EndGlobal");

                        // End
                        writer.Flush();
                    }

                    // Write solution to console
                    Console.WriteLine("Solution generated : ");
                    Console.ForegroundColor = ConsoleColor.Yellow;
                    Console.WriteLine(stringBuilder);
                    Console.WriteLine();
                    Console.ResetColor();

                    // Write solution to file
                    using (System.IO.StreamWriter file = new System.IO.StreamWriter(projectGroup.Path))
                    {
                        file.Write(stringBuilder.ToString());
                    }
                    Console.WriteLine("Done writing project file at " + projectGroup.Path);
                }
            }
        }
    }
}
