using System;
using System.Collections.Generic;
using System.Text;

namespace QED
{
    namespace BuildTool
    {
        namespace Core
        {
            public enum OutputType
            {
                Application,
                SharedLibrary,
                StaticLibrary,
            }

            public enum CppVersion
            {
                cpp11,
                cpp14,
                cpp17
            }

            public abstract class Project : ConditionalConfigurationData
            {
                public Project()
                {
                    ProjectID = BuildTool.projects.Count;

                    // Directories
                    SourceFileGroups = new List<string>();
                    HeaderFileGroups = new List<string>();

                    // Conditionals
                    Conditionals = new List<Conditional>();

                    ReferencedProjectIDs = new List<int>();
                }


                #region Basic configuration

                public string Name { get; protected set; }
                public OutputType OutputType { get; protected set; }
                public CppVersion CppVersion { get; protected set; }

                #endregion

                #region Directories
                public Directory OutputDirectory { get; protected set; }
                public List<string> SourceFileGroups { get; protected set; }
                public List<string> HeaderFileGroups { get; protected set; }

                #endregion

                #region Target definitions

                public Targets Targets { get; protected set; }

                #endregion

                #region Config

                public List<Conditional> Conditionals { get; protected set; }
                public List<Filter> Filters { get; set; }
                public List<int> ReferencedProjectIDs { get; set; }

                #endregion

                public int ProjectID { get; private set; }
                public string Path { get; private set; }
            }
        }
    }
}
