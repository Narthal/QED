using System;
using System.Collections.Generic;
using System.Text;

namespace QED
{
    namespace BuildTool
    {
        namespace Core
        {
            public abstract class ProjectGroup
            {
                public ProjectGroup()
                {
                    Projects = new List<string>();
                    ProjectIDs = new List<int>();
                }

                public void AddProject(string projectName)
                {
                    ProjectIDs.Add(BuildTool.GetProject(projectName).ProjectID);
                }

                public List<string> Projects { get; private set; }

                public List<int> ProjectIDs { get; private set; }
            }
        }
    }
}
