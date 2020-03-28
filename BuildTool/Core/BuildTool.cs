using System;
using System.Collections.Generic;
using System.Text;

namespace QED
{
    namespace BuildTool
    {
        public static class BuildTool
        {
            #region Data

            // Registered directories
            public static List<Core.Directory> directories = new List<Core.Directory>();

            // Registered file group names
            public static Dictionary<string, List<string>> fileGroups = new Dictionary<string, List<string>>();

            // Registered projects
            public static List<Core.Project> projects = new List<Core.Project>();

            // Registered project groups
            public static List<Core.ProjectGroup> projectGroups = new List<Core.ProjectGroup>();

            #endregion

            #region Helper methods

            public static Core.Directory GetDirectory(string name)
            {
                foreach (Core.Directory directory in directories)
                {
                    if (directory.GetType().Name == name)
                    {
                        return directory;
                    }
                }

                throw new Exception("No such directory : " + name);
            }

            public static Core.Project GetProject(string name)
            {
                foreach (Core.Project project in projects)
                {
                    if (project.GetType().Name == name)
                    {
                        return project;
                    }
                }

                throw new Exception("No such project : " + name);
            }

            public static Core.ProjectGroup GetProjectGroup(string name)
            {
                foreach (Core.ProjectGroup projectGroup in projectGroups)
                {
                    if (projectGroup.GetType().Name == name)
                    {
                        return projectGroup;
                    }
                }

                throw new Exception("No such project group : " + name);
            }

            #endregion  

        }
    }
}

