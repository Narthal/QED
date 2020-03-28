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
                    ProjectGroupID = BuildTool.projectGroups.Count;
                    Name = this.GetType().Name;

                    // Projects
                    ProjectIDs = new List<int>();
                }

                public void RetieveProjectGroupPath()
                {
                    object[] customAttributes = GetType().GetCustomAttributes(true);
                    foreach (Attribute attribute in customAttributes)
                    {
                        if (attribute.GetType() == typeof(RegisterPathAttribute))
                        {
                            var PathAttribute = (RegisterPathAttribute)attribute;
                            Path = System.IO.Directory.GetParent(PathAttribute.SourcePath).FullName + '\\' + Name + ".sln";
                        }
                    }
                }

                public string Name { get; set; }
                public string Path { get; private set; }
                public int ProjectGroupID { get; private set; }
                public void AddProject(string projectName)
                {
                    ProjectIDs.Add(BuildTool.GetProject(projectName).ProjectID);
                }

                public List<int> ProjectIDs { get; private set; }
            }
        }
    }
}
