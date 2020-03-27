using System;
using System.Collections.Generic;

namespace QED
{
    namespace BuildTool
    {
        // Types of classes :
        //      BuildTool
        //      Directory
        //      File
        //      Configuration
        //      Project
        //      Solution
        //      Triggers
        class Program
        {
            static void Main(string[] args)
            {
                Core.Attributes.RegisterAttributes();

                int i = BuildTool.directories.Count;
                int k = BuildTool.fileGroups.Count;
                int m = BuildTool.projects.Count;

                foreach (Core.Project project in BuildTool.projects)
                {
                    // Create filters after conditionals are set
                    project.Filters = new List<Core.Filter>();
                    foreach (Core.Architecture architecture in project.Targets.GetArchitectureFlags())
                    {
                        foreach (Core.Platform platform in project.Targets.GetPlatformFlags())
                        {
                            foreach (Core.Configuration configuration in project.Targets.GetConfigurationFlags())
                            {
                                project.Filters.Add(new Core.Filter(architecture, platform, configuration));
                                foreach (var conditional in project.Conditionals)
                                {
                                    if
                                        (
                                            (conditional.ArchitectureFilters.HasValue == false || conditional.ArchitectureFilters.Value.HasFlag(architecture)) &&
                                            (conditional.PlatformFilters.HasValue == false || conditional.PlatformFilters.Value.HasFlag(platform)) &&
                                            (conditional.ConfigurationFilters.HasValue == false || conditional.ConfigurationFilters.Value.HasFlag(configuration))
                                        )
                                    {
                                        project.Filters[project.Filters.Count - 1].EnableOptimizations = conditional.EnableOptimizations;
                                        project.Filters[project.Filters.Count - 1].UseDebugStdLibrary = conditional.UseDebugStdLibrary;
                                        project.Filters[project.Filters.Count - 1].StaticLinkStdLibrary = conditional.StaticLinkStdLibrary;
                                        project.Filters[project.Filters.Count - 1].EnablePrecompiledHeaders = conditional.EnablePrecompiledHeaders;
                                        project.Filters[project.Filters.Count - 1].PrecompiledHeaderFileGroup = conditional.PrecompiledHeaderFileGroup;
                                        project.Filters[project.Filters.Count - 1].CompilerOptions = conditional.CompilerOptions;
                                        project.Filters[project.Filters.Count - 1].EnableIncrementalLinking = conditional.EnableIncrementalLinking;
                                        project.Filters[project.Filters.Count - 1].PreprocessorDefinitions = conditional.PreprocessorDefinitions;
                                    }
                                }
                            }
                        }
                    }
                }

                VisualStudio.Project vsproject = new VisualStudio.Project();
                vsproject.Generate(BuildTool.projects[0]);

                //VisualStudio.Solution solution = new VisualStudio.Solution();
                //solution.Generate();

                Console.ReadKey();
            }
        }
    }
}

