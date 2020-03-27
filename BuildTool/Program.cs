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
                    project.CreateFilters();
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

