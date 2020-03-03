using System;


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

                VisualStudio.ProjectGenerator project = new VisualStudio.ProjectGenerator();
                project.Generate(BuildTool.projects[0]);

                //VisualStudio.Solution solution = new VisualStudio.Solution();
                //solution.Generate();

                Console.ReadKey();
            }
        }
    }
}

