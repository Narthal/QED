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
                int j = BuildTool.fileGroups.Count;
                int k = BuildTool.projects.Count;
                int m = BuildTool.projectGroups.Count;

                foreach (Core.Project project in BuildTool.projects)
                {
                    project.CreateFilters();
                }

                foreach (var project in BuildTool.projects)
                {
                    VisualStudio.Project vsproject = new VisualStudio.Project();
                    vsproject.Generate(project);
                }
                

                VisualStudio.Solution solution = new VisualStudio.Solution();
                solution.Generate(BuildTool.projectGroups[0].ProjectIDs);

                Console.ReadKey();
            }
        }
    }
}

