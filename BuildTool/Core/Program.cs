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



                // Project setup
                foreach (Core.Project project in BuildTool.projects)
                {
                    project.CreateFilters();
                    project.RetieveProjectPath();
                }
                
                // Project generation
                foreach (var project in BuildTool.projects)
                {
                    VisualStudio.Project vsproject = new VisualStudio.Project();
                    vsproject.Generate(project);
                }

                // Project group setup
                foreach (Core.ProjectGroup projectGroup in BuildTool.projectGroups)
                {
                    projectGroup.RetieveProjectGroupPath();
                }

                // Project group generation
                VisualStudio.Solution solution = new VisualStudio.Solution();
                solution.Generate(BuildTool.GetProjectGroup("QED"));

                Console.ReadKey();
            }
        }
    }
}

