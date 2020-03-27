using System;
using System.Collections.Generic;
using System.Reflection;

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
                                        foreach (PropertyInfo filterPropertyInfo in project.Filters.GetType().GetGenericArguments()[0].GetProperties())
                                        {
                                            foreach (PropertyInfo conditionalPropertyInfo in conditional.GetType().GetProperties())
                                            {
                                                if (filterPropertyInfo.Name == conditionalPropertyInfo.Name)
                                                {
                                                    filterPropertyInfo.SetValue(project.Filters[project.Filters.Count - 1], conditionalPropertyInfo.GetValue(conditional));
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                VisualStudio.Project vsproject = new VisualStudio.Project();
                vsproject.Generate(BuildTool.projects[0]);

                VisualStudio.Solution solution = new VisualStudio.Solution();
                solution.Generate(new List<int> { 0 });

                Console.ReadKey();
            }
        }
    }
}

