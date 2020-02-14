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
                int j = BuildTool.fileGroups.Count;
                int k = BuildTool.fileGroupNames.Count;
                string l = BuildTool.TargetConfig.ToString();

                //VisualStudio.Project project = new VisualStudio.Project();
                //project.Generate();

                //VisualStudio.Solution solution = new VisualStudio.Solution();
                //solution.Generate();

                Console.ReadKey();
            }
        }
    }
}

